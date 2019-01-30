//
// Created on 1/23/2019.
//

#include <iostream>
#include <Character.h>


Character::Character() {
}

/*
 * Create character with just a name.
 */
Character::Character(std::string name) {
    this->name = name;
    roomID = STARTING_ROOM;
}
std::string Character::getCharacterName(){
    return this->name;
}

std::string Character::getCharacterRoomID() {
    return this->roomID;
}

void Character::setCharacterRoomId(std::string id) {
    this->roomID = id;
}

void Character::addItemtoInventory(Object obj) {
    this->inventory.addItem(obj);
}


void Character::listInventory() {
    this->inventory.listInventory();
}

void Character::removeItemFromInventory(std::string name) {
    inventory.removeItem(name);
}
