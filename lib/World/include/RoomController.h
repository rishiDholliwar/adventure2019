#ifndef ALTERSPACE_ROOMCONTROLLER_H
#define ALTERSPACE_ROOMCONTROLLER_H

#include <Room.h>

class RoomController {
    public:
        RoomController();

        //Getters
        const std::vector<ID> & getCharacterList (ID roomId);
        const std::vector<ID> & getObjectList (ID roomId);
        const std::vector<std::string> & getUsernameList (ID roomId);
        std::vector<ID> getRoomIdList() const;

        // Adders
        // return true if succeed, else return false
        bool generateRoom(ID roomId, const std::string& roomName);
        bool addCharacterToRoom(ID characterId, ID roomId);
        bool addObjectToRoom(ID objectId, ID roomId);
        bool addUserNameToRoom(const std::string& userName, ID roomId);

        // Removers
        bool removeCharacterFromRoom(ID characterId, ID roomId);
        bool removeObjectFromRoom(ID objectId, ID roomId);
        bool removeRoom(ID roomId);
        bool removeUserNameFromRoom(const std::string &userName, ID roomId);

        // Link Rooms
        // char 'n', 'e', 's', 'w' represents north, east, south, west
        // link room2 to room1 in the direction of room1,
        // return true if succeed, else return false
        void linkRoom(Direction dir, ID room1Id, ID room2Id);
        // return 0 indicates no room is linked in the direction
        ID getLinkedRoom(Direction dir, ID roomId);

private:
         std::vector<Room> roomList;
         std::vector<ID> emptyIdVector;
         std::vector<std::string> emptyStringVector;

         Room* searchRoom(ID roomId);


};


#endif //ROOMCONTROLLER_H
