//
// Created by evan on 17/01/19.
//

#include "Door.h"
#include <iostream>


Door::Door(unsigned int id, unsigned destinatedRoomId, std::string direction) {
    Door::id = id;
    Door::destinatedRoomId = destinatedRoomId;
    Door::direction = std::move(direction);
}

void Door::addDescription(std::string description) {
    Door::descriptions.push_back(std::move(description));
}

void Door::addKeyword(std::string keyword) {
    Door::keywords.push_back(std::move(keyword));
}

