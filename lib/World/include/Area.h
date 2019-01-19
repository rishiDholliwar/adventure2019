//
// Created by rishi on 1/17/19.
//

#ifndef OOP_AREA_H
#define OOP_AREA_H

#include <vector>
#include <string>
#include <Area.h>
#include <Room.h>
#include <memory>

class Area
{
public:
    Area(unsigned int& id, std::string& name);
    void addRoom(std::unique_ptr<Room> room);
    const std::vector<std::unique_ptr<Room>>& getRooms(){return rooms;};
private:
    std::string name;
    unsigned id;
    std::vector<std::unique_ptr<Room>> rooms;
};
#endif //OOP_AREA_H
