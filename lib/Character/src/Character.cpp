#include <utility>
#include <iostream>
#include <algorithm>
#include <Character.h>


Character::Character(const Name &name, ID characterID, ID roomID)
{
  this->name = name;
  this->characterID = characterID;
  this->roomID = roomID;
  this->inventory = Inventory{};
  this->wearing = std::vector<Object>();
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

std::string Character::getInfo() const {
	std::string charIDInfo;
	charIDInfo = "ID: " + std::to_string(getCharacterID()) + "\n";
	std::string charNameInfo;
	charNameInfo = "Name: " + getName() + "\n";
	std::string charWearInfo;
	charWearInfo = "Wearing: \n\t" + listWearing();
	std::string roomInfo;
	roomInfo = "Room ID: " + std::to_string(getRoomID()) + "\n";

	return charIDInfo + charNameInfo + roomInfo + charWearInfo;
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

auto Character::getWearingIterator(ID objectId) {
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

    return !(it == wearing.end());
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
	std::string wearList = "";
	int wearCount = 1;

	for (Object obj : wearing) {
		std::string wearIndex = std::to_string(wearCount) + ". " + obj.getName() + "\n";
		wearList += wearIndex;
		wearCount++;
	}

	return wearList;
}

std::string Character::listInventory() {
    return inventory.listInventory();
}













