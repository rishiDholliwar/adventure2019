//
// Created by evan on 30/01/19.
//

#include <algorithm>
#include "RoomControllor.h"

RoomControllor::RoomControllor() = default;

bool RoomControllor::generateRoom(unsigned int roomId, std::string roomName) {
    auto size = RoomControllor::roomList.size();
    auto tempRoom = RoomControllor::searchRoom(roomId);

    if (tempRoom == nullptr)
        RoomControllor::roomList.emplace_back(roomId,roomName);

    return size != RoomControllor::roomList.size();
}

bool RoomControllor::removeRoom(int roomId) {
    auto size = RoomControllor::roomList.size();

    auto it = std::find_if(RoomControllor::roomList.begin(), RoomControllor::roomList.end(),
            [&roomId](const Room& room)
            {return room.getId() == roomId;}
            );
    RoomControllor::roomList.erase(it);

    return size != roomList.size();
}

const std::vector<int> & RoomControllor::getCharacterList(int roomId) {
    return RoomControllor::searchRoom(roomId)->getCharacterList();
}

const std::vector<int> & RoomControllor::getObjectList(int roomId) {
    return RoomControllor::searchRoom(roomId)->getObjectList();
}

std::vector<int> RoomControllor::getRoomList() const {
    std::vector<int> integerRoomList;

    std::transform(RoomControllor::roomList.begin(), RoomControllor::roomList.end(),
            std::back_inserter(integerRoomList),
            [](auto room){return room.getId();});

    return integerRoomList;
}

bool RoomControllor::addCharacterToRoom(int characterId, int roomId) {
    auto tempRoom = RoomControllor::searchRoom(roomId);

    return (tempRoom != nullptr) && (tempRoom->addCharacter(characterId));
}

bool RoomControllor::removeCharacterFromRoom(int characterId, int roomId) {
    auto tempRoom = RoomControllor::searchRoom(roomId);

    return (tempRoom != nullptr) && (tempRoom->removeCharacter(characterId));
}

bool RoomControllor::addObjectToRoom(int objectId, int roomId) {
    auto tempRoom = RoomControllor::searchRoom(roomId);

    return (tempRoom != nullptr) && (tempRoom->addObject(objectId));
}

bool RoomControllor::removeObjectFromRoom(int objectId, int roomId) {
    auto tempRoom = RoomControllor::searchRoom(roomId);

    return (tempRoom != nullptr) && (tempRoom->removeObject(objectId));
}

void RoomControllor::linkRoom(char dir, int room1Id, int room2Id) {
    auto room = searchRoom(room1Id);
    room->linkRoom(dir, room2Id);
}

int RoomControllor::getLinkedRoom(char dir, int roomId) {
    auto room = searchRoom(roomId);
    return room->getLinkedRoom(dir);
}

Room* RoomControllor::searchRoom(int roomId) {

    auto tempRoom = std::find_if(RoomControllor::roomList.begin(), RoomControllor::roomList.end(),
                                 [&roomId](const Room& room)
                                 {return room.getId() == roomId;}
    );

    // if room not found
    if (tempRoom == RoomControllor::roomList.end())
        return nullptr;

    return tempRoom.base();
}