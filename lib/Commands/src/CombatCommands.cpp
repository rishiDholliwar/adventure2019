#include <CombatCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <Server.h>
#include <boost/algorithm/string.hpp>
#include <regex>
//todo if user is in combat state can they be sent a request or send request??
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
//    Character character = characterController->getCharacter(username);
    std::vector<Response> res;
//
//    removeExtraWhiteSpaces(input);
//    Name targetName = input;
//
//    std::string commandName = "quick attack: \n";
//
//    //character is attacking himself
//    if (character.getName() == targetName) {
//        std::string userOutput = combatController->selfAttackMsg();
//        Response userResponse = Response(commandName + userOutput, username);
//        auto res = formulateResponse(userResponse);
//        return std::make_pair(res, true);
//    }
//
//    if (roomController->isTargetInRoom(username, character.getRoomID(), targetName)) {
//        Character targetCharacter = characterController->getCharacter(targetName);
//        //this is a new request
//        if (combatController->isNewBattle(username, targetName)) {
//            combatController->createNewBattle(character, targetCharacter);
//
//            Response userResponse = Response(toMSG(targetName) + combatController->sendThreatMsg(), username);
//
//            std::string targetOutput = combatController->sendQuickBattleRequest(character, targetCharacter);
//            Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);
//
//            auto res = formulateResponse(userResponse, targetResponse);
//            return std::make_pair(res, true);
//        }
//
//        //see if character is sending duplicate attack requests
//        if (combatController->checkDuplicateSendRequest(username, targetName)) {
//            Response userResponse = Response(combatController->sendDuplicateRequestMsg(targetName), username);
//            auto res = formulateResponse(userResponse);
//            return std::make_pair(res, true);
//        }
//
//        //see if character is replying to attack request
//        if (combatController->replyPendingRequest(username, targetName)) {
//
//            combatController->setCombatState(targetName,username);
//            //check if battle is ready, and if true start battle
//            if (combatController->battleReady(username, targetName)) {
//                std::string combatResults = combatController->executeQuickBattle(character, targetCharacter, input);
//
//                for (auto &fighter: combatController->getFighters(username, targetName)) {
//                    Name name = fighter.getName();
//                    characterController->setCharacterHP(name, fighter.getCurrentHP());
//                }
//
//                if (combatController->isGameOver(username, targetName)) {
//                    combatController->deleteGame(username, targetName);
//                }
//
//                std::string combatOutput = combatController->sendOwnerFightingMsg(targetName) + combatResults;
//                Response userResponse = Response(toMSG(targetName) + combatOutput, username);
//
//                std::string targetOutput = combatController->sendTargetFightingMsg(username) + combatResults;
//                Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);
//
//                auto res = formulateResponse(userResponse, targetResponse);
//                return std::make_pair(res, true);
//            }
//        }
//    } else {
//        //character is not in the room
//        std::string error = "\tCharacter " + targetName + " not found\n";
//        commandName += error;
//        res.emplace_back(commandName, username);
//        return std::make_pair(res, true);
//    }

    res.emplace_back("quick attack error\n", username);
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
std::pair<std::vector<Response>, bool> CombatRoundAttack::execute() {
    Character character = characterController->getCharacter(username);
    std::vector<Response> res;

    removeExtraWhiteSpaces(input);
    Name targetName = input;

    std::string commandName = "attack: \n";


    //target is already in a battle and no battle reqeust sent
    if (combatController->isBattleState(targetName)) {
        std::string userOutput = combatController->sendTargetInCombatState(targetName);
        Response userResponse = Response(userOutput, username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }
///////////////////////////////////battle state begin////////////////////////////////////////////////////////////////////////

    //check if user is in battle state
    if (combatController->isBattleState(username)) {
        //todo do check to see if other player is still there and delete the game if they are not
        std::cout << "---------------------------------" + username + "---------------------------------" << std::endl;
        std::cout << username + " is in battle state\n";

        //checking to make sure input is correct from the user (the user only typed /attack)
        if (combatController->checkInputForNextRound(username, input)) {
            std::cout << "typed /attack" << std::endl;
            Name targetName = combatController->getTargetName(username);
            Character targetCharacter = characterController->getCharacter(targetName);
            std::cout << "Username: " + username + ", opponent: " + targetName << std::endl;
            //todo later, maybe check with a bool so then we can send user message "waiting for other player"
            combatController->setFighterReady(username);
            //todo want to check if we can execute the round (need function in  combat to see if everyone is ready)
            if (combatController->isNextRoundReady(username)) {
                std::cout << "doing next round" << std::endl;

//                std::vector<Character> updateFighters;
//                for (auto &fighterName :  combatController->getOpponents(username)) {
//                    std::cout << "updating: " << fighterName << std::endl;
//                    updateFighters.push_back(characterController->getCharacter(fighterName));
//                }




                std::string combatResults = combatController->executeBattleRound(character, targetCharacter, input);

                std::cout << "got combat results" << std::endl;
                std::cout << "username: " << username << std::endl;
                std::cout << "targName: " << targetName << std::endl;
                Character &fighter1 = combatController->getFighter(username);
                Name fighterName1 = fighter1.getName();
                std::cout << "f1: " << fighterName1 << std::endl;
                characterController->setCharacterHP(fighterName1, fighter1.getCurrentHP());

                Character &fighter2 = combatController->getFighter(targetName);
                Name fighterName2 = fighter2.getName();
                std::cout << "f2: " << fighterName2 << std::endl;
                characterController->setCharacterHP(fighterName2, fighter2.getCurrentHP());


                std::cout << "done set fighters hp" << std::endl;

                if (combatController->isGameOver(username)) {
                    std::cout << "GAME OVER!!!" << std::endl;
                    //todo change back to some other state for the characters
                    combatController->deleteGame(username, targetName);
                } else {
                    combatController->resetRoundReady(username);
                }

                std::string combatOutput = combatController->sendOwnerFightingMsg(targetName) + combatResults;
                Response userResponse = Response(toMSG(targetName) + combatOutput, username);

                std::string targetOutput = combatController->sendTargetFightingMsg(username) + combatResults;
                Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);
                std::cout << "---------------------------------" + username + "---------------------------------"
                          << std::endl << std::endl;

                auto res = formulateResponse(userResponse, targetResponse);
                return std::make_pair(res, true);
            } else {
                std::string userOutput = " waiting for other player";
                Response userResponse = Response(toMSG(targetName) + userOutput, username);

                std::string targetOutput = targetName + " is ready for next round";
                Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);
                std::cout << "---------------------------------" + username + "---------------------------------"
                          << std::endl << std::endl;

                auto res = formulateResponse(userResponse, targetResponse);
                return std::make_pair(res, true);
            }


        }
        std::cout << "---------------------------------" + username + "---------------------------------" << std::endl
                  << std::endl;

        std::string userOutput = "Error: enter '/attack' when ready for next round";
        Response userResponse = Response(userOutput, username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }
///////////////////////////////////battle state end////////////////////////////////////////////////////////////////////////

    //user is already in a battle and cant put in another request
//    if(combatController->isInBattleState(username)){
//        std::string userOutput =  combatController->sendSelfInCombatState();
//        Response userResponse = Response(userOutput, username);
//        auto res = formulateResponse(userResponse);
//        return std::make_pair(res, true);
//    }

    //character is attacking himself
    if (character.getName() == targetName) {
        std::string userOutput = combatController->selfAttackMsg();
        Response userResponse = Response(commandName + userOutput, username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    if (roomController->isTargetInRoom(username, character.getRoomID(), targetName)) {
        Character targetCharacter = characterController->getCharacter(targetName);





        //battle has already been accepted by both people
        if (combatController->isBattleStarted(username, targetName)) {
            std::string combatOutput = combatController->sendOwnerFightingMsg(targetName);
            Response userResponse = Response(toMSG(targetName) + combatOutput, username);

            std::string targetOutput = combatController->sendTargetFightingMsg(username);
            Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);

            auto res = formulateResponse(userResponse, targetResponse);
            return std::make_pair(res, true);
        }


        //this is a new request
        if (combatController->isNewBattle(username, targetName)) {
            std::cout << "username: " << username <<", new battle with: " <<targetName <<  std::endl;
            combatController->createNewBattle(character, targetCharacter);

            Response userResponse = Response(toMSG(targetName) + combatController->sendThreatMsg(), username);

            std::string targetOutput = combatController->sendRoundBattleRequest(character, targetCharacter);
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
            std::cout << username + " reply pending request\n";
            combatController->setCombatState(targetName, username);
            //check if battle is ready, and if true start battle


            //todo now fighters must be in combat state
            if (combatController->battleReady(username, targetName)) {
                Response userResponse = Response(
                        toMSG(targetName) + "battle started.\n Enter '/attack' to start next round ", username);


                Response targetResponse = Response(
                        fromMSG(username) + "battle started.\n Enter '/attack' to start next round ", targetName);

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

std::unique_ptr<Command>
CombatRoundAttack::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatRoundAttack>(this->characterController, this->roomController,
                                               this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatRoundAttack::clone() const {
    return std::make_unique<CombatRoundAttack>(this->characterController, this->roomController,
                                               this->combatController, this->username, this->input,
                                               this->connection);
}

std::string CombatRoundAttack::help() {
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


