
#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include <Room.h>
#include <Door.h>
using namespace std;

class Room
{
public:
    Room();
private:
    unsigned id;
    string name;
    vector<string> descriptions;
    vector<string> extendedDescriptions;
    vector<Door> doors;

};


#endif //OOP_ROOM_H
