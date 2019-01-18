//
// Created by rishi on 1/17/19.
//

#ifndef OOP_AREA_H
#define OOP_AREA_H

#include <vector>
#include <string>
#include <Area.h>
#include <Room.h>

using namespace std;

class Area
{
public:
    Area(unsigned int id, string name);
    void addRoom(Room& room);
private:
    string name;
    unsigned id;
    vector<Room> rooms;
};
#endif //OOP_AREA_H
