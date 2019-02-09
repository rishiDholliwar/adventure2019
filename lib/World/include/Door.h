//
// Created by evan on 17/01/19.
//

#ifndef WEBSOCKETNETWORKING_DOOR_H
#define WEBSOCKETNETWORKING_DOOR_H

#include <vector>
#include <string>
#include <memory>

class Door {
public:
    using ID = unsigned int;

    enum DoorStatus{
        LOCKED = 0,
        UNLOCKED = 1,
    };

    Door(ID  id, ID  destinatedRoomId, const std::string& direction);
    void addDescription(const std::string& description);
    void addKeyword(const std::string& keyword);
    ID const& getId() const{return id;};
    ID const& getDestinatedRoomId() const{return destinatedRoomId;};
    std::string const& getDirection() const{return direction;};
    bool lockDoor();
    bool unlockDoor();
    DoorStatus const& getStatus() const{ return status;};

private:
    ID id;
    ID destinatedRoomId;
    std::string  direction;
    DoorStatus status;
    std::vector<std::string> descriptions;
    std::vector<std::string> keywords;

};


#endif //WEBSOCKETNETWORKING_DOOR_H
