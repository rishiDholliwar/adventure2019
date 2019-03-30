#include <CombatCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <Server.h>
#include <boost/algorithm/string.hpp>
#include <regex>


//todo bug with /move

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
    Character character = characterController->getCharacter(username);
    std::vector<Response> res;

    removeExtraWhiteSpaces(input);
    Name targetName = input;

    std::string commandName = "attack: \n";

    //checking flee
    //TODO add another state in combat for flee?



    //check if user is in battle state
    if (combatController->isBattleState(username)) {

        //TODO refactor 
        Name tn =  combatController->getTargetName(username);
        if(combatController->isFlee(username,tn)){
            Name targetName = combatController->getTargetName(username);
            Character targetCharacter = characterController->getCharacter(targetName);
            combatController->deleteGame(username, targetName);
            characterController->toggleCharacterCombat(username,targetName);
            this->registerCallback = false;
            Response targetResponse = Response("", targetName);

            auto res = formulateResponse(targetResponse);
            return std::make_pair(res, true);
        }



        //todo do check to see if other player is still there and delete the game if they are not
        //checking to make sure input is correct from the user (the user only typed /attack)
       
        Name targetName = combatController->getTargetName(username);
        Character targetCharacter = characterController->getCharacter(targetName);
     
        std::string combatResults = combatController->executeBattleRound(character, targetCharacter, input);

        Character &fighter1 = combatController->getFighter(username);
        Name fighterName1 = fighter1.getName();
        characterController->setCharacterHP(fighterName1, fighter1.getCurrentHP());

        Character &fighter2 = combatController->getFighter(targetName);
        Name fighterName2 = fighter2.getName();
        characterController->setCharacterHP(fighterName2, fighter2.getCurrentHP());

        if (combatController->isGameOver(username)) {
            //todo change back to some other state for the characters
            combatController->deleteGame(username, targetName);
           characterController->toggleCharacterCombat(username,targetName);
            this->registerCallback = false;
        } 

        std::string combatOutput = combatController->sendOwnerFightingMsg(targetName) + combatResults;
        Response userResponse = Response(toMSG(targetName) + combatOutput, username);

        std::string targetOutput = combatController->sendTargetFightingMsg(username) + combatResults;
        Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);

        auto res = formulateResponse(userResponse, targetResponse);
        return std::make_pair(res, true);
    }

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

          //checks if target is in battle state, and if true no request sent
            if (combatController->isBattleState(targetName)) {
                std::string userOutput = combatController->sendTargetInCombatState(targetName);
                Response userResponse = Response(userOutput, username);
                auto res = formulateResponse(userResponse);
                return std::make_pair(res, true);
            }

            std::cout << "new battle\n";
            combatController->createNewBattle(character, targetCharacter);
           // combatController->setFighterReady(username);

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
            combatController->setCombatState(targetName, username);
            characterController->toggleCharacterCombat(username,targetName);
            //characterController->toggleCharacterCombat(targetName);
            this->registerCallback = true;
            this->callbackAfterHeartbeats = ROUND_DURATION;
            //todo now fighters must be in combat state
            //check if battle is ready, and if true start battle
            if (combatController->battleReady(username, targetName)) {
                Response userResponse = Response(
                        toMSG(targetName) + "battle started", username);


                Response targetResponse = Response(
                        fromMSG(username) + "battle started", targetName);

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
    std::cout << "attack callback\n";
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
                                               this->combatController, this->username, this->input,
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
    //TODO i dont think your suppose to be able to use this command when not in combat state
     Character character = characterController->getCharacter(username);



        //PRINT ALL NEIGHBORUING ROOMS 
        std::cout << "Neighbouring rooms\n";
           
        ID roomID = character.getRoomID();
        std::cout << "Current room id: " << roomID << std::endl;

        std::vector<Room> rooms = roomController->getRoomList();
       for(auto&room : rooms){
        //std::cout << room.getName() << std::endl;

       }

            std::cout << "done\n";









    //TODO need to use move command to go ro room after flee  
    if(combatController->isBattleState(username)){
        Name targetName = combatController->getTargetName(username);
        Character targetCharacter = characterController->getCharacter(targetName);
        std::string results = combatController->flee(character,targetCharacter,"");
      //  combatController->deleteGame(username, targetName);
        this->registerCallback = false;

        Response userResponse = Response("you have fled:\n" + results, username);
        Response targetResponse = Response("target has fled:\n" + results, targetName);
        auto res = formulateResponse(userResponse,targetResponse);
        return std::make_pair(res, true);
    } else {
       Response userResponse = Response("you are not in battle:", username);
       auto res = formulateResponse(userResponse);
       return std::make_pair(res, true);
    }

    // Response targetResponse = Response("target has fleed:",
    //                                  username);
 
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
    return "/flee - escape from a battle.";
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


