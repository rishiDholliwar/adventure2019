#include <algorithm>
#include <Room.h>

Room::Room(ID id, const Name& name){
    this->id = id;
    this->name = name;
}

/*
 *  Adders
*/

void Room::addDescription(const std::string& description) {
    descriptions.push_back(description);
}

void Room::addExtendedDescription(const std::string& extDescription) {
    extendedDescriptions.push_back(extDescription);
}

void Room::addKeywords(const std::string &keyword) {
    keywords.push_back(keyword);
}

bool Room::addObject(ID objectId) {
    return addUniqueItemToList(objectId, this->objectList);
}

bool Room::addCharacter(const Name &userName) {
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
