//
// Created by evan on 30/01/19.
//

#include <algorithm>
#include "RoomControllor.h"

RoomControllor::RoomControllor() = default;

bool RoomControllor::generateRoom(unsigned int roomId, std::string roomName) {
    auto tempRoom = RoomControllor::searchRoom(roomId);
    if (tempRoom != nullptr)
        return false;
    RoomControllor::roomList.emplace_back(roomId,roomName);
    return true;
}

void RoomControllor::removeRoom(int roomId) {
    std::remove_if(RoomControllor::roomList.begin(), RoomControllor::roomList.end(),
            [&roomId](const Room& room)
            {return room.getId() == roomId;}
            );
}

const std::vector<int> & RoomControllor::getCharacterList(int roomId) {
    return RoomControllor::searchRoom(roomId)->getCharacterList();
}

const std::vector<int> & RoomControllor::getObjectList(int roomId) {
    return RoomControllor::searchRoom(roomId)->getObjectList();
}

std::vector<int> RoomControllor::getRoomList() const {
    std::vector<int> integerRoomList;
    for (const Room &room : RoomControllor::roomList){
        integerRoomList.push_back(room.getId());
    }
    return integerRoomList;
}

bool RoomControllor::addCharacterToRoom(int characterId, int roomId) {
    auto tempRoom = RoomControllor::searchRoom(roomId);
    if (tempRoom == nullptr)
        return false;

    return tempRoom->addCharacter(characterId);
}

bool RoomControllor::removeCharacterFromRoom(int characterId, int roomId) {
    auto tempRoom = RoomControllor::searchRoom(roomId);
    if (tempRoom == nullptr)
        return false;

    return tempRoom->removeCharacter(characterId);
}

bool RoomControllor::addObjectToRoom(int objectId, int roomId) {
    auto tempRoom = RoomControllor::searchRoom(roomId);
    if (tempRoom == nullptr)
        return false;

    return tempRoom->addObject(objectId);
}

bool RoomControllor::removeObjectFromRoom(int objectId, int roomId) {
    auto tempRoom = RoomControllor::searchRoom(roomId);
    if (tempRoom == nullptr)
        return false;

    return tempRoom->removeObject(objectId);
}

Room* RoomControllor::searchRoom(int roomId) {

    auto tempRoom = std::find_if(RoomControllor::roomList.begin(), RoomControllor::roomList.end(),
                                 [&roomId](const Room& room)
                                 {return room.getId() == roomId;}
    );

    // if room not found
    if (tempRoom == RoomControllor::roomList.end())
        return nullptr;
    Room* room = tempRoom.base();

    return room;
}