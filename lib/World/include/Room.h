
#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <vector>
#include <string>
#include "Room.h"
#include "Door.h"
#include <memory>


class Room
{
public:
    Room(unsigned int  id, std::string& name);
    void addDescription(std::string& description);
    void addExtendedDescription(std::string& extDescription);
    const unsigned int& getId(){return id;};
    const std::string& getName(){return name;};
    const std::vector<std::string>& getDescriptions(){return descriptions;};
    const std::vector<std::string>& getExtendedDescriptions(){return extendedDescriptions;};
    const std::vector<std::unique_ptr<Door>>& getDoors(){return doors;};
    void join(int objectId);
    void quit(int objectId);
    void addDoor(std::unique_ptr<Door>& door);

private:
    unsigned int  id;
    std::string name;
    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;
    std::vector<std::unique_ptr<Door>> doors;
    std::vector<unsigned int> objectIdList;

};


#endif //OOP_ROOM_H
