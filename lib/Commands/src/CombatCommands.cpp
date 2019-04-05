#include <CombatCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <Server.h>
#include <boost/algorithm/string.hpp>
#include <regex>
#include <algorithm>

using networking::Connection;
using AlterSpace::ID;

bool CombatAttack::isCharacterNPCS() {
    ID roomId = characterController->getCharacterRoomID(username);
    auto characterList = roomController->getCharacterList(roomId);
    std::vector<Name> npcs;

    characterList.erase(unique(characterList.begin(), characterList.end()), characterList.end());

    for (auto &characterName : characterList) {
        if (characterName == targetInput) {
            if (!characterController->doesCharacterExist(characterName) &&
                !characterController->getUsernamesOfCharacter(characterName).empty()) {
                npcs = characterController->getUsernamesOfCharacter(characterName);

                for (auto npcName = npcs.begin(); npcName != npcs.end();) {
                    if (characterController->getCharacterRoomID(*npcName) == roomId) {
                        npcName = npcs.erase(npcName);
                        return true;
                    } else {
                        ++npcName;
                    }
                }
            }
        }
    }
    return false;
}

//if user types /examineCombat then print all characters in the room
//else print the name the user has entered
std::pair<std::vector<Response>, bool> CombatExamine::execute() {
    std::stringstream ss;
    ID roomId = characterController->getCharacterRoomID(username);

    auto characterList = roomController->getCharacterList(roomId);
    std::vector<Character> toExamineUsers;
    std::vector<std::vector<Name>> toExamineNPCS;
    std::vector<Name> npcs;
    bool isSpecificTarget = !input.empty();

    characterList.erase(unique(characterList.begin(), characterList.end()), characterList.end());

    for (auto &characterName : characterList) {
        if (!characterController->doesCharacterExist(characterName) &&
            !characterController->getUsernamesOfCharacter(characterName).empty()) {
            npcs = characterController->getUsernamesOfCharacter(characterName);

            for (auto npcName = npcs.begin(); npcName != npcs.end();) {
                if (characterController->getCharacterRoomID(*npcName) != roomId) {
                    npcName = npcs.erase(npcName);
                } else {
                    ++npcName;
                }
            }
            toExamineNPCS.push_back(npcs);
        } else {
            toExamineUsers.push_back(characterController->getCharacter(characterName));
        }
    }

    for (auto &character:  toExamineUsers) {
        Name name = character.getName();

        if (isSpecificTarget) {
            if (name == input) {
                ss << characterController->getCharacter(name).examineCombat();
                ss << "\n";
            }
        } else {
            ss << characterController->getCharacter(name).examineCombat();
            ss << "\n";
        }
    }
    for (auto &ex:  toExamineNPCS) {
        for (auto &character:  ex) {
            Name name = characterController->getCharacter(character).getName();
            if (isSpecificTarget) {
                if (name == input) {
                    ss << characterController->getCharacter(character).examineCombat();
                    ss << "\n";
                }
            } else {
                ss << characterController->getCharacter(character).examineCombat();
                ss << "\n";
            }
        }
    }

    if (ss.str().empty()) {
        ss << "\tCharacter " << input << " not found";
    }

    Response userResponse = Response("Combat Examine:\n" + ss.str(), username);
    auto res = formulateResponse(userResponse);
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
           "/combat [target]: Displays combat information for [target].";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<std::vector<Response>, bool> CombatAttack::execute() {
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
                characterController->setCharacterCombat(targetName, false);
                Response userResponse = Response(combatController->sendTargetOfflineMsg() + results, targetName);
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
                characterController->setCharacterCombat(username, false);
                Response userResponse = Response(combatController->sendTargetOfflineMsg() + results, username);
                auto res = formulateResponse(userResponse);
                return std::make_pair(res, true);
            }
        }
        return std::make_pair(res, true);
    }

    // check if npc
    if (isCharacterNPCS()) {
        Response userResponse = Response("npcs not available", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    Character &character = characterController->getCharacter(username);

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
        Character &targetCharacter = characterController->getCharacter(targetName);

        //check if user is in battle state
        if (combatController->isBattleState(username)) {
            Name targetName = combatController->getTargetName(username);
            Character &targetCharacter = characterController->getCharacter(targetName);

            std::string combatResults = combatController->executeBattleRound(character, targetCharacter, targetInput);

            Character &fighter1 = combatController->getFighter(username);
            Name fighterName1 = fighter1.getName();
            characterController->setCharacterHP(fighterName1, fighter1.getCurrentHP());

            Character &fighter2 = combatController->getFighter(targetName);
            Name fighterName2 = fighter2.getName();
            characterController->setCharacterHP(fighterName2, fighter2.getCurrentHP());

            if (combatController->isBattleOver(username)) {
                combatController->deleteBattle(username, targetName);
                characterController->setCharacterCombat(username, targetName, false);
                this->registerCallback = false;
            }

            Response userResponse = Response(combatResults, username);
            Response targetResponse = Response(combatResults, targetName);
            auto res = formulateResponse(userResponse, targetResponse);
            return std::make_pair(res, true);
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
        if (combatController->replyBattleRequest(username, targetName)) {
            combatController->setCombatState(targetName, username);
            characterController->setCharacterCombat(username, targetName, true);
            this->registerCallback = true;
            this->callbackAfterHeartbeats = ROUND_DURATION;

            //check if battle is ready, and if true start battle
            if (combatController->battleReady(username, targetName)) {
                Response userResponse = Response(toMSG(targetName) + combatController->sendBattleStartedMsg(),
                                                 username);
                Response targetResponse = Response(fromMSG(username) + combatController->sendBattleStartedMsg(),
                                                   targetName);
                auto res = formulateResponse(userResponse, targetResponse);
                return std::make_pair(res, true);
            }
        }
    } else {
        //character is not in the room
        commandName += combatController->sendCharacterNotFoundMsg(targetName);
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
    return "/attack [target] - Send battle request with rounds to [name] or accept if sent a request.";
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
    Character &character = characterController->getCharacter(username);

    if (combatController->isBattleState(username)) {
        Name targetName = combatController->getTargetName(username);
        Character &targetCharacter = characterController->getCharacter(targetName);
        combatController->setFleeState(username);
        std::string results = combatController->flee(character, targetCharacter, "");

        characterController->setCharacterCombat(username, targetName, false);
        this->registerCallback = false;

        ID roomId = character.getRoomID();
        std::vector<std::string> directions{"north", "east", "south", "west", "up", "down", "northeast", "southeast",
                                            "northwest", "southwest"};
        std::random_shuffle(directions.begin(), directions.end());

        for (auto &direction: directions) {
            ID toID = roomController->getDoorDesignatedRoomId(roomId, direction);
            if (toID != Door::unfoundDoorId) {
                if (roomController->getDoorStatus(roomId, direction) != Door::LOCKED) {
                    std::vector<std::string> userList = roomController->getCharacterList(
                            characterController->getCharacterRoomID(username));
                    // Update roomList to account for character moving
                    roomController->removeCharacterFromRoom(username, roomId);
                    roomController->addCharacterToRoom(username, toID);
                    characterController->setCharacterRoomID(username, toID);

                    std::vector<std::string> characterList = roomController->getCharacterList(
                            characterController->getCharacterRoomID(username));
                    removeTargets(characterList, username);

                    Response userResponse = Response(combatController->sendYouFledMsg(direction) + results, username);
                    Response targetResponse = Response(combatController->sendTargetFledMsg() + results, targetName);
                    auto res = formulateResponse(userResponse, targetResponse);
                    return std::make_pair(res, true);
                }
            }
        }

        Response userResponse = Response(combatController->sendYouFledMsg("") + results, username);
        Response targetResponse = Response(combatController->sendTargetFledMsg() + results, targetName);
        auto res = formulateResponse(userResponse, targetResponse);
        return std::make_pair(res, true);
    } else {
        Response userResponse = Response(combatController->sendNotInBattleMsg(), username);
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
