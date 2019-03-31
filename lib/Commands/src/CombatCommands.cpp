#include <CombatCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <Server.h>
#include <boost/algorithm/string.hpp>
#include <regex>
#include <algorithm>    // std::random_shuffle

//todo bug with flee then /combat


using networking::Connection;
using AlterSpace::ID;
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
std::pair<std::vector<Response>, bool> CombatAttack::execute() {
    std::cout << "combat attack\n";
    std::vector<Response> res;

    //check if a fighter has logged out
    if (combatController->isTargetLogoutState(username)) {

        if (!(characterController->doesCharacterExist(username))) {
            Name targetName = combatController->getTargetName(username);
            std::string results = combatController->logout(username);
            combatController->deleteBattle(username, targetName);
            this->registerCallback = false;
            //check if other user logged out just after you
            if ((characterController->doesCharacterExist(targetName))) {
                characterController->toggleCharacterCombat(targetName);
                Response userResponse = Response("target is offline:\n" + results, targetName);
                auto res = formulateResponse(userResponse);
                return std::make_pair(res, true);
            }
        } else {
            Name targetName = combatController->getTargetName(username);
            std::string results = combatController->logout(targetName);
            combatController->deleteBattle(username, targetName);
            this->registerCallback = false;
            //check if other user logged out just after you
            if ((characterController->doesCharacterExist(username))) {
                characterController->toggleCharacterCombat(username);
                Response userResponse = Response("target is offline:\n" + results, username);
                auto res = formulateResponse(userResponse);
                return std::make_pair(res, true);
            }
        }
        return std::make_pair(res, true);
    }

    Character character = characterController->getCharacter(username);

    std::string commandName = "attack: \n";

    removeExtraWhiteSpaces(targetInput);
    Name targetName = targetInput;

    //check character is attacking himself
    if (character.getName() == targetInput) {
        std::string userOutput = combatController->selfAttackMsg();
        Response userResponse = Response(commandName + userOutput, username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    //check if a fighter fled
    if (combatController->isFleeState(username)) {
        combatController->deleteBattle(username, targetName);
        this->registerCallback = false;
        return std::make_pair(res, true);
    }

    if (roomController->isTargetInRoom(username, character.getRoomID(), targetName)) {
        Character targetCharacter = characterController->getCharacter(targetName);

        //check if user is in battle state
        if (combatController->isBattleState(username)) {
            Name targetName = combatController->getTargetName(username);
            Character targetCharacter = characterController->getCharacter(targetName);

            std::string combatResults = combatController->executeBattleRound(character, targetCharacter, targetInput);

            Character &fighter1 = combatController->getFighter(username);
            Name fighterName1 = fighter1.getName();
            characterController->setCharacterHP(fighterName1, fighter1.getCurrentHP());

            Character &fighter2 = combatController->getFighter(targetName);
            Name fighterName2 = fighter2.getName();
            characterController->setCharacterHP(fighterName2, fighter2.getCurrentHP());

            if (combatController->isGameOver(username)) {
                combatController->deleteBattle(username, targetName);
                characterController->toggleCharacterCombat(username, targetName);
                this->registerCallback = false;
            }

            std::string combatOutput = combatController->sendOwnerFightingMsg(targetName) + combatResults;
            Response userResponse = Response(toMSG(targetName) + combatOutput, username);

            std::string targetOutput = combatController->sendTargetFightingMsg(username) + combatResults;
            Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);

            auto res = formulateResponse(userResponse, targetResponse);
            return
                    std::make_pair(res, true);
        }

        //this is a new request
        if (combatController->isNewBattle(username, targetName)) {

            //checks if target is in battle state, and if true no request sent
            if (combatController->isBattleState(targetName)) {
                std::string userOutput = combatController->sendTargetInCombatState(targetName);
                Response userResponse = Response(userOutput, username);
                auto res = formulateResponse(userResponse);
                return std::make_pair(res, true);
            }

            combatController->createNewBattle(character, targetCharacter);

            Response userResponse = Response(toMSG(targetName) + combatController->sendThreatMsg(), username);

            std::string targetOutput = combatController->sendRoundBattleRequest(character, targetCharacter);
            Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);

            auto res = formulateResponse(userResponse, targetResponse);
            return std::make_pair(res, true);
        }

        //check if character is sending duplicate attack requests
        if (combatController->checkDuplicateSendRequest(username, targetName)) {
            Response userResponse = Response(combatController->sendDuplicateRequestMsg(targetName), username);
            auto res = formulateResponse(userResponse);
            return std::make_pair(res, true);
        }

        //check if character is replying to attack request
        if (combatController->replyPendingRequest(username, targetName)) {
            combatController->setCombatState(targetName, username);
            characterController->toggleCharacterCombat(username, targetName);
            this->registerCallback = true;
            this->callbackAfterHeartbeats = ROUND_DURATION;

            //check if battle is ready, and if true start battle
            if (combatController->battleReady(username, targetName)) {
                Response userResponse = Response(toMSG(targetName) + "battle started", username);
                Response targetResponse = Response(fromMSG(username) + "battle started", targetName);
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

std::pair<std::vector<Response>, bool> CombatAttack::callback() {
    auto res = this->execute();

    if (combatController->isBattleState(username)) {
        this->registerCallback = true;
    }

    return std::make_pair(res.first, false);
}

std::unique_ptr<Command>
CombatAttack::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatAttack>(this->characterController, this->roomController,
                                          this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatAttack::clone() const {
    return std::make_unique<CombatAttack>(this->characterController, this->roomController,
                                          this->combatController, this->username, this->targetInput,
                                          this->connection);
}

std::string CombatAttack::help() {
    return "/attack [name] - Send battle request with rounds to [name] or accept if sent a request.";
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<std::vector<Response>, bool> CombatFlee::execute() {
    Character character = characterController->getCharacter(username);

    if (combatController->isBattleState(username)) {
        Name targetName = combatController->getTargetName(username);
        Character targetCharacter = characterController->getCharacter(targetName);
        combatController->setFleeState(username);
        std::string results = combatController->flee(character, targetCharacter, "");

        characterController->toggleCharacterCombat(username, targetName);
        this->registerCallback = false;

        ID roomId = character.getRoomID();
        std::vector<std::string> directions{"north", "east", "south", "west"};
        std::random_shuffle(directions.begin(), directions.end());

        for (auto &direction: directions) {
            ID toID = roomController->getDoorDesignatedRoomId(roomId, direction);
            if (toID != Door::unfoundDoorId) {
                if (roomController->getDoorStatus(roomId, direction) != Door::LOCKED) {
                    std::vector<std::string> userList = roomController->getCharacterList(
                            characterController->getCharacterRoomID(username));
                    // Update roomList to account for character moving
                    roomController->removeCharacterFromRoom(username, roomId);
                    roomController->removeCharacterFromRoom(username, toID);
                    characterController->setCharacterRoomID(username, toID);

                    std::vector<std::string> characterList = roomController->getCharacterList(characterController->getCharacterRoomID(username));
                    removeTargets(characterList, username);

                    Response userResponse = Response("you have fled " + direction + "\n" + results, username);
                    Response targetResponse = Response("target has fled:\n" + results, targetName);
                    auto res = formulateResponse(userResponse, targetResponse);
                    return std::make_pair(res, true);
                }
            }
        }

        Response userResponse = Response("you have fled:\n" + results, username);
        Response targetResponse = Response("target has fled:\n" + results, targetName);
        auto res = formulateResponse(userResponse, targetResponse);
        return std::make_pair(res, true);
    } else {
        Response userResponse = Response("you are not in battle:", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }
}

std::unique_ptr<Command> CombatFlee::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatFlee>(this->characterController, this->roomController,
                                        this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatFlee::clone() const {
    return std::make_unique<CombatFlee>(this->characterController, this->roomController,
                                        this->combatController, this->username, this->input,
                                        this->connection);
}

std::string CombatFlee::help() {
    return "/flee - escape from a battle and move to a random neighboring room";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Helper functions:

void removeExtraWhiteSpaces(Input &input) {
    input = std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1");
}

void getCharactersInCurrentRoom(RoomController *roomCtrl, CharacterController *characterCtrl,
                                Character player,
                                std::vector<Character> &charactersInRoom) {

    Name name = player.getName();
    for (auto name: roomCtrl->getCharacterList(characterCtrl->getCharacterRoomID(name))) {
        charactersInRoom.push_back(characterCtrl->getCharacter(name));
    }
}

std::string toMSG(const Name &name) {
    return "To [" + name + "]: ";
}

std::string fromMSG(const Name &name) {
    return "From [" + name + "]: ";
}


void removeTargets(std::vector<std::string> &characterList, Name username) {
    characterList.erase(
            std::remove_if(characterList.begin(), characterList.end(),
                           [username](const std::string &character) { return (character == username); }),
            characterList.end());
}
