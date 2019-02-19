#include <utility>

//
// Created on 1/23/2019.
//

#include <iostream>
#include <Character.h>


Character::Character(const std::string &name, unsigned int characterID, unsigned int roomID) : name(name),
                                                                                               characterID(characterID),
                                                                                               roomID(roomID),
                                                                                               inventory() {
    this->currentHP = maxHP;
    this->currentMP = maxMP;
}

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

void Character::updateCharacterStatus(Character::CharacterStatus status) {
    this->status = status;
}

std::string Character::getListOfSpells() {
    if(characterSpells.empty()){
        return std::string();
    }

    int spellCounter = 1;
    std::string spellList;
    for(auto &spells : characterSpells){
        std::string spellString = std::to_string(spellCounter) + ". " + spells;
        spellList += spellString;
        spellCounter++;
    }
    return spellList;
}


unsigned int Character::getCharacterCurrentHP() {
    return currentHP;
}

unsigned int Character::getCharacterCurrentMP() {
    return currentMP;
}

void Character::setCharacterCurrentHP(unsigned int hp) {
    this->currentHP = hp;
}

void Character::setCharacterCurrentMP(unsigned int mp) {
    this->currentMP = mp;
}

bool Character::doesSpellExist(std::string &spellName) {
    if(characterSpells.empty()){
        return false;
    }
    for(auto &spells : characterSpells){
        if(spells == spellName){
            return true;
        }
    }
    return false;
}













