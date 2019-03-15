#include <Door.h>
#include <iostream>


Door::Door(AlterSpace::ID _id, AlterSpace::ID _designatedRoomId, const std::string & _direction) {
    id = _id;
    designatedRoomID = _designatedRoomId;
    direction = _direction;
    status = UNLOCKED;
}

void Door::addKeyword(const std::string &keyword) {
    this->keywords.push_back(keyword);
}

void Door::addDescription(const std::string &description) {
    this->descriptions.push_back(description);
}

void Door::setDoorLocked() {
    status = LOCKED;
}

void Door::setDoorUnlocked() {
    status = UNLOCKED;
}