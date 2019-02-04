#include <algorithm>
#include <Room.h>

Room::Room(ID id, const std::string& name){
    this->id = id;
    this->name = name;
}

/*
 *  Adders
*/

void Room::addDescription(const std::string& description) {
    this->descriptions.push_back(description);
}

void Room::addExtendedDescription(const std::string& extDescription) {
    this->extendedDescriptions.push_back(extDescription);
}

bool Room::addCharacter(ID characterId) {
    return addUniqueItemToList(characterId, this->characterList);
}

bool Room::addObject(ID objectId) {
    return addUniqueItemToList(objectId, this->objectList);
}

bool Room::addUserName(const std::string &userName) {
    return addUniqueItemToList(userName, this->usernameList);
}
/*
 *  Removers
 */

bool Room::removeCharacter(ID characterId) {
    return removeUniqueItemFromList(characterId, this->characterList);
}

bool Room::removeObject(ID objectId) {
    return removeUniqueItemFromList(objectId, this->objectList);
}

bool Room::removeUserName(const std::string &userName) {
    return removeUniqueItemFromList(userName, this->usernameList);
}
/*
 *  Link Rooms
 */

void Room::linkRoom(Direction dir, ID targetRoomId) {
    if (dir == Direction::NORTH)
        this->linkingRoomList.north = targetRoomId;
    else if (dir == Direction::EAST)
        this->linkingRoomList.east = targetRoomId;
    else if (dir == Direction::SOUTH)
        this->linkingRoomList.south = targetRoomId;
    else if (dir == Direction::WEST)
        this->linkingRoomList.west = targetRoomId;
}

ID Room::getLinkedRoom(Direction dir) {
    ID targetRoomId;

    if (dir == Direction::NORTH)
        targetRoomId = this->linkingRoomList.north;
    else if (dir == Direction::EAST)
        targetRoomId = this->linkingRoomList.east;
    else if (dir == Direction::SOUTH)
        targetRoomId = this->linkingRoomList.south;
    else if (dir == Direction::WEST)
        targetRoomId = this->linkingRoomList.west;
    else
        targetRoomId = 0;

    return targetRoomId;
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

bool Room::hasObject(ID objectId) {
    return std::find(this->objectList.begin(), this->objectList.end(), id) != this->objectList.end();
}
