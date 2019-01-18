
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
    Room(unsigned int id, string name);
    void addDescription(const string& description);
    void addExtendedDescription(const string& extDescription);
    const vector<string>& getDescriptions(){return descriptions;};
    const vector<string>& getExtendedDescriptions(){return extendedDescriptions;};
    const vector<Door>& getDoors(){return doors;};
    void join(const int objectId);
    void quit(const int objectId);
    void addDoor(Door& door);

private:
    unsigned id;
    string name;
    vector<string> descriptions;
    vector<string> extendedDescriptions;
    vector<Door> doors;
    vector<unsigned> objectIdList;

};


#endif //OOP_ROOM_H
