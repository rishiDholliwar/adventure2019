#include <CombatCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <Server.h>
#include <boost/algorithm/string.hpp>
#include <regex>

using networking::Connection;

static const std::string CHARACTER_SEPARATOR = " ";

//if user types /examineCombat then print all characters in the room
//else print the names the user has entered
std::pair<std::vector<Response>, bool> CombatExamine::execute() {
    Character character = characterController->getCharacter(username);
    std::vector<Response> res;

    std::stringstream output;
    output << "combat examine: \n";

    bool whiteSpacesOnly = std::all_of(input.begin(), input.end(), isspace);
    if (input == "" || whiteSpacesOnly) {

        std::vector<Character> charactersInRoom;
        getCharactersInCurrentRoom(roomController, characterController, characterController->getCharacter(username),
                                   charactersInRoom);

        for (auto &character: charactersInRoom) {
            output << character.examineCombat();
            output << "\n";
        }

        res.emplace_back(output.str(), username);
        return std::make_pair(res, true);
    }

    removeExtraWhiteSpaces(input);

    std::vector<std::string> inputs;
    boost::split(inputs, input, boost::is_any_of(CHARACTER_SEPARATOR));

    //print characters the user has entered
    for (auto &targetName: inputs) {
        if (roomController->isTargetInRoom(username, character.getRoomID(), targetName)) {
            Character targetCharacter = characterController->getCharacter(targetName);
            output << targetCharacter.examineCombat();
            output << "\n";
        } else {
            std::string error = "\tCharacter " + targetName + " not found\n\n";
            output << error;
        }
    }

    res.emplace_back(output.str(), username);
    return std::make_pair(res, true);

}

std::unique_ptr<Command> CombatExamine::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatExamine>(this->characterController, this->roomController,
                                           this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatExamine::clone() const {
    return std::make_unique<CombatExamine>(this->characterController, this->roomController,
                                           this->combatController, this->username, this->input,
                                           this->connection);
}

std::string CombatExamine::help() {
    return "/combat: Displays combat information for all players in room.\n"
           "/combat [name]: Displays combat information for [name].";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::pair<std::vector<Response>, bool> CombatQAttack::execute() {
    Character character = characterController->getCharacter(username);
    std::vector<Response> res;

    removeExtraWhiteSpaces(input);
    Name targetName = input;

    std::string commandName = "quick attack: \n";

    //character is attacking himself
    if (character.getName() == targetName) {
        std::string userOutput = combatController->selfAttackMsg();
        Response userResponse = Response(commandName + userOutput, username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    if (roomController->isTargetInRoom(username, character.getRoomID(), targetName)) {
        Character targetCharacter = characterController->getCharacter(targetName);
        //this is a new request
        if (combatController->isNewBattle(username, targetName)) {
            combatController->createNewBattle(character, targetCharacter);

            Response userResponse = Response(toMSG(targetName) + combatController->sendThreatMsg(), username);

            std::string targetOutput = combatController->sendBattleRequest(character, targetCharacter);
            Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);

            auto res = formulateResponse(userResponse, targetResponse);
            return std::make_pair(res, true);
        }

        //see if character is sending duplicate attack requests
        if (combatController->checkDuplicateSendRequest(username, targetName)) {
            Response userResponse = Response(combatController->sendDuplicateRequestMsg(targetName), username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, true);
        }

        //see if character is replying to attack request
        if (combatController->replyPendingRequest(username, targetName)) {

            //check if battle is ready, and if true start battle
            if (combatController->battleReady(username, targetName)) {
                std::string combatResults = combatController->executeBattle(character, targetCharacter, input);

                for (auto &fighter: combatController->getFighters(username, targetName)) {
                    Name name = fighter.getName();
                    characterController->setCharacterHP(name, fighter.getCurrentHP());
                }

                if (combatController->isGameOver(username, targetName)) {
                    combatController->deleteGame(username, targetName);
                }

                std::string combatOutput = combatController->sendOwnerFightingMsg(targetName) + combatResults;
                Response userResponse = Response(toMSG(targetName) + combatOutput, username);

                std::string targetOutput = combatController->sendTargetFightingMsg(username) + combatResults;
                Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);

                auto res = formulateResponse(userResponse, targetResponse);
                return std::make_pair(res, true);
            }
        }
    } else {
        //character is not in the room
        std::string error = "\tCharacter " + targetName + " not found\n";
        commandName += error;
        res.emplace_back(commandName, username);
        return std::make_pair(res, true);
    }

    res.emplace_back(commandName + "attack error\n", username);
    return std::make_pair(res, true);

}

std::unique_ptr<Command> CombatQAttack::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatQAttack>(this->characterController, this->roomController,
                                           this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatQAttack::clone() const {
    return std::make_unique<CombatQAttack>(this->characterController, this->roomController,
                                           this->combatController, this->username, this->input,
                                           this->connection);
}

std::string CombatQAttack::help() {
    return "/qAttack [name] - Send battle request without rounds to [name] or accept if sent a request.";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::pair<std::vector<Response>, bool> CombatBattles::execute() {
    Character character = characterController->getCharacter(username);

    std::string output = "Battles: \n";

    Response userResponse = Response(combatController->printAllBattles(),
                                     username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> CombatBattles::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatBattles>(this->characterController, this->roomController,
                                           this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatBattles::clone() const {
    return std::make_unique<CombatBattles>(this->characterController, this->roomController,
                                           this->combatController, this->username, this->input,
                                           this->connection);
}

std::string CombatBattles::help() {
    return "/battles - See list of pending battles.";
}

//Helper functions:

void removeExtraWhiteSpaces(Input &input) {
    input = std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1");
}

void getCharactersInCurrentRoom(RoomController *roomCtrl, CharacterController *characterCtrl,
                                Character player,
                                std::vector<Character> &charactersInRoom) {

    Name name = player.getName();
    for (auto name: roomCtrl->getUsernameList(characterCtrl->getCharacterRoomID(name))) {
        charactersInRoom.push_back(characterCtrl->getCharacter(name));
    }
}

std::string toMSG(const Name &name) {
    return "To [" + name + "]: ";
}

std::string fromMSG(const Name &name) {
    return "From [" + name + "]: ";
}


