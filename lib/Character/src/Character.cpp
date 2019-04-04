#include <iostream>
#include <algorithm>
#include <Character.h>
#include <sstream>
#include <ios>

Name Character::getName() const {
    return this->name;
}

ID Character::getCharacterID() const {
	return this->characterID;
}

ID Character::getRoomID() const {
    return this->roomID;
}

bool Character::isNPC() const {
	return this->characterType == CharacterType::NON_PLAYABLE;
}

void Character::setNPC() {
	this->characterType = CharacterType::NON_PLAYABLE;
}

ID Character::getID() const {
    return id;
}

std::vector<std::string> const& Character::getKeywords() const{ 
	return keywords;
}

std::string const& Character::getShortDesc() const{
	return shortdesc;
}

std::vector<std::string> const& Character::getLongDesc() const{
	return longdesc;
}

std::vector<std::string> const& Character::getDescription() const{
	return description;
}

std::string Character::getInfo() const {

  std::stringstream retString;

  if (isNPC()) {
  	retString << "Type: NPC\n";
  }
  
  retString << "ID: " << getID() << "\n" << "Name: " << getName() << "\n" << "Wearing: \n" << listWearing() << "Room ID: " << getRoomID() << "\n";


	return retString.str();
}

std::vector<Object> Character::getItemsFromInventory(Name objectName) {
    return inventory.getItems(objectName);
}

std::vector<Object> Character::getItemsFromWearing(Name objectName) {

    std::vector<Object> items;

    for (auto &item : wearing) {
        if (item.getName() == objectName) {
            items.push_back(item);
        }
    }

    return items;
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
    this->roomID = roomID;
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

void Character::wear(ID objectId) {
    wearing.push_back(getItemFromInventory(objectId));
    dropItem(objectId);
}

ID Character::getWearingID(Name objectName) {
    auto it = getWearingIterator(objectName);
    return (*it).getID();
}

void Character::remove(Object obj) {

    if (isWearing(obj.getID())) {
      auto it = getWearingIterator(obj.getID());

      it = wearing.erase(it);
      addItemToInventory(obj);
    }
}


void Character::dropItem(ID objectId) {
    inventory.removeItem(objectId);
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


bool Character::isConfused() const {
  return confused;
}

const std::vector<Object> &Character::getWearing() const {
    return wearing;
}

void Character::setWearing(const std::vector<Object> &wearing) {
    this->wearing = wearing;
}

const Inventory &Character::getInventory() const {
    return inventory;
}

void Character::setInventory(const Inventory &inventory) {
    Character::inventory = inventory;
}

//For combat:

void Character::giveFullHP() {
    currentHP = maxHP;
}

unsigned int Character::getCurrentHP() const {
    return currentHP;
}

void Character::setCurrentHP(unsigned int currentHP) {
    if (currentHP < 0) {
        currentHP = 0;
    }

    this->currentHP = currentHP;
}

unsigned int Character::getAttack() const {
    return attack;
}

void Character::setAttack(unsigned int attack) {
    this->attack = attack;
}

unsigned int Character::getDefense() const {
    return defense;
}

void Character::setDefense(unsigned int defense) {
    this->defense = defense;
}

unsigned int Character::getMaxHP() const {
    return maxHP;
}

void Character::setMaxHP(unsigned int maxHP) {
    this->maxHP = maxHP;
}

std::string Character::examineCombat() {
    std::stringstream output;

    output << "\tName: " << name << "\n"
           << "\tHP: " << std::to_string(currentHP) + "/" + std::to_string(maxHP) + "\n"
           << "\tAttack: " << attack << "\n"
           << "\tDefence: " << defense << "\n";

    return output.str();
}

bool  Character::isInCombat(){
  return combat;
}

void Character::setCombatState(bool state){
   combat = state;
}

