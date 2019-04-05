#include <algorithm>
#include <RoomController.h>
#include <iostream>

RoomController::RoomController(){}

RoomController::RoomController(const std::vector<Room> roomList) : roomList(roomList) {
    for(Room& room : this->roomList) {
        auto& doors = room.getDoorList();
        for(auto& door : doors ) {
            if(searchRoom(door.getDesignatedRoomId()) == nullptr) {
                std::cout << "In room: " << room.getName() << std::endl;
                std::cout << "Deleted door to: " << door.getDesignatedRoomId() << std::endl;
                room.removeDoorByDirection(door.getDirection());
            }
        }
    }
}

/*
 * Getters
 */

const std::vector<ID> & RoomController::getObjectList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        static std::vector<ID> emptyIdVector;
        return emptyIdVector;
    }

    return room->getObjectList();
}

const std::vector<Name>& RoomController::getCharacterList(ID roomId) {
    auto room = RoomController::searchRoom(roomId);

    if (room == nullptr){
        static std::vector<std::string> emptyStringVector;
        return emptyStringVector;
    }

    return room->getCharacterList();
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

bool RoomController::addObjectToRoom(ID objectId, ID roomId) {
    auto tempRoom = this->searchRoom(roomId);
    if(tempRoom != nullptr) {
        tempRoom->addObject(objectId);
    }
    return (tempRoom != nullptr);
}

bool RoomController::addCharacterToRoom(const Name &userName, ID roomId) {
    auto tempRoom = this->searchRoom(roomId);
    if(tempRoom != nullptr) {
        tempRoom->addCharacter(userName);
    }
    return (tempRoom != nullptr);
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

bool RoomController::removeObjectFromRoom(ID objectId, ID roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->removeObject(objectId));
}

bool RoomController::removeCharacterFromRoom(const Name &userName, ID roomId) {
    auto tempRoom = RoomController::searchRoom(roomId);
    return (tempRoom != nullptr) && (tempRoom->removeCharacter(userName));
}

void RoomController::lockDoor(ID roomID, std::string& direction) {
    auto door = searchDoor(roomID, direction);
    door->setDoorLocked();
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

std::string RoomController::getRoomDescription(ID roomId) {
    auto room = searchRoom(roomId);
    if (room == nullptr){
        static std::string roomNotFoundMessage = "Room does not exist.";
        return roomNotFoundMessage;
    }

    std::stringstream outputString;
    std::string indentation = "\t";
    outputString << "Room Name: " << room->getName() << "\n";

    auto descriptions = room->getDescriptions();
    for (auto &description : descriptions){
        outputString << indentation << description << "\n";
    }

    return outputString.str();
}

std::string RoomController::getAllDoorInformationInRoom(ID roomId) {
    auto room = searchRoom(roomId);
    if (room == nullptr){
        static std::string roomNotFoundMessage = "Room does not exist.";
        return roomNotFoundMessage;
    }

    std::stringstream outputString;
    std::string indentation = "\t";
    outputString << "Direction Information:\n";
    auto doorList = room->getDoorList();
    for (const auto &door: doorList){
        ID doorId = door.getId();
        outputString << indentation <<door.getDirection() << " ";
        if (door.getStatus()){
            outputString << "(Unlocked)";
        }else{
            outputString << "(Locked)";
        }
        outputString << "\n";
    }

    return outputString.str();
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

bool RoomController::moveCharacter(Name username, ID originRoomId, ID destinationRoomId) {{
        removeCharacterFromRoom(username, originRoomId);
        addCharacterToRoom(username, destinationRoomId);
}}

bool RoomController::isDoorExist(ID roomId, std::string &direction) {
    auto door = searchDoor(roomId, direction);
    return door != nullptr;
}

bool RoomController::isDoorLocked(ID roomId, std::string &direction) {
    auto door = searchDoor(roomId, direction);
    if (door == nullptr){
        return true;
    }
    Door::DoorStatus status = door->getStatus();
    return status == Door::DoorStatus::LOCKED;
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

std::vector<ID> RoomController::adjacentRoomIDs(ID roomID) {
    auto room = RoomController::searchRoom(roomID);
    std::vector<ID> adjacentRoomID;
    if (room == nullptr){
      return adjacentRoomID;
    }
    for(auto& door: room->getDoorList()){
        adjacentRoomID.push_back(door.getDesignatedRoomId());
    }

    return adjacentRoomID;
}

const std::vector<Room> &RoomController::getRoomList() const {
    return roomList;
}




