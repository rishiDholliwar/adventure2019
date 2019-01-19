#include <algorithm>
#include "Room.h"

Room::Room(unsigned int id, std::string& name){
    Room::id = id;
    Room::name = std::move(name);
}

void Room::addDescription(std::string& description) {
    Room::descriptions.push_back(std::move(description));
}

void Room::addDoor(std::unique_ptr<Door>& door) {
    Room::doors.push_back(std::move(door));
}
void Room::addExtendedDescription(std::string& extDescription) {
    Room::extendedDescriptions.push_back(std::move(extDescription));
}

void Room::join(int objectId) {
    Room::objectIdList.push_back(objectId);
}

void Room::quit(int objectId) {
    std::remove(objectIdList.begin(), objectIdList.end(), objectId);
}
