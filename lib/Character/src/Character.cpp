#include <utility>

#include <utility>

//
// Created on 1/23/2019.
//

#include <iostream>
#include <Character.h>


std::string Character::getName(){
    return this->name;
}

unsigned int Character::getRoomID() {
    return this->roomID;
}

unsigned int Character::getCharacterId() const {
    return characterId;
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

void Character::listInventory() {
    inventory.listInventory();
}

void Character::dropItem(unsigned int objectId) {
    inventory.removeItem(objectId);
}


Character::Character(const std::string &name, unsigned int characterId, unsigned int roomID) :roomID(roomID), name(name), inventory(){}









