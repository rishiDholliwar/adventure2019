//
// Created by evan on 30/01/19.
//

#include <algorithm>
#include <RoomController.h>

RoomController::RoomController() = default;

/*
 * Getters
 */
const std::vector<RoomController::ID> & RoomController::getCharacterList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        return emptyIdVector;
    }

    return room->getCharacterList();
}

const std::vector<RoomController::ID> & RoomController::getObjectList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        return emptyIdVector;
    }

    return room->getObjectList();
}

const std::vector<std::string>& RoomController::getUsernameList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        return emptyStringVector;
    }

    return room->getUsernameList();
}

std::vector<RoomController::ID> RoomController::getRoomIdList() const {
    std::vector<RoomController::ID> integerRoomList;

    std::transform(this->roomList.begin(), this->roomList.end(),
            std::back_inserter(integerRoomList),
            [](auto room){return room.getId();});

    return integerRoomList;
}

/*
 * Adders
 */

bool RoomController::generateRoom(RoomController::ID roomId, const std::string& roomName) {
    auto tempRoom = RoomController::searchRoom(roomId);

    if (tempRoom == nullptr) {
        this->roomList.emplace_back(roomId, roomName);
    }

    return !tempRoom;
}

bool RoomController::addCharacterToRoom(ID characterId, ID roomId) {
    auto tempRoom = this->searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->addCharacter(characterId));
}

bool RoomController::addObjectToRoom(ID objectId, ID roomId) {
    auto tempRoom = this->searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->addObject(objectId));
}

bool RoomController::addUserNameToRoom(const std::string &userName, ID roomId) {
    auto tempRoom = this->searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->addUserName(userName));
}

/*
 * Removers
 */

bool RoomController::removeRoom(ID roomId) {
    auto size = this->roomList.size();

    auto it = std::find_if(this->roomList.begin(), this->roomList.end(),
                           [&roomId](const Room& room)
                           {return room.getId() == roomId;}
    );

    if (it != this->roomList.end()) {
        this->roomList.erase(it);
    }

    return size != this->roomList.size();
}

bool RoomController::removeCharacterFromRoom(ID characterId, ID roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->removeCharacter(characterId));
}

bool RoomController::removeObjectFromRoom(ID objectId, ID roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->removeObject(objectId));
}

bool RoomController::removeUserNameFromRoom(const std::string &userName, ID roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->removeUserName(userName));
}

/*
 *  Link Rooms
 */
bool RoomController::addDoorToRoom(RoomController::ID roomId, RoomController::ID doorId,
                                   RoomController::ID destinatedRoomId, const std::string &direction) {
    auto room = searchRoom(roomId);
    return room->addDoor(doorId, destinatedRoomId, direction);
}

bool RoomController::removeDoorFromRoom(RoomController::ID roomId, ID doorId) {
    auto room = searchRoom(roomId);
    return room->removeDoor(doorId);
}

std::string RoomController::getTextOfRoomDetails(RoomController::ID roomId) {
    auto room = searchRoom(roomId);
    return room->getTextOfRoomDetails();
}

/*
 * private functions
 */

Room* RoomController::searchRoom(ID roomId) {

    auto tempRoom = std::find_if(this->roomList.begin(), this->roomList.end(),
                                 [&roomId](const Room& room)
                                 {return room.getId() == roomId;}
    );

    // if room not found
    if (tempRoom == this->roomList.end())
        return nullptr;

    return tempRoom.base();
}

