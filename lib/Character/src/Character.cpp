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
  this->inventory.addItem(Object(100,"Basic Sword"));
  this->inventory.addItem(Object(200,"Basic Armor"));
  this->wearing = std::vector<Object>();
}

Name Character::getName() const {
    return this->name;
}

ID Character::getRoomID() const {
    return this->roomID;
}

ID Character::getCharacterID() const {
    return characterID.id;
}

std::string Character::getInfo() const {

  std::stringstream retString;
  retString << "ID: " << getCharacterID() << "\n" << "Name: " << getName() << "\n" << "Wearing: \n\t" << listWearing() << "Room ID: " << getRoomID() << "\n";


	return retString.str();
}

Object Character::getItemFromInventory(Name objectName) {
    return inventory.getItem(objectName); 
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

bool Character::wear(Object obj) {
    wearing.push_back(obj);
    dropItem(obj.getID());
    return isWearing(obj.getID());
}

bool Character::remove(Object obj) {
    auto it = getWearingIterator(obj.getID());

    if (it != wearing.end()) {
        it = wearing.erase(it);
        addItemToInventory(obj);
        return (!isWearing(obj.getID()) && hasItem(obj.getID()));
    }

    return !isWearing(obj.getID());
}


bool Character::dropItem(ID objectId) {
    return inventory.removeItem(objectId);
}

std::string Character::listWearing() const {
	std::stringstream wearList;
	int wearCount = 1;

	for (auto &obj : wearing) {
		wearList << wearCount << ". " << obj.getName() << "\n";
		wearCount++;
	}

	return wearList.str();
}

std::string Character::listInventory() {
    return inventory.listInventory();
}













