#include <Room.h>
#include <AlterSpace.h>

#ifndef ALTERSPACE_ROOMCONTROLLER_H
#define ALTERSPACE_ROOMCONTROLLER_H

using AlterSpace::Name;
using AlterSpace::ID;

class RoomController {
public:

    RoomController();


    explicit RoomController(const std::vector<Room> roomList);

    const std::vector<Room> &getRoomList() const;


    //Getters

    const std::vector<ID> & getObjectList (ID roomId);
    const std::vector<Name> & getCharacterList(ID roomId);
    std::vector<ID> getRoomIdList() const;




    ID getDoorIdByDirection(ID roomId, const std::string& direction);
    Door::DoorStatus getDoorStatus(ID roomId, const std::string& direction);
    ID getDoorDesignatedRoomId(ID roomId, const std::string& direction);
    bool doesDirectionExist(ID roomId, const std::string& direction);


    void lockDoor(ID roomID, std::string& direction);

    bool isDoorLocked(ID roomId, ID doorId);

    /*
     * The function gives information of the room
     * Post-condition:
     *          return string of information of room
     */
    std::string getRoomDescription(ID roomId);

    /*
    * The function gives information of doors in the room
    * Post-condition:
    *          return string of information of doors in the room
    */
    std::string getAllDoorInformationInRoom(ID roomId);

    /*
     * create a room according to the roomID and roomName inside RoomController
     * Post-condition:
     *          return true if the room is successfully created
     *          return false otherwise
     */
    bool generateRoom(ID roomId, const Name& roomName);

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
    bool addObjectToRoom(ID objectId, ID roomId);
    bool addCharacterToRoom(const Name &userName, ID roomId);

    /*
     * The 3 functions can remove unique id or unique userName from the room
     * Post-condition:
     *          return true if the element is successfully removed
     *          return false otherwise
     */
    bool removeObjectFromRoom(ID objectId, ID roomId);
    bool removeCharacterFromRoom(const std::string &userName, ID roomId);

    /*
     * The function creates a door in the room according to the IDs
     * Post-condition:
     *          return true if the door is successfully created
     *          return false otherwise
     */
    bool addDoorToRoom(ID roomId, ID doorId, ID designatedRoomId, const std::string &direction);

    /*
     * The function removes door from the room according to the IDs
     * Post-condition:
     *          return true if the door is successfully removed
     *          return false otherwise
     */
    bool removeDoorFromRoom(ID roomId, ID doorId);

    bool moveCharacter(Name username, ID originRoomId, ID destinationRoomId);

    bool isDoorExist(ID roomId, std::string &direction);

    bool isDoorLocked(ID roomId, std::string &direction);


    /*
    * return the Room object, return nullptr if roomId not found
    */
    Room* searchRoom(ID roomId);

    /*
     * return the Door object, return nullptr if doorId not found
     */
    Door* searchDoor(ID roomId, const std::string& direction);

    bool doesObjectExistInRoom(ID roomId, ID objectId);
    bool doesCharacterExistInRoom(ID roomId, Name characterName);

    // Validity checkers
    //        bool roomExists(ID roomId);
    //        bool roomHasCharacter(ID roomId, Name& userName);
    //        bool roomHasItem(ID roomId, ID objectId);
    //        bool roomHasItem(ID roomId, Name itemName);
    //        // bool roomHasNPC(ID roomId);
    //        // bool roomHasDoor(ID roomId);
    //        // bool roomHasKeywod(ID roomId, std::string keyword);
    //
    //        // look and examines
    //        std::string lookDoor(ID roomId);
    //        std::string examineDoor(ID roomId);
    //
    //        std::string lookRoom(ID roomId);
    //        std::string examineRoom(ID roomId);
    //        std::string lookRoomKeyword(ID roomId, std::string keyword);

    // std::string lookNPC(ID roomId);
    // std::string examineNPC(ID roomId);

            bool isTargetInRoom(Name &userName, ID roomId, Name &target);
private:
    std::vector<Room> roomList;

};


#endif //ROOMCONTROLLER_H
