#include <iostream>
#include <algorithm>
#include <Room.h>

Room::Room(unsigned int id, string name){
    Room::id = id;
    Room::name = name;
}

void Room::addDescription(const string& description) {
    Room::descriptions.push_back(description);
}

void Room::addDoor(Door& door) {
    Room::doors.push_back(door);
}

void Room::addExtendedDescription(const string& extDescription) {
    Room::extendedDescriptions.push_back(extDescription);
}

void Room::join(const int objectId) {
    Room::objectIdList.push_back(objectId);
}

void Room::quit(const int objectId) {
    std::remove(objectIdList.begin(), objectIdList.end(), objectId);
}
