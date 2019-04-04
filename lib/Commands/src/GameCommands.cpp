#include <GameCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <string>

//Say
std::pair<std::vector<Response>, bool> Say::execute() {
    std::cout << "Say " << input << std::endl;
    Name charName = characterController->getCharName(username);

    Response userResponse = Response("Me: " + input, username);

    std::string genericMessage = charName + ": "+ input;
    std::cout << genericMessage << std::endl;

    auto res = formulateResponse(userResponse,
                                 roomController->getCharacterList(characterController->getCharacterRoomID(username)), genericMessage);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Say::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto say = std::make_unique<Say>(this->characterController, this->roomController, username, input);
    return std::move(say);
}

std::unique_ptr<Command> Say::clone() const {
    auto say = std::make_unique<Say>(this->characterController, this->roomController, this->username, this->input);
    return std::move(say);
}

std::string Say::help() {
    return "/say [message] - sends message to other players in the room";
}


// tell
std::pair<std::vector<Response>, bool> Tell::execute() {
    std::vector<std::string> inputStrings = utility::popFront(target);

    //check if user input format is incorrect
    if (inputStrings.size() != 2 || target.empty()) {
        Response userResponse = Response(help(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    Name charName = characterController->getCharName(username);
    Name targetCharName = inputStrings.at(TARGET_CHARACTER_NAME);


    //if tell target character is not currently logged in
    if (!characterController->doesCharacterExist(targetCharName)) {
        Response userResponse = Response(targetCharName + " is not currently logged in", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    Name targetUserName = characterController->getUsernameOfCharacter(targetCharName);


    std::string message = inputStrings.at(MESSAGE);

    Response userResponse = Response("To [" + targetCharName + "]: " + message, username);
    Response targetResponse = Response("From [" + charName + "]: " + message, targetUserName);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Tell::clone(Name username, Input target, Connection connection = Connection{}) const {
    auto tell = std::make_unique<Tell>(this->characterController, username, target);
    return std::move(tell);
}

std::unique_ptr<Command> Tell::clone() const {
    auto tell = std::make_unique<Tell>(this->characterController, this->username, this->target);
    return std::move(tell);
}

std::string Tell::help() {
    return "/tell [target] [message] - Send a message to a specific player in the world";
};



// whisper
std::pair<std::vector<Response>, bool> Whisper::execute() {
    std::vector<std::string> inputStrings = utility::popFront(input);

    if (input.empty() || inputStrings.at(1).empty()) {
        Response userResponse = Response(help(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    Name charName = characterController->getCharName(username);
    Name targetCharName = inputStrings.at(TARGET_CHARACTER_NAME);

    //if tell target character is not currently logged in
    if (!characterController->doesCharacterExist(targetCharName)) {
        Response userResponse = Response(targetCharName + " is not currently logged in", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    Name targetUserName = characterController->getUsernameOfCharacter(targetCharName);




    std::string message = inputStrings.at(MESSAGE);

    Response userResponse = Response("To [" + targetCharName + "]: " + message, username);
    Response targetResponse = Response("From [" + charName + "]: " + message, targetUserName);
    std::string modifiedMessage = "From [" + charName + "] to [ " + targetCharName + " ]: " + whisperModifier(message);

    Response empty = Response();
    std::vector<std::string> characterList = roomController->getCharacterList(
            characterController->getCharacterRoomID(charName));
    removeTargets(characterList, username, targetUserName);

    auto res = formulateResponse(userResponse, targetResponse);
    auto resModified = formulateResponse(empty, characterList, modifiedMessage);

    res.insert(res.end(), resModified.begin(), resModified.end());

    return std::make_pair(res, true);
}

std::unique_ptr<Command> Whisper::clone() const {
    auto whisper = std::make_unique<Whisper>(this->characterController, this->roomController, this->username, this->input);
    return std::move(whisper);
}

std::unique_ptr<Command> Whisper::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto whisper = std::make_unique<Whisper>(this->characterController, this->roomController, username, input);
    return std::move(whisper);
}

std::string Whisper::help() {
    return "/whisper [target] [message] - Send a message to a specific player in the world ... but beware of prying ears";
}

void Whisper::removeTargets(std::vector<std::string> &characterList, Name username, Name targetName) {
    characterList.erase(
            std::remove_if(characterList.begin(), characterList.end(),
                           [username, targetName](const std::string &character) { return (character == username) || (character == targetName); }),
            characterList.end());
}

//DisplayInventory
std::pair<std::vector<Response>, bool> DisplayInventory::execute() {
    std::cout << "Inventory " << std::endl;

    //get the string containing inventory listed numerically
    std::string inventoryList = characterController->characterListInventory(username);

    //check if inventory is empty or not
    if(inventoryList.empty()) {
        Response userResponse = Response("Your inventory is empty!", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, true);
    }

    Response userResponse = Response("Your inventory has: \n" + inventoryList, username);
    auto res = formulateResponse(userResponse);

    return std::make_pair(res, true);
}

std::unique_ptr<Command> DisplayInventory::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto inventory = std::make_unique<DisplayInventory>(this->characterController, username, input);
    return std::move(inventory);
}

std::unique_ptr<Command> DisplayInventory::clone() const {
    auto inventory = std::make_unique<DisplayInventory>(this->characterController, this->username, this->input);
    return std::move(inventory);
}

std::string DisplayInventory::help() {
    return "/inventory - displays your inventory";
}

//Give
std::pair<std::vector<Response>, bool> Give::execute() {
    std::vector<std::string> inputStrings = utility::popFront(input);

    if ((inputStrings.at(CHECK_INTERACT) == "interact") && (!(interactionsCharacters.empty()) || !(interactionsGifts.empty())) ) {
        return this->interact();
    }

    ID roomId = characterController->getCharacterRoomID(username);
    std::vector<Name> charInRoom = roomController->getCharacterList(roomId);

    Name targetCharName = inputStrings.at(TARGET_CHARACTER_NAME);
    Name giftName = inputStrings.at(GIFT_NAME);

    for (auto &charName : charInRoom ) {
        if (input.find(charName) == 0) {
            targetCharName = charName;
            giftName = input.substr(charName.size() + 1);
        }
    }

    //check if user input format is incorrect
    if (targetCharName.empty() || giftName.empty()) {
        Response userResponse = Response("You must type in the {username of the character you wish to gift to}, {item name}", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    //check if gift item exists in user inventory
    if (!characterController->characterHasItem(username, giftName)) {
        Response userResponse = Response("Item name " + giftName + " does not exist for you to give.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    std::vector<Name> v = characterController->getUsernamesOfCharacter(targetCharName);
    std::vector<ID> targetIDs;
    std::vector<Object> giftItems = characterController->getItemsFromCharacterInventory(username, giftName);

    for (auto charName = v.begin(); charName != v.end(); ) {
        std::cout << *charName << std::endl;
        if (characterController->getCharacterRoomID(*charName) != roomId) {
            std::cout << "Erasing: " << *charName << std::endl;
            charName = v.erase(charName);
        }
        else {
            ID targetID = characterController->getCharID(*charName);
            targetIDs.push_back(targetID);
            ++charName;
        }
    }

    if (v.empty()) {
        Response userResponse = Response("Target doesn't exist, sorry!", username);

        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    if (giftItems.empty()) {
        Response userResponse = Response("Item " + giftName + " doesn't exist in your inventory, sorry!", username);

        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    std::cout << "v.size is " << v.size() << std::endl;

    if ((v.size() > 1 && targetIDs.size() > 1 ) || giftItems.size() > 1) {
        std::stringstream ss;

        if (v.size() > 1 && targetIDs.size() > 1) {
            interactionsCharacters = targetIDs;
            ss << "There is more than 1 charcter named " << targetCharName << ". Which character would you like to give to?\n";

            int counter = 0;
            for (auto &name : v) {
                ss << "\t" << ++counter << ". " << name << "\n";
            }
        }

        if (giftItems.size() > 1) {
            interactionsGifts = giftItems;
            ss << "You have more than 1 item named " << giftName << ". Which item would you like to give?\n";

            int counter = 0;
            for (auto &obj : interactionsGifts) {
                ss << "\t" << ++counter << ". " << obj.getName() << ", ID: " << obj.getID() << "\n";
            }
        }

        interactCharacterTargetID = targetIDs.front();
        interactGiftTarget = giftItems.front().getName();

        Response userResponse = Response(ss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    Name targetUserName = v.front();
    ID giftID = giftItems.front().getID();

    characterController->dropItemFromCharacterInventory(username, giftID);

    //drop item from user inventory
    if (characterController->characterHasItem(username, giftID)) {
        Response userResponse = Response("Gifting item has failed.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    //add item to target user inventory
    characterController->addItemToCharacterInventory(targetUserName, objectController->getObjectFromList(giftID));
    std::cout << objectController->getObjectFromList(giftID).getName() << std::endl;

    if (!characterController->characterHasItem(targetUserName, giftID)) {
        characterController->addItemToCharacterInventory(username, objectController->getObjectFromList(giftID));
        Response userResponse = Response("Giving " + giftName + " to character " + targetCharName + " has failed.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    Name charName = characterController->getCharName(username);

    //generate response
    Response userResponse = Response("You have given " + giftName + " to character " + targetCharName + "!", username);
    Response targetResponse = Response(charName + " has given " + giftName + " to you!", targetUserName);
    auto res = formulateResponse(userResponse, targetResponse);

    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Give::interact() {
    std::cout << "give interacting" << std::endl;

    std::cout << "input : " << input << std::endl;

    std::vector<std::string> v = utility::tokenizeString(input);

    std::cout << "v size : " << v.size() << std::endl;
    std::cout << "interactionsCharacters size : " << interactionsCharacters.size() << std::endl;
    std::cout << "interactionsGifts size : " << interactionsGifts.size() << std::endl;

    std::cout << "is interactionsCharacters empty? " << std::boolalpha << interactionsCharacters.empty() << std::endl;
    std::cout << "is interactionsGifts empty? " << interactionsGifts.empty() << std::endl;

    if (!interactionsCharacters.empty() && !interactionsGifts.empty() && v.size() != 3) {
        std::cout << "both are not empty" << std::endl;
        Response userResponse = Response("Please enter /give interact {index number of the character you wish to give to} {index number of the item you wish to give}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    } else if (!interactionsCharacters.empty() && interactionsGifts.empty() && v.size() != 2 ) {
        std::cout << "character isn't empty " << std::endl;
        Response userResponse = Response("Please enter /give interact {index number of the item you wish to give}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    } else if (interactionsCharacters.empty() && !interactionsGifts.empty() && v.size() != 2 ) {
        std::cout << "gifts isn't empty" << std::endl;
        Response userResponse = Response("Please enter /give interact {index number of the character you wish to give to}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    std::cout << "after if loops " << std::endl;

    Name targetUserName = characterController->getUsernameOfCharacter(interactCharacterTargetID);
    Name interactCharacterTarget = characterController->getCharName(targetUserName);

    std::cout << "interactCharacterTarget : " << interactCharacterTarget << std::endl;
    std::cout << "interactGiftTarget : " << interactGiftTarget << std::endl;

    std::cout << "size of getUsernamesOfCharacter(interactCharacterTarget) : " << characterController->getUsernamesOfCharacter(interactCharacterTarget).size() << std::endl;

    std::cout << "targetUserName : " << targetUserName << std::endl;

    ID giftID = characterController->getItemIDFromCharacterInventory(username, interactGiftTarget);

    std::cout << "giftID : " << giftID << std::endl;

    if (!interactionsCharacters.empty() && !interactionsGifts.empty()) {
        std::stringstream charss{v.at(1)};
        std::stringstream giftss{v.at(2)};

        int charIndex = -1;
        charss >> charIndex;
        charIndex--;

        int giftIndex = -1;
        giftss >> giftIndex;
        giftIndex--;

        if ( charIndex >= interactionsCharacters.size() || charIndex < 0 || giftIndex >= interactionsGifts.size() || giftIndex < 0 ) {
            Response userResponse = Response("Please enter /give interact {index number of the character you wish to give to} {index number of the item you wish to give}.", username);
            auto res = formulateResponse(userResponse);

            return std::make_pair(res, false);
        }

        targetUserName = characterController->getUsernameOfCharacter(interactionsCharacters.at(charIndex));
        giftID = interactionsGifts.at(giftIndex).getID();

        if (!characterController->doesCharacterExist(targetUserName)) {
            Response userResponse = Response("Character name " + interactCharacterTarget + " does not exist for you to gift to.", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }

        if (!characterController->characterHasItem(username, giftID)) {
            Response userResponse = Response("Item " + interactGiftTarget + " doesn't exist in your inventory, sorry!", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
    } else if (!interactionsCharacters.empty() && interactionsGifts.empty()) {
        std::stringstream charss{v.at(1)};

        int charIndex = -1;
        charss >> charIndex;
        charIndex--;

        if ( charIndex >= interactionsCharacters.size() || charIndex < 0 ) {
            Response userResponse = Response("Please enter /give interact {index number of the character you wish to give to}.", username);
            auto res = formulateResponse(userResponse);

            return std::make_pair(res, false);
        }

        targetUserName = characterController->getUsernameOfCharacter(interactionsCharacters.at(charIndex));

        if (!characterController->doesCharacterExist(targetUserName)) {
            Response userResponse = Response("Character name " + interactCharacterTarget + " does not exist for you to gift to.", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }

        if (!characterController->characterHasItem(username, giftID)) {
            Response userResponse = Response("Item " + interactGiftTarget + " doesn't exist in your inventory, sorry!", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
    } else if (interactionsCharacters.empty() && !interactionsGifts.empty()) {
        std::stringstream giftss{v.at(1)};

        int giftIndex = -1;
        giftss >> giftIndex;
        giftIndex--;

        if ( giftIndex >= interactionsGifts.size() || giftIndex < 0 ) {
            Response userResponse = Response("Please enter /give interact {index number of the item you wish to give}.", username);
            auto res = formulateResponse(userResponse);

            return std::make_pair(res, false);
        }

        giftID = interactionsGifts.at(giftIndex).getID();

        if (!characterController->doesCharacterExist(targetUserName)) {
            Response userResponse = Response("Character name " + interactCharacterTarget + " does not exist for you to gift to.", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }

        if (!characterController->characterHasItem(username, giftID)) {
            Response userResponse = Response("Item " + interactGiftTarget + " doesn't exist in your inventory, sorry!", username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
    }

    std::cout << "target user name is : " << targetUserName << std::endl;
    std::cout << "gift id is " << giftID << std::endl;

    //drop item from user inventory
    characterController->dropItemFromCharacterInventory(username, giftID);

    if (characterController->characterHasItem(username, giftID)) {
        Response userResponse = Response("Gifting item has failed.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    //add item to target user inventory
    characterController->addItemToCharacterInventory(targetUserName, objectController->getObjectFromList(giftID));

    if (!characterController->characterHasItem(targetUserName, giftID)) {
        characterController->addItemToCharacterInventory(username, objectController->getObjectFromList(giftID));
        Response userResponse = Response("Giving " + interactGiftTarget + " to character " + targetUserName + " has failed.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    Name charName = characterController->getCharName(username);
    Name targetCharName = characterController->getCharName(targetUserName);
    //generate response
    Response userResponse = Response("You have given " + interactGiftTarget + " to character " + targetCharName + "!", username);
    Response targetResponse = Response(charName + " has given " + interactGiftTarget + " to you!", targetUserName);

    interactionsCharacters.clear();
    interactionsGifts.clear();

    auto res = formulateResponse(userResponse, targetResponse);

    return std::make_pair(res, true);
}


std::unique_ptr<Command> Give::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto give = std::make_unique<Give>(this->characterController, this->roomController, this->objectController, username, input);
    give->setInteractions(this->interactionsCharacters, this->interactionsGifts, this->interactCharacterTargetID, this->interactGiftTarget);
    return std::move(give);
}

std::unique_ptr<Command> Give::clone() const {
    auto give = std::make_unique<Give>(this->characterController, this->roomController, this->objectController, this->username, this->input);
    give->setInteractions(this->interactionsCharacters, this->interactionsGifts, this->interactCharacterTargetID, this->interactGiftTarget);
    return std::move(give);
}

std::string Give::help() {
    return "/give [target's character name] [item name] - give item to a player";
}

void Give::setInteractions(std::vector<ID> iC, std::vector<Object> iG, ID interactC, Name interactG) {
    interactionsCharacters = iC;
    interactionsGifts = iG;
    interactCharacterTargetID = interactC;
    interactGiftTarget = interactG;
}

// Confuse
std::pair<std::vector<Response>, bool> Confuse::execute(){

    if(target.empty()) {
        Response userResponse(help(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    //if tell target character is not currently logged in
    if (!characterController->doesCharacterExist(target)) {
        Response userResponse = Response(target + ": is not currently logged in", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    Name targetUserName = characterController->getUsernameOfCharacter(target);

    characterController->confuseCharacter(targetUserName);

    Response userResponse = Response("Successfully confused!", username);
    Response targetResponse = Response("A confuse spell was cast on you!", targetUserName);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Confuse::callback(){

    Name targetUserName = characterController->getUsernameOfCharacter(target);

    characterController->confuseCharacter(targetUserName);

    Response userResponse = Response("Your target is no longer confused", username);
    Response targetResponse = Response("You are no longer confused", targetUserName);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);

}

std::unique_ptr<Command> Confuse::clone() const {
    auto confuse = std::make_unique<Confuse>(this->characterController, this->roomController, this->username, this->target);
    return std::move(confuse);
}

std::unique_ptr<Command> Confuse::clone(Name username, Input target, Connection connection) const {
    auto confuse = std::make_unique<Confuse>(this->characterController, this->roomController, username, target);
    return std::move(confuse);
}

std::string Confuse::help(){
    return "/confuse [target] - confuses a target and they see weird things";
}

//Swap
std::pair<std::vector<Response>, bool> Swap::execute() {

    if (target.empty()) {
        Response userResponse = Response(help(), username);

        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    std::vector<std::string> inputStrings = utility::popFront(target);

    if((inputStrings.at(CHECK_INTERACT) == "interact") && !(interactions.empty())) {
        return this->interact();
    }

    std::vector<Name> v = characterController->getUsernamesOfCharacter(target);
    ID roomId = characterController->getCharacterRoomID(username);

    for (auto npcName = v.begin(); npcName != v.end(); ) {
        std::cout << *npcName << std::endl;
        if (characterController->getCharacterRoomID(*npcName) != roomId) {
            std::cout << "Erasing: " << *npcName << std::endl;
            npcName = v.erase(npcName);
        }
        else {
            ++npcName;
        }
    }

    std::cout << "v.size is " << v.size() << std::endl;

    if (v.size() > 1) {

        interactions = v;
        std::stringstream ss;

        ss << "There is more than 1 NPC named " << target << ". Which NPC would you like to swap with?\n";

        int counter = 0;
        for (auto &name : interactions) {
            ss << "\t" << ++counter << ". " << name << "\n";
        }

        Response userResponse = Response(ss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    if (v.empty()) {
        Response userResponse = Response("Target doesn't exist, sorry!", username);

        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    originalUsername = username;
    originalTargetUsername = v.front();
    swappedCharacterName = target;
    swappedTargetCharacterName = characterController->getCharName(username);

    characterController->swapCharacter(username, originalTargetUsername);

    Response userResponse = Response("Successfully swapped!", username);
    Response targetResponse = Response("A swap spell was cast on you!", originalTargetUsername);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Swap::interact() {
    originalUsername = username;

    std::vector<std::string> v = utility::tokenizeString(target);

    if ( v.size() != 2 ) {
        std::cout << "Too many arguments..." << std::endl;
        Response userResponse = Response("Please enter /swap interact {index number of the NPC you wish to swap with}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    std::stringstream ss{v.at(INTERACT_CHOICE)};
    int index = -1;
    ss >> index;
    index--;
    if ( index >= interactions.size() || index < 0 ) {
        Response userResponse = Response("Please enter /swap interact {index number of the NPC you wish to swap with}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    originalTargetUsername = interactions.at(index);
    swappedCharacterName = characterController->getCharName(originalTargetUsername);
    swappedTargetCharacterName = characterController->getCharName(username);

    characterController->swapCharacter(username, originalTargetUsername);

    Response userResponse = Response("Successfully swapped!", username);
    Response targetResponse = Response("A swap spell was cast on you!", originalTargetUsername);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Swap::callback() {

    if( characterController->getCharName(originalUsername) != swappedCharacterName ||
        characterController->getCharName(originalTargetUsername) != swappedTargetCharacterName) {
        registerCallback = true;
        callbackAfterHeartbeats = 50;
        return std::make_pair(std::vector<Response>{}, false);
    }

    characterController->swapCharacter(originalUsername, originalTargetUsername);

    Response userResponse = Response("Successfully unswapped!", originalUsername);
    Response targetResponse = Response("You have been successfully unswapped!", originalTargetUsername);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Swap::clone(Name username, Input target, Connection connection = Connection{}) const {
    auto swap = std::make_unique<Swap>(this->characterController, this->roomController, username, target);
    if(target.find("interact ") != std::string::npos) {
        swap->setInteractions(this->interactions);
    }
    return std::move(swap);
}

std::unique_ptr<Command> Swap::clone() const {
    auto swap = std::make_unique<Swap>(this->characterController, this->roomController, this->username, this->target);
    swap->setInteractions(this->interactions);
    return std::move(swap);
}

void Swap::setInteractions(std::vector<std::string> i) {
    interactions = i;
}

std::string Swap::help() {
    return "/swap [target username] - swap with the target character with this username";
}

//look
std::pair<std::vector<Response>, bool> Look::execute() {
    std::vector<std::string> inputStrings = utility::popFront(target);

    if (inputStrings.size() >= 2) {
        if ((inputStrings.at(CHECK_INTERACT) == "interact") && !(interactions.empty())) {
            return this->interact();
        }
    }

    interactions.clear();

    std::stringstream ss;
    std::stringstream intss;
    ID roomId = characterController->getCharacterRoomID(username);

    auto characterList = roomController->getCharacterList(roomId);
    auto objectList = roomController->getObjectList(roomId);

    ss << line;


    // with no argument
    if (target.empty()){
        ss << roomController->getRoomDescription(roomId);

        // format username into string stream
        ss << "Characters in room: \n";
        for (const auto& characterName : characterList){
            ss << "\t" << characterName << "\n";
        }

        // format object name into string stream
        ss << "Items in room: \n";
        for (const ID objectId : objectList){
            ss << "\t" <<objectController->getObjectName(objectId) << "\n";
        }

        ss << roomController->getAllDoorInformationInRoom(roomId);

        ss << line;
        Response userResponse = Response(ss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // with argument

    int index = 0;

    intss << "There is more than 1 NPC/objects named " << target << ". Which NPC/objects would you like to look at?\n";

    // search character
    for (auto &characterName : characterList){

        if (characterName == target) {

            if (!characterController->doesCharacterExist(characterName) && !characterController->getUsernamesOfCharacter(characterName).empty()) {
                std::vector<Name> npcNames = characterController->getUsernamesOfCharacter(characterName);
                for(auto& name : npcNames) {
                    std::cout << "list: " << name << std::endl;
                }
                std::cout << npcNames.size() << std::endl;

                for (auto npcName = npcNames.begin(); npcName != npcNames.end(); ) {
                    std::cout << *npcName << std::endl;
                    if (characterController->getCharacterRoomID(*npcName) != roomId) {
                        std::cout << "Erasing: " << *npcName << std::endl;
                        npcName = npcNames.erase(npcName);
                    }
                    else {
                        ++npcName;
                    }
                }

                interactions = npcNames;

                for (auto &name : interactions) {
                    intss << "\t" << ++index << ". " << target << "- " << characterController->getCharacterInfo(name) << "\n";
                }

                if (index > 1) {
                    std::cout << "more than 1" << std::endl;

                    break;
                } else if (index == 1) {
                    std::cout << "Help" << std::endl;
                    characterName = npcNames.front();
                    std::cout << "Help" << std::endl;
                    std::cout << characterName << std::endl;
                    std::cout << "Seg fault?" << std::endl;

                    ss << "\t" << characterName << "\n" << characterController->lookCharacter(characterName) << "\n";
                    break;
                } else {
                    std::cout << "npc list is empty???" << std::endl;
                    continue;
                }

            }
            ss << "\t" << characterName << "\n" << characterController->lookCharacter(characterName) << "\n";
            index += 1;
        }
    }



    //search object
    for (const ID objectId : objectList){
        Name objectName = objectController->getObjectName(objectId);
        if (objectName == target) {
            ss << "\t" << target << "- " << objectId<< "\n" << objectController->lookItem(objectId);
            intss << "\t" << ++index << ". " << target << "- ID: "  <<
               objectId<< "- Type: Item\n";
            interactions.push_back(std::to_string(objectId));
        }
    }

    if (index >= 2){
        intss << line;
        Response userResponse = Response(intss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    if (index <= 0){
        Response userResponse = Response("Target not found.\n", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    ss << line;
    interactions.clear();
    Response userResponse = Response(ss.str(), username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, false);

}

std::unique_ptr<Command> Look::clone() const {
    auto look = std::make_unique<Look>(this->characterController, this->roomController, this->objectController,
                                       this->username, this->target);
    look->setInteractions(this->interactions);
    return std::move(look);
}

std::unique_ptr<Command> Look::clone(Name username, Input target, Connection connection) const {
    auto look = std::make_unique<Look>(this->characterController, this->roomController, this->objectController,
                                       username, target);
    look->setInteractions(this->interactions);
    return std::move(look);
}

std::pair<std::vector<Response>, bool> Look::interact() {
    std::vector<std::string> inputStrings = utility::tokenizeString(target);

    if (inputStrings.size() <= 1){
        Response userResponse = Response("Please input a target. /look interact {index}", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }
    std::stringstream ss;
    std::string selection = inputStrings.at(INTERACT_TARGET);

    std::stringstream tmpSs{selection};
    int index = -1;
    tmpSs >> index;
    index--;

    if ( index >= interactions.size() || index < 0 ) {
        Response userResponse = Response("Please enter /look interact {index number of character or object}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    std::string interactTarget = interactions.at(index);
    ID roomId = characterController->getCharacterRoomID(username);

    bool has_only_digits = (interactTarget.find_first_not_of( "0123456789" ) == std::string::npos);

    if (has_only_digits){
        ID objectId = std::stoul(interactTarget);
        Name objectName = objectController->getObjectName(objectId);
        auto objectList = roomController->getObjectList(roomId);
        if (roomController->doesObjectExistInRoom(roomId, objectId)) {
            ss << line;
            ss << "\t" << objectName << "-" << objectId << "\n" << objectController->lookItem(objectId) << "\n";
            ss << line;
        }else{
            ss << objectName << " is not in the room.\n";
            Response userResponse = Response(ss.str(), username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
    }else{
        if (characterController->getCharacterRoomID(interactTarget) == roomId) {
            ss << line;
            ss << "\t" << interactTarget << "\n" << characterController->lookCharacter(interactTarget) << "\n";
            ss << line;
        }else{
            ss << interactTarget << " is not in the room.\n";
            Response userResponse = Response(ss.str(), username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
    }


    Response userResponse = Response(ss.str(), username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, false);
}

void Look::setInteractions(std::vector<std::string> i) {
    interactions = i;
}

std::string Look::help() {
    return "/look [target] - get short description of the target, or use /look to get short description about the room.";
}

std::pair<std::vector<Response>, bool> Examine::execute() {

    std::vector<std::string> inputStrings = utility::popFront(target);

    if((inputStrings.at(CHECK_INTERACT) == "interact") && !(interactions.empty())) {
        return this->interact();
    }

    if (target.empty()){
        Response userResponse = Response("Please input a target.\n", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    interactions.clear();

    std::stringstream ss;
    std::stringstream intss;
    intss << line;
    ss << line;

    ID roomId = characterController->getCharacterRoomID(username);

    auto characterList = roomController->getCharacterList(roomId);
    auto objectList = roomController->getObjectList(roomId);

    int index = 0;

    intss << "There is more than 1 NPC/objects named " << target << ". Which NPC/objects would you like to examine?\n";

    // search character
    for (auto &characterName : characterList){

        if (characterName == target) {

            if (!characterController->doesCharacterExist(characterName) && !characterController->getUsernamesOfCharacter(characterName).empty()) {
                std::vector<Name> npcNames = characterController->getUsernamesOfCharacter(characterName);
                for(auto& name : npcNames) {
                    std::cout << "list: " << name << std::endl;
                }
                std::cout << npcNames.size() << std::endl;

                for (auto npcName = npcNames.begin(); npcName != npcNames.end(); ) {
                    std::cout << *npcName << std::endl;
                    if (characterController->getCharacterRoomID(*npcName) != roomId) {
                        std::cout << "Erasing: " << *npcName << std::endl;
                        npcName = npcNames.erase(npcName);
                    }
                    else {
                        ++npcName;
                    }
                }

                interactions = npcNames;

                for (auto &name : interactions) {
                    intss << "\t" << ++index << ". " << target << "- " << characterController->getCharacterInfo(name) << "\n";
                }

                if (index > 1) {
                    std::cout << "more than 1" << std::endl;

                    break;
                } else if (index == 1) {
                    std::cout << "Help" << std::endl;
                    characterName = npcNames.front();
                    std::cout << "Help" << std::endl;
                    std::cout << characterName << std::endl;
                    std::cout << "Seg fault?" << std::endl;

                    ss << "\t" << characterName << "\n" << characterController->examineCharacter(characterName) << "\n";
                    break;
                } else {
                    std::cout << "npc list is empty???" << std::endl;
                    continue;
                }

            }
            ss << "\t" << characterName << "\n" << characterController->examineCharacter(characterName) << "\n";
            index += 1;
        }
    }


    //search object
    for (const ID objectId : objectList){
        Name objectName = objectController->getObjectName(objectId);
        if (objectName == target) {
            ss << "\t" << target << "- " << objectId<< "\n" << objectController->lookItem(objectId);
            intss << "\t" << ++index << ". " << target << "- ID: "  <<
                  objectId<< "- Type: Item\n";
            interactions.push_back(std::to_string(objectId));
        }
    }

    if (index >= 2){
        intss << line;
        Response userResponse = Response(intss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    if (index <= 0){
        Response userResponse = Response("Target not found.\n", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    ss << line;
    interactions.clear();
    Response userResponse = Response(ss.str(), username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, false);
}

std::pair<std::vector<Response>, bool> Examine::interact() {
    std::vector<std::string> inputStrings = utility::tokenizeString(target);

    if (inputStrings.size() <= 1){
        Response userResponse = Response("Please input a target. /examine interact {index}", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }
    std::stringstream ss;
    std::string selection = inputStrings.at(INTERACT_TARGET);

    std::stringstream tmpSs{selection};
    int index = -1;
    tmpSs >> index;
    index--;

    if ( index >= interactions.size() || index < 0 ) {
        Response userResponse = Response("Please enter /examine interact {index number of character or object}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    std::string interactTarget = interactions.at(index);
    ID roomId = characterController->getCharacterRoomID(username);

    bool has_only_digits = (interactTarget.find_first_not_of( "0123456789" ) == std::string::npos);

    if (has_only_digits){
        ID objectId = std::stoul(interactTarget);
        Name objectName = objectController->getObjectName(objectId);
        auto objectList = roomController->getObjectList(roomId);
        if (roomController->doesObjectExistInRoom(roomId, objectId)) {
            ss << line;
            ss << "\t" << objectName << "-" << objectId << "\n" << objectController->examineItem(objectId) << "\n";
            ss << line;
        }else{
            ss << objectName << " is not in the room.\n";
            Response userResponse = Response(ss.str(), username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
    }else{
        if (characterController->getCharacterRoomID(interactTarget) == roomId) {
            ss << line;
            ss << "\t" << interactTarget << "\n" << characterController->examineCharacter(interactTarget) << "\n";
            ss << line;
        }else{
            ss << interactTarget << " is not in the room.\n";
            Response userResponse = Response(ss.str(), username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, false);
        }
    }

    Response userResponse = Response(ss.str(), username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, false);
}

std::unique_ptr<Command> Examine::clone() const {
    auto examine = std::make_unique<Examine>(this->characterController, this->roomController, this->objectController,
                                             this->username, this->target);
    examine->setInteractions(this->interactions);
    return std::move(examine);
}

std::unique_ptr<Command> Examine::clone(Name username, Input target, Connection connection) const {
    auto examine = std::make_unique<Examine>(this->characterController, this->roomController, this->objectController,
                                             username, target);
    examine->setInteractions(this->interactions);
    return std::move(examine);
}

void Examine::setInteractions(std::vector<std::string> i) {
    interactions = i;
}

std::string Examine::help() {
    return "/examine [target] - get detailed description of the target.";
}

std::pair<std::vector<Response>, bool> Help::execute() {
    const auto commands = commandHandler->getAllCommands();
    std::ostringstream os;
    os << "Commands: \n";
    for(const auto& command : commands) {
        os << command->help() << "\n";
    }

    Response userResponse = Response(os.str(), username);

    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Help::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto help = std::make_unique<Help>(this->characterController, this->commandHandler, username, input);
    return std::move(help);
}

std::unique_ptr<Command> Help::clone() const {
    auto help = std::make_unique<Help>(this->characterController, this->commandHandler, this->username, this->input);
    return std::move(help);
}

std::string Help::help() {
    return "/help - 911 what is your emergency?";
}

// Move
std::pair<std::vector<Response>, bool> Move::execute() {

    std::cout << "Move: " << direction << std::endl;

    ID roomId = characterController->getCharacterRoomID(username);
    ID toID = roomController->getDoorDesignatedRoomId(roomId, direction);

    std::cout << "designated Room: "<<toID << std::endl;


    // check if door exists
    if (toID == Door::unfoundDoorId){
        Response userResponse = Response("Door does not exist!", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res ,true);
    }


    // Verify if door is locked
    if( roomController->getDoorStatus(roomId, direction) == Door::LOCKED){
        Response userResponse = Response("Door is locked!", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res ,true);
    }
    // list of users to notify that character moved north
    std::vector<std::string> userList = roomController->getCharacterList(characterController->getCharacterRoomID(username));

    Name charName = characterController->getCharName(username);
    // Update roomList to account for character moving
    roomController->removeCharacterFromRoom(charName, roomId);
    roomController->addCharacterToRoom(charName, toID);
    characterController->setCharacterRoomID(username, toID);

    // send message to the moving user and another message to users in the room
    Response userResponse = Response("Headed " + direction, username);
    std::string genericMessage = charName + " headed " + direction;

    std::string enteringMessage = charName + " entered the room";

    Response empty = Response();
    std::vector<std::string> characterList = roomController->getCharacterList(characterController->getCharacterRoomID(username));
    removeTargets(characterList, username);

    auto res = formulateResponse(userResponse, userList, genericMessage);
    auto resModified = formulateResponse(empty, characterList, enteringMessage);
    res.insert(res.end(), resModified.begin(), resModified.end());
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Move::clone() const {
    auto move = std::make_unique<Move>(this->characterController, this->roomController, this->username, this->direction);
    return std::move(move);
}

std::unique_ptr<Command> Move::clone(Name username, Input direction, Connection connection) const {
    auto move = std::make_unique<Move>(this->characterController, this->roomController, username, direction);
    return std::move(move);
}

std::string Move::help() {
    return "/move [direction] - move to the target direction";
}

void Move::removeTargets(std::vector<std::string> &characterList, Name username) {
    characterList.erase(
            std::remove_if(characterList.begin(), characterList.end(),
                           [username](const std::string &character) { return (character == username); }),
            characterList.end());
}

//Info
std::pair<std::vector<Response>, bool> Info::execute() {
    Response userResponse = Response(characterController->getCharacterInfo(username), username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Info::clone() const {
    auto info = std::make_unique<Info>(this->characterController, this->username, this->input);
    return std::move(info);
}

std::unique_ptr<Command> Info::clone(Name username, Input input, Connection connection) const {
    auto info = std::make_unique<Info>(this->characterController, username, input);
    return std::move(info);
}

std::string Info::help() {
    return "/info - Get character details";
}

//Wear
std::pair<std::vector<Response>, bool> Wear::execute() {

    std::vector<std::string> inputStrings = utility::popFront(input);

    // Check if user specifies an interaction
    if ((inputStrings.at(CHECK_INTERACT) == "interact") && !(interactions.empty())) {
        return this->interact();
    }

    Name objectName = input;

    // Validate user input format
    if (objectName.empty()) {
        Response userResponse = Response("You must provide the name of the object you would like to wear", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Error checking for state before wear
    if (!characterController->characterHasItem(username, objectName)) {
        Response userResponse = Response(objectName + " is not in your inventory", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Check for multiple objects of the same name
    std::vector<Object> objectsOfName = characterController->getItemsFromCharacterInventory(username, objectName);

    if (objectsOfName.size() > MULTIPLE_ITEMS) {

        interactions = objectsOfName;

        std::stringstream ss;

        ss << "You have more than 1 item named " << objectName << ". Which item would you like to wear?\n";

        int counter = 0;
        for (auto &obj : interactions) {
            ss << "\t" << ++counter << ". " << obj.getName() << ", ID: " << obj.getID() << "\n";
        }

        Response userResponse = Response(ss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    ID objectID = characterController->getItemIDFromCharacterInventory(username, objectName);

    // Wear item (drops item from inventory)
    characterController->characterWearItem(username, objectID);
    interactions.clear();

    // Error checking for state after wear
    if (characterController->characterHasItem(username, objectID) || !characterController->characterIsWearingItem(username, objectID)) {
        Response userResponse = Response("Wearing item has failed.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Generate success response
    Response userResponse = Response("You are now wearing " + objectName, username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Wear::interact() {

    std::vector<std::string> v = utility::tokenizeString(input);

    if ( v.size() != 2 ) {
        Response userResponse = Response("Please enter /wear interact {index number of the item you want to wear}.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    std::stringstream ss{v.at(INTERACT_CHOICE)};
    int index = -1;
    ss >> index;
    index--;
    if ( index >= interactions.size() || index < 0 ) {
        Response userResponse = Response("Please enter /wear interact {index number of the item you want to wear}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    Name objectName = interactions.at(index).getName();
    ID objectID = interactions.at(index).getID();

    // Error checking for state before wear
    if (!characterController->characterHasItem(username, objectID)) {
        Response userResponse = Response(objectName + "is not in your inventory", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Wear item (drops item from inventory)
    characterController->characterWearItem(username, objectID);
    interactions.clear();

    // Error checking for state after wear
    if (characterController->characterHasItem(username, objectID) || !characterController->characterIsWearingItem(username, objectID)) {
        Response userResponse = Response("Wearing item has failed.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Generate success response
    Response userResponse = Response("You are now wearing " + objectName, username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Wear::clone() const {
    auto wear = std::make_unique<Wear>(this->characterController, this->username, this->input);
    wear->setInteractions(this->interactions);
    return std::move(wear);
}

std::unique_ptr<Command> Wear::clone(Name username, Input input, Connection connection) const {
    auto wear = std::make_unique<Wear>(this->characterController, username, input);
    wear->setInteractions(this->interactions);
    return std::move(wear);
}

std::string Wear::help() {
    return "/wear [item name] - wear item";
}

void Wear::setInteractions(std::vector<Object> i) {
    interactions = i;
}

//Takeoff
std::pair<std::vector<Response>, bool> Takeoff::execute() {

    std::vector<std::string> inputStrings = utility::popFront(input);

    // Check if user specifies an interaction
    if ((inputStrings.at(CHECK_INTERACT) == "interact") && !(interactions.empty())) {
        return this->interact();
    }

    Name objectName = input;

    // Validate user input format
    if (objectName.empty()) {
        Response userResponse = Response("You must provide the name of the object you would like to take off", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Error checking for state before takeoff
    if (!characterController->characterIsWearingItem(username, objectName)) {
        Response userResponse = Response("You are not wearing " + objectName, username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Check for character wearing multiple objects of the same name
    std::vector<Object> objectsOfName = characterController->getItemsFromCharacterWearing(username, objectName);

    if (objectsOfName.size() > MULTIPLE_ITEMS) {

        interactions = objectsOfName;

        std::stringstream ss;

        ss << "You are wearing more than 1 item named " << objectName << ". Which item would you like to take off?\n";

        int counter = 0;
        for (auto &obj : interactions) {
            ss << "\t" << ++counter << ". " << obj.getName() << ", ID: " << obj.getID() << "\n";
        }

        Response userResponse = Response(ss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    ID objectID = characterController->getItemIDFromCharacterWearing(username, objectName);

    // Drop item from user wear (adds item to inventory)
    characterController->characterRemoveItem(username, objectController->getObjectFromList(objectID));
    interactions.clear();

    // Error checking for state after takeoff
    if (characterController->characterIsWearingItem(username, objectID) || !characterController->characterHasItem(username, objectID)) {
        Response userResponse = Response("Taking off item has failed.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Generate success response
    Response userResponse = Response("You have taken off " + objectName, username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Takeoff::interact() {

    std::vector<std::string> v = utility::tokenizeString(input);

    if ( v.size() != 2) {
        Response userResponse = Response("Please enter /takeoff interact {index number of the item you wish to take off}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    std::stringstream ss{v.at(INTERACT_CHOICE)};
    int index = -1;
    ss >> index;
    index--;
    if ( index >= interactions.size() || index < 0) {
        Response userResponse = Response("Please enter /takeoff interact {index number of the item you wish to take off}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    ID objectID = interactions.at(index).getID();
    Name objectName = interactions.at(index).getName();

    // Error checking for state before takeoff
    if (!characterController->characterIsWearingItem(username, objectName)) {
        Response userResponse = Response("You are not wearing " + objectName, username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Drop item from user wear (adds item to inventory)
    characterController->characterRemoveItem(username, objectController->getObjectFromList(objectID));
    interactions.clear();

    // Error checking for state after takeoff
    if (characterController->characterIsWearingItem(username, objectID) || !characterController->characterHasItem(username, objectID)) {
        Response userResponse = Response("Taking off item has failed.", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    // Generate success response
    Response userResponse = Response("You have taken off " + objectName, username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Takeoff::clone() const {

    auto takeoff = std::make_unique<Takeoff>(this->characterController, this->objectController, this->username, this->input);
    takeoff->setInteractions(interactions);
    return std::move(takeoff);
}

std::unique_ptr<Command> Takeoff::clone(Name username, Input input, Connection connection) const {

    auto takeoff = std::make_unique<Takeoff>(this->characterController, this->objectController, username, input);
    takeoff->setInteractions(interactions);
    return std::move(takeoff);
}

std::string Takeoff::help() {
    return "/takeoff [item name] - take off item";
}

void Takeoff::setInteractions(std::vector<Object> i) {
    interactions = i;
}
