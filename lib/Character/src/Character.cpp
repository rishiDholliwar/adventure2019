#include <iostream>
#include <algorithm>
#include <Character.h>
#include <sstream>
#include <ios>

Character::Character(const Name &name, ID roomID)
{
  this->name = name;
  this->roomID = roomID;
  this->inventory = Inventory{};
  this->confused = false;
  this->wearing = std::vector<Object>();
}

Name Character::getName() const {
    return this->name;
}

ID Character::getRoomID() const {
    return this->roomID;
}

ID Character::getID() const {
    return id;
}

std::string Character::getInfo() const {

  std::stringstream retString;
  retString << "ID: " << getID() << "\n" << "Name: " << getName() << "\n" << "Wearing: \n" << listWearing() << "Room ID: " << getRoomID() << "\n";


	return retString.str();
}

std::vector<Object> Character::getItemsFromInventory(Name objectName) {
    return inventory.getItems(objectName);
}

Object Character::getItemFromInventory(Name objectName) {
    return inventory.getItem(objectName);
}

Object Character::getItemFromInventory(ID objectId) {
    return inventory.getItem(objectId);
}

void Character::addItemToInventory(Object obj) {
    inventory.addItem(obj);
}

void Character::setRoomID(ID roomID) {
    Character::roomID = roomID;
}

bool Character::hasItem(ID objectId) {
    return inventory.doesItemExist(objectId);
}

bool Character::hasItem(Name &objectName) {
    return inventory.doesItemExist(objectName);
}

std::vector<Object>::iterator Character::getWearingIterator(ID objectId) {
    auto it = find_if(wearing.begin(), wearing.end(),
                      [ objectId] ( Object const& obj )->bool {
                          return obj.getID() == objectId;
                        });
    return it;
}

std::vector<Object>::iterator Character::getWearingIterator(Name objectName) {
    auto it = find_if(wearing.begin(), wearing.end(),
                      [ objectName ] ( Object const& obj )->bool {
                          return obj.getName() == objectName;
                        });
    return it;
}

bool Character::isWearing(ID objectId) {

    return getWearingIterator(objectId) != wearing.end();
}

bool Character::isWearing(Name objectName) {

    auto it = find_if(wearing.begin(), wearing.end(),
                      [ objectName ] ( Object const& obj )->bool {
                          return obj.getName() == objectName;
                        });

    return it != wearing.end();
}

bool Character::wear(ID objectId) {
    wearing.push_back(getItemFromInventory(objectId));
    dropItem(objectId);
    return isWearing(objectId);
}

ID Character::getWearingID(Name objectName) {
    auto it = getWearingIterator(objectName);
    return (*it).getID();
}

bool Character::remove(Object obj) {

    if (!(isWearing(obj.getID()))) {
      return false;
    }

    auto it = getWearingIterator(obj.getID());

    it = wearing.erase(it);
    addItemToInventory(obj);
    return true;
}


bool Character::dropItem(ID objectId) {
    return inventory.removeItem(objectId);
}

std::string Character::listWearing() const {
	std::stringstream wearList;
	int wearCount = 1;

	for (auto &obj : wearing) {
		wearList << "\t" << wearCount << ". " << obj.getName() << "\n";
		wearCount++;
	}

	return wearList.str();
}

std::string Character::listInventory() {
    return inventory.listInventory();
}


void Character::confuse() {
    if(confused){
        confused = false;
    }else {
        confused = true;
    }
}


bool Character::isConfused() {
  return confused;
}


//For combat:
unsigned int Character::getCurrentHP() const {
    return currentHP;
}

void Character::setCurrentHP(unsigned int currentHP) {
    if(currentHP <=0){

    }  else {
        Character::currentHP = 0;
    }
    Character::currentHP = currentHP;
}

unsigned int Character::getAttack() const {
    return attack;
}

void Character::setAttack(unsigned int attack) {
    Character::attack = attack;
}

unsigned int Character::getDefense() const {
    return defense;
}

void Character::setDefense(unsigned int defense) {
    Character::defense = defense;
}

unsigned int Character::getMaxHP() const {
    return maxHP;
}

void Character::setMaxHP(unsigned int maxHP) {
    Character::maxHP = maxHP;
}

std::string Character::examineCombat() {
    return "\tName: " + name + "\n"
           + "\tcurrentHP: " + std::to_string(currentHP) + "\n"
           //<< "\t\tcurrentMP: " << currentMP << + "\n"
           + "\tmaxHP: " + std::to_string(maxHP) + "\n"
           //<< "\t\tmaxMP: " << maxMP << std::endl
           + "\tattack: " + std::to_string(attack) + "\n"
           + "\tdefence: " + std::to_string(defense) + "\n";
}