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

struct RoomDeleter {
    void operator()(Room* room);
};

class Area
{
public:
    Area(unsigned int id, std::unique_ptr<std::string>  name);
    void addRoom(std::unique_ptr<Room,RoomDeleter> room);
    const std::vector<std::unique_ptr<Room,RoomDeleter>>& getRooms(){return rooms;};
private:
    unsigned int id;
    std::unique_ptr<std::string>  name;
    std::vector<std::unique_ptr<Room,RoomDeleter>> rooms;
};
#endif //OOP_AREA_H
