#include <utility>

//
// Created on 1/23/2019.
//

#include <iostream>
#include <Character.h>


Character::Character(const std::string &name, unsigned int characterID, unsigned int roomID) : name(name),
                                                                                               characterID(characterID),
                                                                                               roomID(roomID),
                                                                                               inventory() {}

std::string Character::getName(){
    return this->name;
}

unsigned int Character::getRoomID() {
    return this->roomID;
}

unsigned int Character::getCharacterID() const {
    return characterID;
}

bool Character::addItemToInventory(Object obj) {
    inventory.addItem(obj);
}

void Character::setRoomID(unsigned int roomID) {
    Character::roomID = roomID;
}

bool Character::hasItem(unsigned int objectId) {
    return inventory.doesItemExist(objectId);
}

void Character::dropItem(unsigned int objectId) {
    inventory.removeItem(objectId);
}

std::string Character::listInventory() {
    return inventory.listInventory();
}













