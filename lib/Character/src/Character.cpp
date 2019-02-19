#include <utility>
#include <iostream>
#include <Character.h>
#include <StringLibrary.h>


Character::Character(const Name &name, ID characterID, ID roomID)
{
  this->name = name;
  this->characterID = characterID;
  this->roomID = roomID;
  this->inventory = Inventory{};
  addDefaultSpells();

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


void Character::addDefaultSpells(){
    addSpellToCharacter(StringLibrary::spellSwap);
    addSpellToCharacter(StringLibrary::spellDecoy);
    addSpellToCharacter(StringLibrary::spellConfuse);
}

void Character::addSpellToCharacter(std::string &spellName) {
    this->characterSpells.push_back(spellName);
}












