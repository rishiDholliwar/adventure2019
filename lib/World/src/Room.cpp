#include <algorithm>
#include <Room.h>


/*
 *  Adders
*/

void Room::addDescription(const std::string& description) {
    this->descriptions.push_back(description);
}

void Room::addCharacter(const Name &userName){
    this->characterList.push_back(userName);
}

void Room::addObject(ID objectId) {
    this->objectList.push_back(objectId);
}

bool Room::addUserName(const Name &userName) {
    return addUniqueItemToList(userName, this->characterList);
}
/*
 *  Removers
 */



bool Room::removeObject(ID objectId) {
    return removeUniqueItemFromList(objectId, this->objectList);
}

bool Room::removeCharacter(const Name &userName) {
    return removeUniqueItemFromList(userName, this->characterList);
}

/*
 *  Link Rooms
 */

bool Room::addDoor(ID doorId, ID designatedRoomId, const std::string &direction) {
    auto size = this->doorList.size();
    auto it = std::find_if(this->doorList.begin(), this->doorList.end(),
                  [&doorId](const Door& door)
                  {return door.getId() == doorId;});

    // if id not exist
    if(it == this->doorList.end()) {
        this->doorList.emplace_back(doorId, designatedRoomId, direction);
    }

    return size != this->doorList.size();
}

bool Room::removeDoor(ID doorId) {
    auto list= this->doorList;

    auto size = list.size();
    auto it = std::find_if(list.begin(), list.end(),
            [&doorId](const Door& door)
            {return door.getId() == doorId;});

    // if id exist
    if (it != list.end())
        list.erase(it);

    return size != list.size();
}

void Room::removeDoorByDirection(const std::string& direction) {
    auto it = std::find_if(doorList.begin(), doorList.end(),
            [&direction](const Door& door)
            {return door.getDirection() == direction;});

    // if id exist
    if (it != doorList.end()) {
        doorList.erase(it);
    }
}

std::string Room::getTextOfRoomDetails() {
    std::stringstream outputString;
    outputString << "Room ID: " << this->getId() << "\n" <<
                    "Room Name: " << this->getName() << "\n";

    for (auto &description : this->descriptions){
        outputString << description << "\n";
    }

    for (auto &description : this->extendedDescriptions){
        //outputString << description << "\n";
    }

    outputString << getTextOfDoorDetails();
    return outputString.str();
}

std::string Room::getTextOfDoorDetails() {
    std::stringstream outputString;
    outputString << "Doors ID, Direction, Destination, Status\n";
    for (const auto &door: this->doorList){
        ID doorId = door.getId();
        outputString << doorId << ", " << door.getDirection() <<
                        ", " << door.getDesignatedRoomId() << ", ";
        if (door.getStatus()){
            outputString << "Unlocked";
        }else{
            outputString << "Locked";
        }
        outputString << "\n";
    }
    return outputString.str();
}

Door* Room::searchDoor(ID doorId) {

    auto it = std::find_if(doorList.begin(), doorList.end(),
                           [&doorId](const Door& door)
                           {return door.getId() == doorId;});

    if (it != doorList.end()) {
        return it.base();
    }else{
        return nullptr;
    }
}

Door* Room::searchDoorByDirection(const std::string& direction) {
    auto it = std::find_if(doorList.begin(), doorList.end(),
                           [&direction](const Door& door)
                           {return door.getDirection() == direction;});

    if (it != doorList.end()) {
        return it.base();
    }else{
        return nullptr;
    }
}

/*
 *  private functions
 */

template <typename T>
bool Room::addUniqueItemToList(T id, std::vector<T> &list) {
    auto size = list.size();
    auto it = std::find(list.begin(), list.end(),id);

    // if id not exist
    if(it == list.end())
        list.push_back(id);

    return size != list.size();
}

template <typename T>
bool Room::removeUniqueItemFromList(T id, std::vector<T> &list) {
    auto size = list.size();
    auto it = std::find(list.begin(), list.end(), id);

    // if id exist
    if (it != list.end())
        list.erase(it);

    return size != list.size();
}

Room::Room(ID id, const Name &name, const std::vector<std::string> &descriptions, const std::vector<Door> &doorList,
           const std::vector<ExtendedDescription> &extendedDescriptions) : id(id), name(name),
                                                                           descriptions(descriptions),
                                                                           doorList(doorList),
                                                                           extendedDescriptions(extendedDescriptions) {}