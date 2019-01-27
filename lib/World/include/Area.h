//
// Created by rishi on 1/17/19.
//

#ifndef OOP_AREA_H
#define OOP_AREA_H

#include <vector>
#include <string>
#include "Room.h"
#include <memory>


class Area
{
public:
    Area(unsigned int id, std::string name);
    void addRoom(Room* room);
    unsigned int const& getId() const{return id;};
    std::string const& getName() const{return name;};
    std::vector<Room*> const& getRooms()const{return rooms;};
private:
    unsigned int id;
    std::string name;
    std::vector<Room*> rooms;
};
#endif //OOP_AREA_H
