//
// Created by evan on 30/01/19.
//

#include <algorithm>
#include <RoomController.h>

RoomController::RoomController() = default;

bool RoomController::generateRoom(unsigned int roomId, const std::string& roomName) {
    auto size = RoomController::roomList.size();
    auto tempRoom = RoomController::searchRoom(roomId);

    if (tempRoom == nullptr)
        RoomController::roomList.emplace_back(roomId,roomName);

    return size != RoomController::roomList.size();
}

bool RoomController::removeRoom(int roomId) {
    auto size = RoomController::roomList.size();

    auto it = std::find_if(RoomController::roomList.begin(), RoomController::roomList.end(),
            [&roomId](const Room& room)
            {return room.getId() == roomId;}
            );
    RoomController::roomList.erase(it);

    return size != roomList.size();
}

const std::vector<int> & RoomController::getCharacterList(int roomId) {
    return RoomController::searchRoom(roomId)->getCharacterList();
}

const std::vector<int> & RoomController::getObjectList(int roomId) {
    return RoomController::searchRoom(roomId)->getObjectList();
}

std::vector<int> RoomController::getRoomList() const {
    std::vector<int> integerRoomList;

    std::transform(RoomController::roomList.begin(), RoomController::roomList.end(),
            std::back_inserter(integerRoomList),
            [](auto room){return room.getId();});

    return integerRoomList;
}

bool RoomController::addCharacterToRoom(int characterId, int roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);

    return (tempRoom != nullptr) && (tempRoom->addCharacter(characterId));
}

bool RoomController::removeCharacterFromRoom(int characterId, int roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);

    return (tempRoom != nullptr) && (tempRoom->removeCharacter(characterId));
}

bool RoomController::addObjectToRoom(int objectId, int roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);

    return (tempRoom != nullptr) && (tempRoom->addObject(objectId));
}

bool RoomController::removeObjectFromRoom(int objectId, int roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);

    return (tempRoom != nullptr) && (tempRoom->removeObject(objectId));
}

void RoomController::linkRoom(char dir, int room1Id, int room2Id) {
    auto room = searchRoom(room1Id);
    room->linkRoom(dir, room2Id);
}

int RoomController::getLinkedRoom(char dir, int roomId) {
    auto room = searchRoom(roomId);
    return room->getLinkedRoom(dir);
}

Room* RoomController::searchRoom(int roomId) {

    auto tempRoom = std::find_if(RoomController::roomList.begin(), RoomController::roomList.end(),
                                 [&roomId](const Room& room)
                                 {return room.getId() == roomId;}
    );

    // if room not found
    if (tempRoom == RoomController::roomList.end())
        return nullptr;

    return tempRoom.base();
}