//
// Created by evan on 30/01/19.
//

#include <algorithm>
#include <RoomController.h>

RoomController::RoomController() {

    generateRoom(1000, "Room1");
    generateRoom(1001, "Room2");
    generateRoom(1002, "Room3");
    generateRoom(1003, "Room4");


    linkRoom(Direction::NORTH, 1000, 1001);
    linkRoom(Direction::EAST, 1001, 1002);
    linkRoom(Direction::SOUTH, 1002, 1003);
    linkRoom(Direction::WEST, 1003, 1000);
};


/*
 * Getters
 */
const std::vector<ID> & RoomController::getCharacterList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        return emptyIdVector;
    }

    return room->getCharacterList();
}

const std::vector<ID> & RoomController::getObjectList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        return emptyIdVector;
    }

    return room->getObjectList();
}

const std::vector<std::string> & RoomController::getUsernameList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        return emptyStringVector;
    }

    return room->getUsernameList();
}

std::vector<ID> RoomController::getRoomIdList() const {
    std::vector<ID> integerRoomList;

    std::transform(this->roomList.begin(), this->roomList.end(),
            std::back_inserter(integerRoomList),
            [](auto room){return room.getId();});

    return integerRoomList;
}

/*
 * Adders
 */

bool RoomController::generateRoom(ID roomId, const std::string& roomName) {
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
void RoomController::linkRoom(Direction dir, ID room1Id, ID room2Id) {
    auto room = searchRoom(room1Id);
    if (room != nullptr) {
        room->linkRoom(dir, room2Id);
    }
}

ID RoomController::getLinkedRoom(Direction dir, ID roomId) {
    auto room = searchRoom(roomId);
    return room->getLinkedRoom(dir);
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