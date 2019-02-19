#include <iostream>
#include <CharacterController.h>
#include "../../World/include/RoomController.h"

CharacterController::CharacterController() = default;



bool CharacterController::addToOnlineUsers(std::string &username, RoomController &roomController) {

    //find and load character based on username
    /* json work
     * if character not found one will be made and then loaded*/

    // Dummy Data for all logged in users
    Character dummyCharacter(username, CHARACTER_ID, ROOM_ID);
    roomController.addUserNameToRoom(dummyCharacter.getName(),dummyCharacter.getRoomID());

    return onlineUsers.emplace(username,dummyCharacter).second;
}

bool CharacterController::removeFromOnlineUsers(std::string &username){
    return onlineUsers.erase(username) > 0;
}

Character &CharacterController::getCharacter(std::string &username) {
    return onlineUsers.find(username)->second;
}

bool CharacterController::doesCharacterExist(std::string &userName) {
    return onlineUsers.count(userName) > 0 ;
}

std::vector<std::string> CharacterController::getNamesOfOnlineUsers() {
    std::vector<std::string> usernameList;
    for(auto &characters : onlineUsers) {
        usernameList.push_back(characters.first);
    }
    return usernameList;
}

void CharacterController::swapCharacters(Character &userCharacter, Character &targetCharacter) {
    auto item1 = onlineUsers.find(userCharacter.getName());
    auto item2 = onlineUsers.find(targetCharacter.getName());
    if ((item1 != onlineUsers.end()) && (item2 != onlineUsers.end())){
        std::swap(item1->second, item2->second);
    }

}

bool CharacterController::doesCharacterHaveSpell(std::string &username, std::string &spellName) {
    Character character = getCharacter(username);
    return(character.doesSpellExist(spellName));
}


