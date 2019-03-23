#include <iostream>
#include <string>
#include <CharacterController.h>
#include <RoomController.h>
#include <Utility.h>


CharacterController::CharacterController() = default;

bool CharacterController::addCharacter(Name &username, RoomController &roomController, ObjectController &objectController) {

    //find and load character based on username
    /* json work
     * if character not found one will be made and then loaded*/

    // Dummy Data for all logged in users
    Character dummyCharacter(username, ROOM_ID);
    roomController.addUserNameToRoom(dummyCharacter.getName(),dummyCharacter.getRoomID());

    dummyCharacter.addItemToInventory(Object("Basic Sword"));
    objectController.addObjectToList(dummyCharacter.getItemFromInventory("Basic Sword"));

    dummyCharacter.addItemToInventory(Object("Basic Armor"));
    objectController.addObjectToList(dummyCharacter.getItemFromInventory("Basic Armor"));


    return _characters.emplace(username,dummyCharacter).second;
}

bool CharacterController::removeCharacter(Name &username){
    return _characters.erase(username) > 0;
}

bool CharacterController::findCharacter(Name username) {
    //
    return _characters.find(username) != _characters.end();
}

Character &CharacterController::getCharacter(Name &username) {
    return _characters.find(username)->second;
}

Character &CharacterController::getCharacterByCharName(Name &charName) {
    auto it = find_if(_characters.begin(), _characters.end(),
                        [&charName] (auto const& character) {
                            return charName == character.second.getName();
                        });

    return it->second;
}

Name CharacterController::getUsernameOfCharacter(Name &charName){
    auto it = find_if(_characters.begin(), _characters.end(),
                        [&charName] (auto const& character) {
                            return charName == character.second.getName();
                        });

    return it->first;
}


bool CharacterController::doesCharacterExist(Name &username) {
    return _characters.find(username) != _characters.end();
}

std::vector<Name> CharacterController::getAllCharacterNames() {
    std::vector<std::string> usernameList{};
    for(auto &characters : _characters) {
        usernameList.push_back(characters.first);
    }
    return usernameList;
}

std::string CharacterController::lookCharacter(Name &userName) {
    auto character = getCharacter(userName);
    return utility::extractStringVector(character.getDescriptions());
}

std::string CharacterController::examineCharacter(Name &userName) {
    auto character = getCharacter(userName);
    auto extDescriptions = character.getExtendedDescriptions();
    if (extDescriptions.empty()){
        return lookCharacter(userName);
    }
    return utility::extractStringVector(extDescriptions);
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

std::vector<Object> CharacterController::getItemsFromCharacterInventory(Name &username, Name itemName) {
    return getCharacter(username).getItemsFromInventory(itemName);
}

Object CharacterController::getItemFromCharacterInventory(Name &username, Name itemName) {
    return getCharacter(username).getItemFromInventory(itemName);
}

Object CharacterController::getItemFromCharacterInventory(Name &username, ID itemID) {
    return getCharacter(username).getItemFromInventory(itemID);
}

ID CharacterController::getItemIDFromCharacterInventory(Name &username, Name itemName) {
    return getItemFromCharacterInventory(username, itemName).getID();
}

bool CharacterController::characterIsWearingItem(Name &username, ID objectID) {
    return getCharacter(username).isWearing(objectID);
}

bool CharacterController::characterIsWearingItem(Name &username, Name itemName) {
    return getCharacter(username).isWearing(itemName);
}

bool CharacterController::characterWearItem(Name &username, Name itemName) {
    ID itemID = getItemIDFromCharacterInventory(username, itemName);
    return getCharacter(username).wear(itemID);
}

ID CharacterController::getItemIDFromCharacterWearing(Name &username, Name itemName) {
    return getCharacter(username).getWearingID(itemName);
}

bool CharacterController::characterRemoveItem(Name &username, Object item) {
    return getCharacter(username).remove(item);
}

std::string CharacterController::characterListInventory(Name &username) {
    return getCharacter(username).listInventory();
}

void CharacterController::swapCharacter(Name &userCharacterName, Name &targetCharacterName) {
    auto item1 = _characters.find(userCharacterName);
    auto item2 = _characters.find(targetCharacterName);
    if ((item1 != _characters.end()) && (item2 != _characters.end())){
        std::swap((item1->second), (item2->second));
    }

}

void CharacterController::confuseCharacter(Name &targetCharacterName){
    getCharacter(targetCharacterName).confuse();
}

bool CharacterController::isCharacterConfused(Name &username) {
    return getCharacter(username).isConfused();
}
