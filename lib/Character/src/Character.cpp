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
std::string Character::getName(){
    return this->name;
}

std::string Character::getRoomID() {
    return this->roomID;
}

void Character::addItemtoInventory(Object obj) {
    inventory.addItem(obj);
}

void Character::listInventory() {
    inventory.listInventory();
}
