#include <algorithm>
#include "Area.h"

Area::Area(unsigned int id, std::string name) {
    Area::id = id;
    Area::name = std::move(name);
}

void Area::addRoom(Room* room) {
    Area::rooms.push_back(room);
}