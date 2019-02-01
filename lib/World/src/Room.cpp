#include <algorithm>
#include "Room.h"

Room::Room(int id, std::string name){
    Room::id = id;
    Room::name = std::move(name);
    Room::north = 0;
    Room::east = 0;
    Room::south = 0;
    Room::west = 0;
}

void Room::addDescription(std::string description) {
    Room::descriptions.push_back(std::move(description));
}

void Room::addExtendedDescription(std::string extDescription) {
    Room::extendedDescriptions.push_back(std::move(extDescription));
}

void Room::linkRoom(char dir, int targetRoomId) {
    if (dir == 'n')
        Room::north = targetRoomId;
    else if (dir =='e')
        Room::east = targetRoomId;
    else if (dir =='s')
        Room::south = targetRoomId;
    else if (dir =='w')
        Room::west = targetRoomId;
}

int Room::getLinkedRoom(char dir) {
    int targetRoomId;

    if (dir == 'n')
        targetRoomId = Room::north;
    else if (dir =='e')
        targetRoomId = Room::east;
    else if (dir =='s')
        targetRoomId = Room::south;
    else if (dir =='w')
        targetRoomId = Room::west;
    else
        targetRoomId = 0;

    return targetRoomId;
}

bool Room::addCharacter(int characterId) {
    auto size = Room::characterList.size();
    auto it = std::find(Room::characterList.begin(), Room::characterList.end(), characterId);

    // check if character id exist
    if(it == Room::characterList.end())
        Room::characterList.push_back(characterId);

    return size != Room::characterList.size();
}

bool Room::removeCharacter(int characterId) {
    auto size = Room::characterList.size();
    auto it = std::find(characterList.begin(), characterList.end(), characterId);

    if(it != Room::characterList.end())
        Room::characterList.erase(it);


    return size != Room::characterList.size();
}

bool Room::addObject(int objectId) {
    auto size = Room::objectList.size();
    auto it = std::find(Room::objectList.begin(), Room::objectList.end(),objectId);

    // check if character id exist
    if(it == Room::objectList.end())
        Room::objectList.push_back(objectId);

    return size != Room::objectList.size();
}

bool Room::removeObject(int objectId) {
    auto size = Room::objectList.size();
    auto it = std::find(Room::objectList.begin(), Room::objectList.end(), objectId);

    if (it != Room::objectList.end())
        Room::objectList.erase(it);

    return size != Room::objectList.size();
}