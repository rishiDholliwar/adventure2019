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

using namespace std;

class Area
{
public:
    Area(unsigned int& id, string& name);
    void addRoom(std::unique_ptr<Room> room);
private:
    string name;
    unsigned id;
    vector<std::unique_ptr<Room>> rooms;
};
#endif //OOP_AREA_H
