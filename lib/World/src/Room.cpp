#include <algorithm>
#include "Room.h"

Room::Room(int id, std::string name){
    Room::id = id;
    Room::name = std::move(name);
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

bool Room::addCharacter(int characterId) {
//    auto tempVector = Room::characterList;
//    auto tempId = std::find(tempVector.begin(), tempVector.end(), characterId);
//    // check if character id exist
//    if(tempId != tempVector.end())
//        return false;

    Room::characterList.push_back(characterId);
    return true;
}

bool Room::removeCharacter(int characterId) {
    std::remove(characterList.begin(), characterList.end(), characterId);
    return true;
}

bool Room::addObject(int objectId) {
    auto tempVector = Room::objectList;
    auto tempId = std::find(tempVector.begin(), tempVector.end(),objectId);
    // check if character id exist
    if(tempId != tempVector.end())
        return false;

    tempVector.push_back(objectId);
    return true;;
}

bool Room::removeObject(int objectId) {
    std::remove(objectList.begin(), objectList.end(), objectId);
    return true;
}