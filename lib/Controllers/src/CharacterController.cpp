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

bool CharacterController::doesCharacterExist(Name &username) {
    return _characters.find(username) != _characters.end();
}

std::vector<Name> CharacterController::getAllCharacterNames() {
    std::vector<std::string> usernameList;
    for(auto &characters : _characters) {
        usernameList.push_back(characters.first);
    }
    return usernameList;
}

std::string CharacterController::getCharacterInfo(Name &username) {
    return getCharacter(username).getInfo();
}

ID CharacterController::getCharacterRoomID(Name &username) {
    return getCharacter(username).getRoomID();
}

void CharacterController::setCharacterRoomID(Name &username, ID roomID) {
    getCharacter(username).setRoomID(roomID);
}

bool CharacterController::characterHasItem(Name &username, ID itemID) {
    return getCharacter(username).hasItem(itemID);
}

bool CharacterController::characterHasItem(Name &username, Name itemName) {
    return getCharacter(username).hasItem(itemName);
}

void CharacterController::addItemToCharacterInventory(Name &username, Object item) {
    getCharacter(username).addItemToInventory(item);
}

bool CharacterController::dropItemFromCharacterInventory(Name &username, ID objectID) {
    return getCharacter(username).dropItem(objectID);
}

Object CharacterController::getItemFromCharacterInventory(Name &username, Name itemName) {
    return getCharacter(username).getItemFromInventory(itemName);
}

bool CharacterController::characterIsWearingItem(Name &username, ID objectID) {
    return getCharacter(username).isWearing(objectID);
}

bool CharacterController::characterIsWearingItem(Name &username, Name itemName) {
    return getCharacter(username).isWearing(itemName);
}

bool CharacterController::characterWearItem(Name &username, Object item) {
    return getCharacter(username).wear(item);
}

bool CharacterController::characterRemoveItem(Name &username, Object item) {
    return getCharacter(username).remove(item);
}

std::string CharacterController::characterListInventory(Name &username) {
    return getCharacter(username).listInventory();
}

void CharacterController::swapCharacters(Name &userCharacterName, Name &targetCharacterName) {
    auto item1 = _characters.find(userCharacterName);
    auto item2 = _characters.find(targetCharacterName);
    if ((item1 != _characters.end()) && (item2 != _characters.end())){
        std::swap(item1->second, item2->second);
    }

}


