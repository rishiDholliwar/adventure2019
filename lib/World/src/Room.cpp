#include <iostream>
#include <algorithm>
#include <Room.h>

Room::Room(unsigned int& id, string& name){
    Room::id = id;
    Room::name = name;
}

void Room::addDescription(string& description) {
    Room::descriptions.push_back(description);
}

void Room::addDoor(std::unique_ptr<Door> door) {
    Room::doors.push_back(door);
}
void Room::addExtendedDescription(string& extDescription) {
    Room::extendedDescriptions.push_back(extDescription);
}

void Room::join(int& objectId) {
    Room::objectIdList.push_back(objectId);
}

void Room::quit(int& objectId) {
    std::remove(objectIdList.begin(), objectIdList.end(), objectId);
}
