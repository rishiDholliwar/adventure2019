#include <iostream>
#include <CharacterController.h>
#include <RoomController.h>

CharacterController::CharacterController() = default;

bool CharacterController::addCharacter(Name &username, RoomController &roomController) {

    //find and load character based on username
    /* json work
     * if character not found one will be made and then loaded*/

    // Dummy Data for all logged in users
    Character dummyCharacter(username, CHARACTER_ID, ROOM_ID);
    roomController.addUserNameToRoom(dummyCharacter.getName(),dummyCharacter.getRoomID());

    return _characters.emplace(username,dummyCharacter).second;
}

bool CharacterController::removeCharacter(Name &username){
    return _characters.erase(username) > 0;
}

Character &CharacterController::getCharacter(Name &username) {
    return _characters.find(username)->second;
}

bool CharacterController::doesCharacterExist(Name &userName) {
    return _characters.find(userName) != _characters.end();
}

std::vector<Name> CharacterController::getAllCharacterNames() {
    std::vector<std::string> usernameList;
    for(auto &characters : _characters) {
        usernameList.push_back(characters.first);
    }
    return usernameList;
}

void CharacterController::swapCharacters(Character &userCharacter, Character &targetCharacter) {
    auto item1 = _characters.find(userCharacter.getName());
    auto item2 = _characters.find(targetCharacter.getName());
    if ((item1 != _characters.end()) && (item2 != _characters.end())){
        std::swap(item1->second, item2->second);
    }

}

bool CharacterController::doesCharacterHaveSpell(std::string &username, std::string &spellName) {
    Character character = getCharacter(username);
    return(character.doesSpellExist(spellName));
}


