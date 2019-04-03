#include <GameCommands.h>
#include <CharacterController.h>
#include <PigeonCommand.h>

#include <iostream>
#include <Utility.h>
#include <sstream>

//PigeonMail
std::pair<std::vector<Response>, bool> PigeonMail::execute() {
    std::vector<std::string> inputStrings = utility::popFront(input);
    std::string subcommand = inputStrings.front();

    if( subcommand == "interact" ) {
        return this->interact();
    }
    else if( subcommand == "deliver" ) {
        interactions.clear();
        std::vector<std::string> inputs = utility::tokenizeString(inputStrings.at(1));
        auto itr = inputs.begin();
        for( ; itr != inputs.end(); itr++ ) {
            std::vector<Name> possibleUserVector(inputs.begin(), itr);
            std::vector<Name> possibleItemVector(itr, inputs.end());
            auto possibleName = boost::algorithm::join(possibleUserVector, " ");
            auto possibleItem = boost::algorithm::join(possibleItemVector, " ");
            auto usernames = characterController->getUsernamesOfCharacter(possibleName);
            if( !usernames.empty() &&
                characterController->characterHasItem(username, possibleItem) ) {

                auto objects = characterController->getItemsFromCharacterInventory(username, possibleItem);
                for(const auto& obj : objects ) {
                    for( const auto& user : usernames ) {
                        interactions.emplace_back(user, obj);
                    }
                }
            }
        }
        if( interactions.size() > 1 ) {
            std::stringstream ss;
            ss << "Please specify to the pigeon which player and item you'd like to deliver to. \n";
            ss << "  Use /PigeonMail interact [#]\n";
            int counter = 0;
            for( auto& interaction : interactions ) {
                ss << ++counter << ". Character: " << characterController->getCharName(interaction.first) << "\n";
                ss << " - ID: " << characterController->getNPCID(interaction.first) << "\n";
                ss << "  Item to give: " << interaction.second.getName() << " - ID: " << interaction.second.getID() << "\n";
            }
            Response userResponse = Response(ss.str(), username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
        else if( interactions.empty() ) {
            Response userResponse = Response("Could not find username or item...", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }

        targetUsername = interactions.front().first;
        itemUniqueID = interactions.front().second.getID();
        releaseThePigeon();
        std::stringstream ss;
        ss << "Pigeon released. Your tracking number is: " << characterController->getCharName(pigeonUsername) << "\n";
        ss << "Use /PigeonMail status [tracking number] to get the status of your pigeon \n";

        registerCallback = true;
        callbackAfterHeartbeats = 150;

        Response userResponse = Response(ss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);

    }
    else if( subcommand == "status" ) {
        std::string pigeonName = inputStrings.at(1);
        if( pigeonName.find("Pigeon") == std::string::npos ) {
            Response userResponse = Response("Is this even a pigeon???", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
        auto usernames = characterController->getUsernamesOfCharacter(pigeonName);
        std::string pUsername;
        for( auto& user : usernames ) {
            if ( characterController->isCharacterNPC(user) ) {
                // Let's just assume this is the pigeon you want
                pUsername = user;
                break;
            }
        }
        if( pUsername.empty() ) {
            Response userResponse = Response("Please enter a valid tracking number.", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }

        ID userRoomID = characterController->getCharacterRoomID(username);
        auto toRoomID = characterController->getCharacterRoomID(pUsername);

        auto [direction, distance] = pigeonEXE->getShortestDirection(userRoomID, toRoomID);

        std::stringstream message;
        if( characterController->characterHasItem(pUsername, itemUniqueID) ) {
            message << "It looks like your pigeon has either delivered the package or lost it...\n";
            message << "It's currently " << distance << " room(s) away from you\n";
            message << "It is on it's way back... \n";
        }
        else {
            message << "Your high speed pigeon is on the way.\n";
            message << "It's currently " << distance << " room(s) away from you\n";
        }
        Response userResponse = Response(message.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }
    else {
        Response userResponse = Response(this->help(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }
}

void PigeonMail::releaseThePigeon() {
    auto roomID = characterController->getCharacterRoomID(username);
    Object obj = characterController->getItemFromCharacterInventory(username, itemUniqueID);
    objectID = obj.getObjectID();
    characterController->dropItemFromCharacterInventory(username, itemUniqueID);

    auto toRoomID = characterController->getCharacterRoomID(targetUsername);
    auto testID = roomID;
    while( testID != toRoomID ){
        auto [direction, distance] = pigeonEXE->getShortestDirection(testID, toRoomID);
        testID = roomController->getDoorDesignatedRoomId(testID, direction);
        std::cout << testID << " : " << direction << std::endl;
    }


    Character pigeon("Pigeon", roomID);
    auto pigeonUniqueID = pigeon.getID();
    pigeonName = "Pigeon#" + std::to_string(pigeonUniqueID);
    pigeon.setName(pigeonName);
    pigeonUsername = characterController->addNPC(pigeon);
    characterController->addItemToCharacterInventory(pigeonUsername, obj);
    roomController->addCharacterToRoom(pigeonName, roomID);
}

std::pair<std::vector<Response>, bool> PigeonMail::callback() {

    std::vector<Response> res;

    auto roomID = characterController->getCharacterRoomID(pigeonUsername);
    if( ! characterController->doesCharacterExist(targetUsername) ) {
        if( ! characterController->doesCharacterExist(username) ) {
            roomController->removeCharacterFromRoom(pigeonName, roomID);
            if(characterController->characterHasItem(pigeonUsername, itemUniqueID)) {
                roomController->addObjectToRoom(itemUniqueID, roomID);
            }
            characterController->removeCharacter(pigeonUsername);
            return std::make_pair(res, false);
        }
        else {
            auto toRoomID = characterController->getCharacterRoomID(username);
            auto [direction, distance] = pigeonEXE->getShortestDirection(roomID, toRoomID);
            ID newRoomID = characterController->getCharacterRoomID(pigeonUsername);
            if( distance ) {
                Door* door = roomController->searchDoor(roomID, direction);
                newRoomID = door->getDesignatedRoomId();
                roomController->removeCharacterFromRoom(pigeonName, roomID);
                roomController->addCharacterToRoom(pigeonName, newRoomID);
                characterController->setCharacterRoomID(pigeonUsername, newRoomID);
            }
            if( toRoomID == newRoomID ) {
                auto objects = characterController->getCharacter(pigeonUsername).getInventory().getObjects();
                for( auto& obj : objects ) {
                    characterController->addItemToCharacterInventory(username, obj);
                }
                std::stringstream message;
                message << "Target is offline. Pigeon has returned your items\n";
                message << "Thank you for using Pigeon Mail Delivery Services. :)";

                std::cout << "removed: " << roomController->removeCharacterFromRoom(pigeonName, roomID) << std::endl;

                characterController->removeCharacter(pigeonUsername);

                res.emplace_back(message.str(), username);
                return std::make_pair(res, true);
            }
        }
        registerCallback = true;
        return std::make_pair(res, false);
    }
    if( ! characterController->characterHasItem(pigeonUsername, itemUniqueID) ) {
        auto toRoomID = characterController->getCharacterRoomID(username);
        auto [direction, distance] = pigeonEXE->getShortestDirection(roomID, toRoomID);
        ID newRoomID = characterController->getCharacterRoomID(pigeonUsername);
        if( distance ) {
            Door* door = roomController->searchDoor(roomID, direction);
            newRoomID = door->getDesignatedRoomId();
            roomController->removeCharacterFromRoom(pigeonName, roomID);
            roomController->addCharacterToRoom(pigeonName, newRoomID);
            characterController->setCharacterRoomID(pigeonUsername, newRoomID);
        }
        if( toRoomID == newRoomID ) {
            auto objects = characterController->getCharacter(pigeonUsername).getInventory().getObjects();
            for( auto& obj : objects ) {
                characterController->addItemToCharacterInventory(username, obj);
            }

            roomController->removeCharacterFromRoom(pigeonName, roomID);

            characterController->removeCharacter(pigeonUsername);

            std::stringstream message;
            message << "Target is offline. Pigeon has returned your items\n";
            message << "Thank you for using Pigeon Mail Delivery Services. :)";
            res.emplace_back(message.str(), username);
            return std::make_pair(res, true);
        }
        registerCallback = true;
        return std::make_pair(res, false);
    }

    auto toRoomID = characterController->getCharacterRoomID(targetUsername);
    auto [direction, distance] = pigeonEXE->getShortestDirection(roomID, toRoomID);
    ID newRoomID = characterController->getCharacterRoomID(pigeonUsername);
    if( distance ) {
        Door* door = roomController->searchDoor(roomID, direction);
        newRoomID = door->getDesignatedRoomId();
        roomController->removeCharacterFromRoom(pigeonName, roomID);
        roomController->addCharacterToRoom(pigeonName, newRoomID);
        characterController->setCharacterRoomID(pigeonUsername, newRoomID);
    }
    if( toRoomID == newRoomID ) {
        auto objects = characterController->getCharacter(pigeonUsername).getInventory().getObjects();
        for( auto& obj : objects ) {
            characterController->addItemToCharacterInventory(targetUsername, obj);
        }

        roomController->removeCharacterFromRoom(pigeonName, roomID);
        if(characterController->characterHasItem(pigeonUsername, itemUniqueID)) {
            roomController->addObjectToRoom(itemUniqueID, roomID);
        }
        characterController->removeCharacter(pigeonUsername);

        std::stringstream message;
        message << "Pigeon has delivered your items to " << characterController->getCharName(targetUsername) << "\n";
        message << "Thank you for using Pigeon Mail Delivery Services. :)";
        res.emplace_back(message.str(), username);
        message.str(std::string());
        message.clear();
        message << characterController->getCharName(username) << " has delivered you items. \n";
        message << "Thank you for using Pigeon Mail Delivery Services. :)";
        res.emplace_back(message.str(), targetUsername);
        return std::make_pair(res, true);
    }

    registerCallback = true;
    return std::make_pair(res, false);
}

std::pair<std::vector<Response>, bool> PigeonMail::interact() {
    std::vector<std::string> v = utility::tokenizeString(input);

    if ( v.size() != 2 ) {
        std::cout << "Too many arguments..." << std::endl;
        Response userResponse = Response("Please enter /PigeonMail interact #", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    std::stringstream ss{v.at(INTERACT_CHOICE)};
    int index = -1;
    ss >> index;
    index--;
    if ( index >= interactions.size() || index < 0 ) {
        Response userResponse = Response("Please enter /PigeonMail interact #", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    targetUsername = interactions.at(index).first;
    itemUniqueID = interactions.at(index).second.getID();
    interactions.clear();
    if( ! characterController->doesCharacterExist(targetUsername) ) {
        Response userResponse = Response("Target no longer exists...", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }
    if( ! characterController->characterHasItem(username, itemUniqueID) ) {
        Response userResponse = Response("You no longer have the item...", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    releaseThePigeon();
    ss.clear();
    ss << "Pigeon released. Your tracking number is: " << characterController->getCharName(pigeonUsername) << "\n";
    ss << "Use /PigeonMail status [tracking number] to get the status of your pigeon \n";

    Response userResponse = Response(ss.str(), username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

void PigeonMail::setInteractions(std::vector<std::pair<Name, Object>> i) {
    interactions = i;
}

std::unique_ptr<Command> PigeonMail::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto pm = std::make_unique<PigeonMail>(this->characterController, this->roomController, this->pigeonEXE, username, input);
    pm->setInteractions(this->interactions);
    return std::move(pm);
}

std::unique_ptr<Command> PigeonMail::clone() const {
    auto pm = std::make_unique<PigeonMail>(this->characterController, this->roomController, this->pigeonEXE, this->username, this->input);
    pm->setInteractions(this->interactions);
    return std::move(pm);
}

std::string PigeonMail::help() {
    std::string helpMessage = "/PigeonMail deliver [target name] [item] - delivers an item to the target\n";
    helpMessage += "/PigeonMail status [tracking number] - track your package";
    return helpMessage;
}
