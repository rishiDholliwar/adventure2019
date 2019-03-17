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

    std::string output = "examine: \n";

    bool whiteSpacesOnly = std::all_of(input.begin(), input.end(), isspace);
    if (input == "" || whiteSpacesOnly) {

        std::vector<Character> charactersInRoom;
        getCharactersInCurrentRoom(roomController, characterController, characterController->getCharacter(username),
                                   charactersInRoom);
        std::string examineString = "";

        for (auto &character: charactersInRoom) {
            output += character.examineCombat();
            output += "\n";
        }

        res.emplace_back(output + examineString, username);
        return std::make_pair(res, true);
    }

    removeExtraWhiteSpaces(input);

    std::vector<std::string> inputs;
    boost::split(inputs, input, boost::is_any_of(CHARACTER_SEPARATOR));

    //print characters the user has entered
    for (auto &targetName: inputs) {
        if (isCharacterInRoom(roomController, character, targetName)) {
            Character targetCharacter = characterController->getCharacter(targetName);
            output += targetCharacter.examineCombat();
            output += "\n";
        } else {
            std::string error = "\tCharacter " + targetName + " not found\n\n";
            output += error;
        }
    }

    res.emplace_back(output, username);
    return std::make_pair(res, true);

}

std::unique_ptr<Command> CombatExamine::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatExamine>(this->userController, this->characterController, this->roomController,
                                           this->objectController, this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatExamine::clone() const {
    return std::make_unique<CombatExamine>(this->userController, this->characterController, this->roomController,
                                           this->objectController, this->combatController, this->username, this->input,
                                           this->connection);
}

std::string CombatExamine::help() {
    return "/combatExamine look at combat stats";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<std::vector<Response>, bool> CombatAttack::execute() {
    Character character = characterController->getCharacter(username);
    std::vector<Response> res;

    removeExtraWhiteSpaces(input);
    Name targetName = input;
    std::string commandName = "attack: \n";


    //character is attacking himself
    if (character.getName() == targetName) {
        std::string userResponse = combatController->selfAttack();
        res.emplace_back(commandName + userResponse, username);
        return std::make_pair(res, true);
    }

    if (isCharacterInRoom(roomController, character, targetName)) {

        //this is a new request
        if (combatController->isNewBattle(username, targetName)) {
            Character targetCharacter = characterController->getCharacter(targetName);
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
                std::string combatResults = combatController->executeBattle(username, targetName, input);

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


    res.emplace_back(commandName + " error\n", username);
    return std::make_pair(res, true);

}

std::unique_ptr<Command> CombatAttack::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatAttack>(this->userController, this->characterController, this->roomController,
                                          this->objectController, this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatAttack::clone() const {
    return std::make_unique<CombatAttack>(this->userController, this->characterController, this->roomController,
                                          this->objectController, this->combatController, this->username, this->input,
                                          this->connection);
}

std::string CombatAttack::help() {
    return "/combatAttack ";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::pair<std::vector<Response>, bool> CombatBattles::execute() {
    Character character = characterController->getCharacter(username);

    std::string output = "Battles: \n";

    Response userResponse = Response(combatController->printAllBattles(),
                                     username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);


}

std::unique_ptr<Command> CombatBattles::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatBattles>(this->userController, this->characterController, this->roomController,
                                           this->objectController, this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatBattles::clone() const {
    return std::make_unique<CombatBattles>(this->userController, this->characterController, this->roomController,
                                           this->objectController, this->combatController, this->username, this->input,
                                           this->connection);
}

std::string CombatBattles::help() {
    return "/combatExamine look at combat stats";
}

//Helper functions:

void removeExtraWhiteSpaces(Input &input) {
//    boost::trim_right(input);
//    boost::trim_left(input);
//    input.erase(std::remove_if(
//            begin(input), end(input),
//            [l = std::locale{}](auto ch) { return std::isspace(ch, l); }
//    ), end(input));

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

bool isCharacterInRoom(RoomController *rc, Character &instigator, Name target) {
    for (auto &ch : rc->getUsernameList(instigator.getRoomID())) {
        if (ch == target) {
            return true;
        }
    }
    return false;
}

std::string toMSG(const Name &name) {
    return "To [" + name + "]: ";
}

std::string fromMSG(const Name &name) {
    return "From [" + name + "]: ";
}


