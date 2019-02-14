#include <utility>
#include <iostream>
#include <Character.h>


Character::Character(const Name &name, ID characterID, ID roomID)
{
  this->name = name;
  this->characterID = characterID;
  this->roomID = roomID;
  this->inventory = Inventory{};
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

Object Character::getItemFromInventoryByName(Name objectName) {
    return inventory.getItemByName(objectName); 
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

bool Character::hasItemByName(Name objectName) {
    return inventory.doesItemExistByName(objectName);
}

bool Character::dropItem(ID objectId) {
    return inventory.removeItem(objectId);
}

std::string Character::listInventory() {
    return inventory.listInventory();
}













