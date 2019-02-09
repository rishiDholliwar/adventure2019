//
// Created by evan on 30/01/19.
//

#include <Room.h>

#ifndef ALTERSPACE_ROOMCONTROLLER_H
#define ALTERSPACE_ROOMCONTROLLER_H

class RoomController {
    public:
        using ID = Room::ID;

        RoomController();

        //Getters
        const std::vector<ID> & getCharacterList (ID roomId);
        const std::vector<ID> & getObjectList (ID roomId);
        const std::vector<std::string> & getUsernameList (ID roomId);
        std::vector<ID> getRoomIdList() const;

        /*
         * create a room according to the roomID and roomName inside RoomController
         * Post-condition:
         *          return true if the room is successfully created
         *          return false otherwise
         */
        bool generateRoom(ID roomId, const std::string& roomName);

        /*
         * Delete the room in roomController according to the roomId
         * Post-condition:
         *          return true if the room is successfully deleted
         *          return false otherwise
         */
        bool removeRoom(ID roomId);

        /*
         * The 3 functions can add unique id or unique userName into the room
         * Post-condition:
         *          return true if the element is successfully added
         *          return false otherwise
         */
        bool addCharacterToRoom(ID characterId, ID roomId);
        bool addObjectToRoom(ID objectId, ID roomId);
        bool addUserNameToRoom(const std::string& userName, ID roomId);

        /*
         * The 3 functions can remove unique id or unique userName from the room
         * Post-condition:
         *          return true if the element is successfully removed
         *          return false otherwise
         */
        bool removeCharacterFromRoom(ID characterId, ID roomId);
        bool removeObjectFromRoom(ID objectId, ID roomId);
        bool removeUserNameFromRoom(const std::string &userName, ID roomId);

        // Link Rooms
        bool addDoorToRoom(ID roomId, ID doorId, ID destinatedRoomId, const std::string &direction);
        bool removeDoorFromRoom(ID roomId, ID doorId);

        std::string getTextOfRoomDetails(ID roomId);


    private:
         std::vector<Room> roomList;
         std::vector<ID> emptyIdVector;
         std::vector<std::string> emptyStringVector;

         Room* searchRoom(ID roomId);


};


#endif //ROOMCONTROLLER_H
