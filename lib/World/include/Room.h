
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
    Room(int id, std::string name);
    void addDescription(std::string description);
    void addExtendedDescription(std::string extDescription);
    unsigned int const& getId() const{return id;};
    std::string const& getName() const{return name;};
    std::vector<std::string> const& getDescriptions() const{return descriptions;};
    std::vector<std::string> const& getExtendedDescriptions() const{return extendedDescriptions;};
    std::vector<int> const& getCharacterList() const{return characterList;};
    std::vector<int> const& getObjectList() const{return objectList;};
    bool addCharacter(int characterId);
    bool removeCharacter(int characterId);
    bool addObject(int objectId);
    bool removeObject(int objectId);

    // use character 'n','e','s','w' to represent direction
    // it will assign targetRoom to the coordinate Room*
    void linkRoom(char dir, int targetRoomId);

    int const& getNorth() const{return north;};
    int const& getEast() const{return east;};
    int const& getSouth() const{return south;};
    int const& getWest() const{return west;};


private:
    unsigned int  id;
    std::string name;
    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;
    std::vector<int> characterList;
    std::vector<int> objectList;
    int north;
    int east;
    int south;
    int west;
};


#endif //OOP_ROOM_H
