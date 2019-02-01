//
// Created by evan on 30/01/19.
//

#include <vector>
#include "Room.h"

#ifndef ALTERSPACE_ROOMCONTROLLOR_H
#define ALTERSPACE_ROOMCONTROLLOR_H


class RoomControllor {
    public:
        RoomControllor();
        bool generateRoom(unsigned int roomId, std::string roomName);
        bool removeRoom(int roomId);
        const std::vector<int> & getCharacterList (int roomId);
        const std::vector<int> & getObjectList (int roomId);
        std::vector<int> getRoomList() const;

        // return true if succeed, else return false
        bool addCharacterToRoom(int characterId, int roomId);
        bool removeCharacterFromRoom(int characterId, int roomId);
        bool addObjectToRoom(int objectId, int roomId);
        bool removeObjectFromRoom(int objectId, int roomId);

         // char 'n', 'e', 's', 'w' represents north, east, south, west

        // link room2 to room1 in the direction of room1,
        // return true if succed, else return false
        void linkRoom(char dir, int room1Id, int room2Id);
        // return 0 indicates no room is linked in the direction
        int getLinkedRoom(char dir, int roomId);

    private:
        std::vector<Room> roomList;

         Room* searchRoom(int roomId);

};


#endif //ROOMCONTROLLOR_H
