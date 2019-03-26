
#include <algorithm>
#include <RoomController.h>
#include <iostream>

RoomController::RoomController(){}

RoomController::RoomController(const std::vector<Room> roomList) : roomList(roomList) {}



/*
 * Getters
 */
const std::vector<ID> & RoomController::getCharacterList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        static std::vector<ID> emptyIdVector;
        return emptyIdVector;
    }

    return room->getCharacterList();
}

const std::vector<ID> & RoomController::getObjectList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        static std::vector<ID> emptyIdVector;
        return emptyIdVector;
    }

    return room->getObjectList();
}

const std::vector<Name>& RoomController::getUsernameList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        static std::vector<std::string> emptyStringVector;
        return emptyStringVector;
    }

    return room->getUsernameList();
}

std::vector<ID> RoomController::getRoomIdList() const {
    std::vector<ID> integerRoomList{};

    std::transform(this->roomList.begin(), this->roomList.end(),
            std::back_inserter(integerRoomList),
            [](auto room){return room.getId();});

    return integerRoomList;
}

/*
 * Adders
 */

bool RoomController::generateRoom(ID roomId, const Name& roomName) {
    auto tempRoom = RoomController::searchRoom(roomId);

    if (tempRoom == nullptr) {
//        this->roomList.emplace_back(roomId, roomName);
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

bool RoomController::addUserNameToRoom(const Name &userName, ID roomId) {
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

bool RoomController::removeUserNameFromRoom(const Name &userName, ID roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->removeUserName(userName));
}

/*
 *  Link Rooms
 */
bool RoomController::addDoorToRoom(ID roomId, ID doorId,
                                   ID designatedRoomId, const std::string &direction) {
    auto room = searchRoom(roomId);
    auto designatedRoom = searchRoom(designatedRoomId);
    return (room!=nullptr) && (designatedRoom != nullptr)&& (room->addDoor(doorId, designatedRoomId, direction));
}

bool RoomController::removeDoorFromRoom(ID roomId, ID doorId) {
    auto room = searchRoom(roomId);
    return (room!=nullptr) && room->removeDoor(doorId);
}

std::string RoomController::getTextOfRoomDetails(ID roomId) {
    auto room = searchRoom(roomId);
    if (room == nullptr){
        static std::string roomNotFoundMessage = "Room does not exist.";
        return roomNotFoundMessage;
    }
    return room->getTextOfRoomDetails();
}

ID RoomController::getDoorIdByDirection(ID roomId, const std::string &direction) {
    auto room = searchRoom(roomId);
    if (room == nullptr){
        return Door::unfoundDoorId;
    }

    auto door = room->searchDoorByDirection(direction);
    if (door == nullptr){
        return Door::unfoundDoorId;
    }

    return door->getId();
}

Door::DoorStatus RoomController::getDoorStatus(ID roomId, const std::string& direction) {
    auto door = searchDoor(roomId, direction);
    return door->getStatus();
}

ID RoomController::getDoorDesignatedRoomId(ID roomId, const std::string& direction) {
    auto door = searchDoor(roomId, direction);
    if (door == nullptr){
        return Door::unfoundDoorId;
    }
    return door->getDesignatedRoomId();
}

bool RoomController::doesDirectionExist(ID roomId, const std::string& direction) {
    auto door = searchDoor(roomId, direction);
    if (door == nullptr){
        const static std::string doorNotFoundMessage = "Door does not exist.\n";
        return false;
    }
    return true;
}


/*
 * search functions
 */

Room* RoomController::searchRoom(ID roomId) {
    auto tempRoom = std::find_if(roomList.begin(), roomList.end(),
                                 [&roomId](const Room& room)
                                 {return room.getId() == roomId;}
    );

    // if room not found
    if (tempRoom == this->roomList.end())
        return nullptr;

    return tempRoom.base();
}

Door* RoomController::searchDoor(ID roomId, const std::string &direction) {
    auto room = searchRoom(roomId);
    if (room == nullptr){
        return nullptr;
    }

    return room->searchDoorByDirection(direction);
}

const std::vector<Room> &RoomController::getRoomList() const {
    return roomList;
}




