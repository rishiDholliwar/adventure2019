#include <utility>
#include <iostream>
#include <algorithm>
#include <Character.h>


Character::Character(const Name &name, ID characterID, ID roomID)
{
  this->name = name;
  this->characterID = characterID;
  this->roomID = roomID;
  this->inventory = Inventory{};
  this->wearing = std::vector<Object>();
}

Name Character::getName() const {
    return this->name;
}

ID Character::getRoomID() const {
    return this->roomID;
}

ID Character::getCharacterID() const {
    return characterID;
}

Object Character::getItemFromInventoryByName(Name objType) {
    return inventory.getItemByType(objType);
}

bool Character::addItemToInventory(Object obj) {
    inventory.addItem(obj);
}

void Character::setRoomID(ID roomID) {
    Character::roomID = roomID;
}

bool Character::hasItem(ID objectId) {
    return inventory.doesItemExist(objectId);
}

bool Character::hasItemByName(Name objType) {
    return inventory.doesItemExistByName(objType);
}

auto Character::getWearingIteratorByID(ID objectId) {
    auto it = find_if(wearing.begin(), wearing.end(),
                      [ objectId] ( Object const& obj )->bool {
                          return obj.getID() == objectId;
                        });
    return it;
}

bool Character::isWearing(ID objectId) {
    if (hasItem(objectId) == false) {
        return hasItem(objectId);
    }

    return getWearingIteratorByID(objectId) != wearing.end();
}

bool Character::isWearingByName(Name objType) {
    if (hasItemByName(objType) == false) {
        return hasItemByName(objType);
    }

    auto it = find_if(wearing.begin(), wearing.end(),
                      [ objType ] ( Object const& obj )->bool {
                          return obj.getName() == objType;
                        });

    return !(it == wearing.end());
}

bool Character::wear(Object obj) {
    wearing.push_back(obj);
    return isWearing(obj.getID());
}

bool Character::takeOff(Object obj) {
    auto it = getWearingIteratorByID(obj.getID());

    if (it != wearing.end()) {
        it = wearing.erase(it);
        return isWearing(obj.getID()) == false;
    }

    return isWearing(obj.getID()) == false;
}


bool Character::dropItem(ID objectId) {
    return inventory.removeItem(objectId);
}

std::string Character::listInventory() {
    return inventory.listInventory();
}
