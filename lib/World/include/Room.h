
#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include <Room.h>
#include <Door.h>
#include <memory>

class Room
{
public:
    Room(unsigned int& id, string& name);
    void addDescription(string& description);
    void addExtendedDescription(string& extDescription);
    const vector<string>& getDescriptions(){return descriptions;};
    const vector<string>& getExtendedDescriptions(){return extendedDescriptions;};
    const vector<std::unique_ptr<Door>> getDoors(){return doors;};
    void join(int& objectId);
    void quit(int& objectId);
    void addDoor(std::unique_ptr<Door> door);

private:
    unsigned id;
    string name;
    vector<string> descriptions;
    vector<string> extendedDescriptions;
    vector<std::unique_ptr<Door>> doors;
    vector<unsigned> objectIdList;

};


#endif //OOP_ROOM_H
