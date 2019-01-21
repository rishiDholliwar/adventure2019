#include <algorithm>
#include "Area.h"

Area::Area(unsigned int id, std::string name) {
    Area::id = id;
    Area::name = std::move(name);
}

void Area::addRoom(std::unique_ptr<Room>& room) {
    Area::rooms.push_back(std::move(room));
}