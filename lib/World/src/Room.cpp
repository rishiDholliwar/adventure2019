#include <algorithm>
#include "Room.h"

Room::Room(unsigned int id, std::string name){
    Room::id = id;
    Room::name = std::move(name);
}

void Room::addDescription(std::string description) {
    Room::descriptions.push_back(std::move(description));
}

void Room::addExtendedDescription(std::string extDescription) {
    Room::extendedDescriptions.push_back(std::move(extDescription));
}

void Room::linkRoom(char dir, Room* targetRoom) {
    if (dir == 'n')
        Room::north = targetRoom;
    else if (dir =='e')
        Room::east = targetRoom;
    else if (dir =='s')
        Room::south = targetRoom;
    else if (dir =='w')
        Room::west = targetRoom;

}

//void Room::join(Character* character) {
//    Room::objectIdList.push_back(objectId);
//}
//
//void Room::quit(Character* character) {
//    std::remove(objectIdList.begin(), objectIdList.end(), objectId);
//}
