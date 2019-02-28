//
// Created by evan on 17/01/19.
//

#include <Door.h>
#include <iostream>


Door::Door(Door::ID id, Door::ID destinatedRoomId, const std::string &direction) {
    this->id = id;
    this->designatedRoomID = destinatedRoomId;
    this->direction = direction;
    this->status = UNLOCKED;
}

void Door::addKeyword(const std::string &keyword) {
    this->keywords.push_back(keyword);
}

void Door::addDescription(const std::string &description) {
    this->descriptions.push_back(description);
}

bool Door::setDoorLocked() {
    return (status == UNLOCKED) && (status = LOCKED);
}

bool Door::setDoorUnlocked() {
    return (status == LOCKED) && (status = UNLOCKED);
}