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

Name Character::getName(){
    return this->name;
}

ID Character::getRoomID() {
    return this->roomID;
}

ID Character::getCharacterID() const {
    return characterID;
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

void Character::dropItem(ID objectId) {
    inventory.removeItem(objectId);
}

std::string Character::listInventory() {
    return inventory.listInventory();
}













