
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
    Room(unsigned int  id, std::string name);
    void addDescription(std::string description);
    void addExtendedDescription(std::string extDescription);
    unsigned int const& getId() const{return id;};
    std::string const& getName() const{return name;};
    std::vector<std::string> const& getDescriptions() const{return descriptions;};
    std::vector<std::string> const& getExtendedDescriptions() const{return extendedDescriptions;};
    //void join(Character* objectId);
    //void quit(Character* objectId);

    // use character 'n','e','s','w' to represent direction
    // it will assign targetRoom to the coordinate Room*
    void linkRoom(char dir, Room* targetRoom);

    Room* const& getNorth() const{return north;};
    Room* const& getEast() const{return east;};
    Room* const& getSouth() const{return south;};
    Room* const& getWest() const{return west;};


private:
    unsigned int  id;
    std::string name;
    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;
    //std::vector<Character*> characterList;
    Room* north;
    Room* east;
    Room* south;
    Room* west;
};


#endif //OOP_ROOM_H
