
#ifndef WEBSOCKETNETWORKING_DOOR_H
#define WEBSOCKETNETWORKING_DOOR_H

#include <vector>
#include <string>
#include "AlterSpace.h"


using AlterSpace::Name;
using AlterSpace::ID;


class Door {
public:
    const static ID unfoundDoorId = 0;

    enum DoorStatus{
        LOCKED = 0,
        UNLOCKED = 1,
    };

    Door(ID  id, ID  targetRoomID, const std::string& direction);

    // Adders
    void addDescription(const std::string& description);
    void addKeyword(const std::string& keyword);

    // Getters
    ID const& getId() const{return id;};
    ID const& getDesignatedRoomId() const{return designatedRoomID;};
    std::string const& getDirection() const{return direction;};

    /*
     * Set the door status to locked or unlocked
     * Post-condition:
     *      return true if the action is successful
     *      return false otherwise
     */
    void setDoorLocked();
    void setDoorUnlocked();

    /*
     * return the status of the door
     * Post-condition:
     *      return DoorStatus
     */
    DoorStatus const& getStatus() const{ return status;};

private:
    ID id;
    ID designatedRoomID;
    std::string  direction;
    DoorStatus status;
    std::vector<std::string> descriptions;
    std::vector<std::string> keywords;

};


#endif //WEBSOCKETNETWORKING_DOOR_H
