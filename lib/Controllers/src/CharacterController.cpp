#include <iostream>
#include <string>
#include <sstream>
#include <CharacterController.h>
#include <RoomController.h>

CharacterController::CharacterController() = default;

void CharacterController::addCharacter(Name &username, RoomController &roomController, ObjectController &objectController) {

    // Default Data for all first time users
    Character defaultCharacter(username, ROOM_ID);
    roomController.addUserNameToRoom(defaultCharacter.getName(),defaultCharacter.getRoomID());

    defaultCharacter.addItemToInventory(Object("Basic Sword"));
    objectController.addObjectToList(defaultCharacter.getItemFromInventory("Basic Sword"));

    defaultCharacter.addItemToInventory(Object("Basic Armor"));
    objectController.addObjectToList(defaultCharacter.getItemFromInventory("Basic Armor"));

    _characters.emplace(username,defaultCharacter).second;
}

void CharacterController::addNPC(Name &npcname, RoomController &roomController, ObjectController &objectController) {

    Character defaultNPC(npcname, ROOM_ID, CharacterType::NON_PLAYABLE);
    roomController.addCharacterToRoom(defaultNPC.getID(),defaultNPC.getRoomID());

    std::stringstream ss;
    ss << npcname << "-" << defaultNPC.getID();
    Name npcKey = ss.str();

    _characters.emplace(npcKey, defaultNPC).second;
}

void CharacterController::addCharacter(Character &aCharacter) {
    Name username = aCharacter.getName();

    _characters.emplace(username, aCharacter).second;
}

void CharacterController::addNPC(Character &aNPC) {

    if (!aNPC.isNPC()) {
        return;
    }

    std::stringstream ss;
    ss << aNPC.getName() << "-" << aNPC.getID();
    Name npcKey = ss.str();

    _characters.emplace(npcKey, aNPC);
}

void CharacterController::removeCharacter(Name &username){
    _characters.erase(username);
}

ID CharacterController::getNPCID(Name &npcKey) {
    return _characters.find(npcKey)->second.getID();
}

std::vector<Name> CharacterController::getNPCKeys(Name npcName) {
    int npcNameLength = npcName.length();
    std::vector<Name> npcKeys{};

    for (auto&character : _characters) {

        if (!character.second.isNPC()) {
            continue;
        }

        if (character.second.getName() == npcName) {
            npcKeys.push_back(character.first);
        }
    }

    return npcKeys;
}

Name CharacterController::getCharName(Name &username) {
    return getCharacter(username).getName();
}

Character &CharacterController::getCharacter(Name &username) {
    return _characters.find(username)->second;
}

// Character &CharacterController::getCharacterByCharName(Name &charName) {
//     auto it = find_if(_characters.begin(), _characters.end(),
//                         [&charName] (auto const& character) {
//                             return charName == character.second.getName();
//                         });

//     return it->second;
// }

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

bool CharacterController::isCharacterNPC(Name &npcKey) {
    return _characters.find(npcKey)->second.isNPC();
}

std::vector<Name> CharacterController::getAllCharacterNames() {
    std::vector<std::string> usernameList{};
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

void CharacterController::dropItemFromCharacterInventory(Name &username, ID objectID) {
    getCharacter(username).dropItem(objectID);
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

void CharacterController::characterWearItem(Name &username, Name itemName) {
    ID itemID = getItemIDFromCharacterInventory(username, itemName);
    getCharacter(username).wear(itemID);
}

ID CharacterController::getItemIDFromCharacterWearing(Name &username, Name itemName) {
    return getCharacter(username).getWearingID(itemName);
}

void CharacterController::characterRemoveItem(Name &username, Object item) {
    getCharacter(username).remove(item);
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
