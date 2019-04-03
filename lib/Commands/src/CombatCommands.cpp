#include <CombatCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <Server.h>
#include <boost/algorithm/string.hpp>
#include <regex>
#include <algorithm>    // std::random_shuffle

using networking::Connection;
using AlterSpace::ID;
static const std::string CHARACTER_SEPARATOR = " ";

//if user types /examineCombat then print all characters in the room
//else print the names the user has entered
std::pair<std::vector<Response>, bool> CombatExamine::execute() {

    std::cout << "1. target: " << target << std::endl;
    std::vector<std::string> inputStrings = utility::popFront(target);
    //std::cout << "2. target: " << inputStrings.at(0) << std::endl;
    if((inputStrings.at(CHECK_INTERACT) == "interact") && !(interactions.empty())) {
        return this->interact();
    }

    std::stringstream ss;
    ID roomId = characterController->getCharacterRoomID(username);

    auto characterList = roomController->getCharacterList(roomId);
  
    std::string line = "---------------------------\n";

    ss << line;
    std::vector<Character> ce;
    std::vector<Name> npcNames;
    std::cout << "2. target: " << target << std::endl;
    // with no argument
    if (target.empty()){
         std::cout << "no target\n";

        for (auto &characterName : characterList){
    
            if (!characterController->doesCharacterExist(characterName) && !characterController->getUsernamesOfCharacter(characterName).empty()) {
                       std::cout << "in  if\n";
               npcNames = characterController->getUsernamesOfCharacter(characterName);

                std::cout << npcNames.size() << std::endl;

                for (auto npcName = npcNames.begin(); npcName != npcNames.end(); ) {
               
                        if (characterController->getCharacterRoomID(*npcName) != roomId) {
                           
                            npcName = npcNames.erase(npcName);
                        } else {
                     
                            ++npcName;
                        }

                }
            } else {
                    ce.push_back(characterController->getCharacter(characterName));
                std::cout << "in else\n";
            }
        }

        for (auto &character:  ce) {
            Name n = character.getName();
            ss << characterController->getCharacter(n).examineCombat();
            ss << "\n";
        }

       for (auto &character:  npcNames) {
            std::cout << "npc: " << character << std::endl;
            ss << characterController->getCharacter(character).examineCombat();
            ss << "\n";
        }

        Response userResponse = Response(ss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);

    }

    //specific target
  std::cout << "specific target\n";

        for (auto &characterName : characterList){

             if (characterName == target) {
    
            if (!characterController->doesCharacterExist(characterName) && !characterController->getUsernamesOfCharacter(characterName).empty()) {
                       std::cout << "in  if\n";
               npcNames = characterController->getUsernamesOfCharacter(characterName);

                std::cout << npcNames.size() << std::endl;

                for (auto npcName = npcNames.begin(); npcName != npcNames.end(); ) {
               
                        if (characterController->getCharacterRoomID(*npcName) != roomId) {
                           
                            npcName = npcNames.erase(npcName);
                        } else {
                     
                            ++npcName;
                        }

                }
            } else {
                    ce.push_back(characterController->getCharacter(characterName));
                std::cout << "in else\n";
            }
        }
    }

        for (auto &character:  ce) {
            Name n = character.getName();
            ss << characterController->getCharacter(n).examineCombat();
            ss << "\n";
        }

       for (auto &character:  npcNames) {
            std::cout << "npc: " << character << std::endl;
            ss << characterController->getCharacter(character).examineCombat();
            ss << "\n";
        }

        Response userResponse = Response(ss.str(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);

    


}



std::pair<std::vector<Response>, bool> CombatExamine::interact() {
    std::cout << "look interacting" << std::endl;

    std::vector<std::string> v = utility::tokenizeString(target);

    if ( v.size() != 2 ) {
        std::cout << "Too many arguments..." << std::endl;
        Response userResponse = Response("Please enter /look interact {index number of the npc you wish to look at}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    std::stringstream ss{v.at(INTERACT_CHOICE)};
    int index = -1;
    ss >> index;
    index--;

    if ( index >= interactions.size() || index < 0 ) {
        Response userResponse = Response("Please enter /look interact {index number of the npc you wish to look at}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

    Name npcKey = interactions.at(index);

    ss.clear();
    ss << characterController->getCharName(npcKey) << "\n" <<characterController->lookCharacter(npcKey) << "\n";

    Response userResponse = Response(ss.str(), username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

void CombatExamine::setInteractions(std::vector<std::string> i) {
    interactions = i;
}

std::unique_ptr<Command> CombatExamine::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<CombatExamine>(this->characterController, this->roomController,
                                           this->combatController, username, input, connection);
}

std::unique_ptr<Command> CombatExamine::clone() const {
    return std::make_unique<CombatExamine>(this->characterController, this->roomController,
                                           this->combatController, this->username, this->target,
                                           this->connection);
}

std::string CombatExamine::help() {
    return "/combat: Displays combat information for all players in room.\n"
           "/combat [target]: Displays combat information for [name].";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<std::vector<Response>, bool> CombatAttack::execute() {

std::cout << "combat execute "  << std::endl;
std::cout << "input "  << targetInput<< std::endl;
std::vector<std::string> inputStrings = utility::popFront(targetInput);
for(auto&temp : inputStrings){
    std::cout << "is: " << temp << std::endl;
}
std::cout << "interact string: " << inputStrings.at(CHECK_INTERACT) << std::endl;
    if((inputStrings.at(0) == "interact")) { //todo ad the empty part 
        std::cout << " calling interact\n";
        return this->interact();
    }


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
                characterController->toggleCharacterCombat(username);
                Response userResponse = Response(combatController->sendTargetOfflineMsg() + results, username);
                auto res = formulateResponse(userResponse);
                return std::make_pair(res, true);
            }
        }
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

  //  if (roomController->isTargetInRoom(username, character.getRoomID(), targetName)) {
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

            if (combatController->isGameOver(username)) {
                combatController->deleteBattle(username, targetName);
                characterController->toggleCharacterCombat(username, targetName);
                this->registerCallback = false;
            }

            Response userResponse = Response(combatResults, username);
            Response targetResponse = Response(combatResults, targetName);
            auto res = formulateResponse(userResponse, targetResponse);
            return std::make_pair(res, true);
        }

        //this is a new request
        if (combatController->isNewBattle(username, targetName)) {
               std::stringstream ss;
                ID roomId = characterController->getCharacterRoomID(username);

                auto characterList = roomController->getCharacterList(roomId);
              
                std::string line = "---------------------------\n";

                ss << line;
                std::vector<Name> ce;
                std::vector<Name> npcNames;
            std::cout << "new battle with: " << targetInput << std::endl;

                int index = 1;
                    // search character
            for (auto &characterName : characterList) {

                if (characterName == targetInput) {
                        npcAttack = targetInput;
                        std::cout << "set npcAttack to " << npcAttack << std::endl;
                
                   // std::cout << " add to interactions\n";
                interactions.push_back(characterName);
                    if (!characterController->doesCharacterExist(characterName) && !characterController->getUsernamesOfCharacter(characterName).empty()) {
                        std::vector<Name> npcNames = characterController->getUsernamesOfCharacter(characterName);
                        for(auto& name : npcNames) {
                            //std::cout << "list: " << name << std::endl;
                        }
                        std::cout << npcNames.size() << std::endl;

                        for (auto npcName = npcNames.begin(); npcName != npcNames.end(); ) {
                            std::cout << *npcName << std::endl;
                            if (characterController->getCharacterRoomID(*npcName) != roomId) {
                              //  std::cout << "Erasing: " << *npcName << std::endl;
                                npcName = npcNames.erase(npcName);
                            }
                            else {
                                ++npcName;
                            }
                        }

                        if (npcNames.size() > 1) {
                           // std::cout << "more than 1" << std::endl;
                            interactions = npcNames;
                            std::stringstream ss;

                            ss << "There is more than 1 NPC named " << targetInput << ". Which NPC would you like to look at?\n";

                            int counter = 0;
                            for (auto &name : interactions) {
                                ss << "\t" << ++counter << ". " << targetInput << "- " << characterController->getCharacter(name).examineCombat() << "\n";
                            }

                            Response userResponse = Response(ss.str(), username);
                            auto res = formulateResponse(userResponse);
                            return std::make_pair(res, false);
                        } else if (npcNames.size() == 1) {
                            std::cout << "Help" << std::endl;
                            characterName = npcNames.front();
                            std::cout << "Help" << std::endl;
                            std::cout << characterName << std::endl;
                            std::cout << "Seg fault?" << std::endl;
                        } else {
                            std::cout << "npc list is empty???" << std::endl;
                            continue;
                        }

                    } else {

                          //checks if target is in battle state, and if true no request sent
                                // if (combatController->isBattleState(targetName)) {
                                //     targetName = 
                                //     std::string userOutput = combatController->sendTargetInCombatState(targetName);
                                //     Response userResponse = Response(userOutput, username);
                                //     auto res = formulateResponse(userResponse);
                                //     return std::make_pair(res, true);
                                // }

                                // combatController->createNewBattle(character, targetCharacter);

                                // Response userResponse = Response(toMSG(targetName) + combatController->sendThreatMsg(), username);

                                // std::string targetOutput = combatController->sendRoundBattleRequest(character, targetCharacter);
                                // Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);

                                // auto res = formulateResponse(userResponse, targetResponse);
                                // return std::make_pair(res, true);
        }
                    }
                    ss << index << ". " << characterName << "\n" << characterController->lookCharacter(characterName) << "\n";
                    index += 1;

                }
                Response userResponse = Response("attack npc", username);
                this->registerCallback = false;

                 auto res = formulateResponse(userResponse);
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
                Response userResponse = Response(toMSG(targetName) + combatController->sendBattleStartedMsg(),
                                                 username);
                Response targetResponse = Response(fromMSG(username) + combatController->sendBattleStartedMsg(),
                                                   targetName);
                auto res = formulateResponse(userResponse, targetResponse);
                return std::make_pair(res, true);
            }
        }
    //} else {
        //character is not in the room

    //     commandName += combatController->sendCharacterNotFoundMsg(targetName);
    //     res.emplace_back(commandName, username);
    //     return std::make_pair(res, true);
    // }

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

std::pair<std::vector<Response>, bool> CombatAttack::interact() {
    std::cout << "------look interacting--------" << std::endl;
    // std::cout << "targetInput " << targetInput << std::endl;
        // std::cout << "interaction(0): " <<  interactions.at(0) << std::endl;
    std::vector<std::string> v = utility::tokenizeString(targetInput);

    // for(auto& temp : v){

    //    std::cout << "v: " << temp << std::endl;
    // }

    //  for(auto& temp : interactions){

    //    std::cout << "interaction c: " << temp << std::endl;
    // }


    if ( v.size() != 2 ) {
        std::cout << "Too many arguments..." << std::endl;
        Response userResponse = Response("Please enter /look interact {index number of the npc you wish to look at}.", username);
        auto res = formulateResponse(userResponse);

        return std::make_pair(res, false);
    }

  //  std::cout << "in interact\n";
   // std::cout << "targetInput: " << targetInput << std::endl;
    // if (combatController->isBattleState(targetName)) {
               // std::cout <<"attacking: \n";
 
    std::cout << characterController->getCharacter(username).examineCombat() << std::endl;
  std::cout << "npc attack: " <<  npcAttack << std::endl;
   //  std::cout << "interaction(0): " <<  interactions.at(0) << std::endl;
               // std::cout << characterController->getCharacter(npcAttack).examineCombat() << std::endl;
      
            combatController->createNewBattle(characterController->getCharacter(username), characterController->getCharacter(npcAttack));

           // Response userResponse = Response(toMSG(targetName) + combatController->sendThreatMsg(), username);

            // std::string targetOutput = combatController->sendRoundBattleRequest(character, targetCharacter);
            // Response targetResponse = Response(fromMSG(username) + targetOutput, targetName);

            //auto res = formulateResponse(userResponse, targetResponse);
           // return std::make_pair(res, true);
    //    }
    // std::stringstream ss{v.at(1)};
    // int index = -1;
    // ss >> index;
    // index--;
    // std::cout << "index: "<< index << " >=  interactions size: " << interactions.size() << std::endl;
    // if ( index >= interactions.size() || index < 0 ) {
    //     Response userResponse = Response("Please enter /look interact {index number of the npc you wish to look at}.", username);
    //     auto res = formulateResponse(userResponse);

    //     return std::make_pair(res, false);
    // }

    std::cout << "============end interaction===============\n";

    // Name npcKey = npcAttack;

    // ss.clear();
    // ss << characterController->getCharName(npcKey) << "\n" <<characterController->lookCharacter(npcKey) << "\n";

    Response userResponse = Response("end", username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

void CombatAttack::setInteractions(std::vector<std::string> i, Name npcAttack) {
    interactions = i;
    this->npcAttack = npcAttack;
}



std::unique_ptr<Command>
CombatAttack::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto att  = std::make_unique<CombatAttack>(this->characterController, this->roomController,
                                          this->combatController, username, input, connection);
att->setInteractions(this->interactions,npcAttack);
return std::move(att);

}

std::unique_ptr<Command> CombatAttack::clone() const {
    auto att = std::make_unique<CombatAttack>(this->characterController, this->roomController,
                                          this->combatController, this->username, this->targetInput,
                                          this->connection);

    att->setInteractions(this->interactions,npcAttack);
return std::move(att);
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

        characterController->toggleCharacterCombat(username, targetName);
        this->registerCallback = false;

        ID roomId = character.getRoomID();
        std::vector<std::string> directions{"north", "east", "south", "west", "up", "down"};
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
