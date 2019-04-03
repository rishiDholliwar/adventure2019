#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <CharacterController.h>
#include <RoomController.h>
#include <Utility.h>

void CharacterController::addCharacter(Name &username, RoomController &roomController, ObjectController &objectController) {

    // Default Data for all first time users
    Character defaultCharacter(username, ROOM_ID);
    roomController.addCharacterToRoom(defaultCharacter.getName(), defaultCharacter.getRoomID());

    // defaultCharacter.addItemToInventory(Object("Basic Sword"));
    // objectController.addObjectToList(defaultCharacter.getItemFromInventory("Basic Sword"));

    // std::vector<std::string> keywords;
    // keywords.push_back("Basic ");
    // keywords.push_back("Armor");

    // std::vector<std::string> longdesc;
    // longdesc.push_back("armor long desc1");
    // longdesc.push_back("armor long desc2");

    // std::vector<Extra> extra;

    // Extra e1{keywords, longdesc};

    // extra.push_back(e1);

    // defaultCharacter.addItemToInventory(Object(12, keywords, "armor short desc", longdesc, extra));
    // objectController.addObjectToList(defaultCharacter.getItemFromInventory("Basic Armor"));

    defaultCharacter.addItemToInventory(objectController.getObjectFromList("sword"));
    defaultCharacter.addItemToInventory(objectController.getObjectFromList("cloak"));

    _characters.emplace(username,defaultCharacter).second;
}

void CharacterController::addCharacter(Character &aCharacter) {
    Name username = aCharacter.getName();

    _characters.emplace(username, aCharacter).second;
}

void CharacterController::addNPC(Character aNPC) {

    aNPC.setNPC();

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

std::vector<Name> CharacterController::getUsernamesOfCharacter(Name characterName) {
    std::vector<Name> usernames{};

    for (auto&character : _characters) {
        if (character.second.getName() == characterName) {
            usernames.push_back(character.first);
        }
    }

    return usernames;
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
    auto it = std::find_if(_characters.begin(), _characters.end(),
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

std::string CharacterController::lookCharacter(Name &userName) {
    auto character = getCharacter(userName);
    return utility::extractStringVector(character.getDescription());
}

std::string CharacterController::examineCharacter(Name &userName) {
    auto character = getCharacter(userName);
    auto extDescriptions = character.getLongDesc();
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

void CharacterController::dropItemFromCharacterInventory(Name &username, ID objectID) {
    getCharacter(username).dropItem(objectID);
}

std::vector<Object> CharacterController::getItemsFromCharacterInventory(Name &username, Name itemName) {
    return getCharacter(username).getItemsFromInventory(itemName);
}

std::vector<Object> CharacterController::getItemsFromCharacterWearing(Name &username, Name itemName) {
    return getCharacter(username).getItemsFromWearing(itemName);
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

void CharacterController::characterWearItem(Name &username, ID itemID) {
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
