#include <algorithm>
#include <Room.h>

Room::Room(int id, const std::string& name){
    Room::id = id;
    Room::name = name;
    Room::north = 0;
    Room::east = 0;
    Room::south = 0;
    Room::west = 0;
}

/*
 *  Adders
*/

void Room::addDescription(const std::string& description) {
    Room::descriptions.push_back(description);
}

void Room::addExtendedDescription(const std::string& extDescription) {
    Room::extendedDescriptions.push_back(extDescription);
}

bool Room::addCharacter(int characterId) {
    return addIdToList(characterId, Room::characterList);
}

bool Room::addObject(int objectId) {
    return addIdToList(objectId, Room::objectList);
}

/*
 *  Removers
 */

bool Room::removeCharacter(int characterId) {
    return removeIdFromList(characterId, Room::characterList);
}

bool Room::removeObject(int objectId) {
    return removeIdFromList(objectId, Room::objectList);
}

/*
 *  Link Rooms
 */

void Room::linkRoom(char dir, int targetRoomId) {
    if (dir == 'n')
        Room::north = targetRoomId;
    else if (dir =='e')
        Room::east = targetRoomId;
    else if (dir =='s')
        Room::south = targetRoomId;
    else if (dir =='w')
        Room::west = targetRoomId;
}

int Room::getLinkedRoom(char dir) {
    int targetRoomId;

    if (dir == 'n')
        targetRoomId = Room::north;
    else if (dir =='e')
        targetRoomId = Room::east;
    else if (dir =='s')
        targetRoomId = Room::south;
    else if (dir =='w')
        targetRoomId = Room::west;
    else
        targetRoomId = 0;

    return targetRoomId;
}

/*
 *  private functions
 */

bool Room::addIdToList(int id, std::vector<int> &list) {
    auto size = list.size();
    auto it = std::find(list.begin(), list.end(),id);

    // if id not exist
    if(it == list.end())
        list.push_back(id);

    return size != list.size();
}

bool Room::removeIdFromList(int id, std::vector<int> &list) {
    auto size = list.size();
    auto it = std::find(list.begin(), list.end(), id);

    // if id exist
    if (it != list.end())
        list.erase(it);

    return size != list.size();
}