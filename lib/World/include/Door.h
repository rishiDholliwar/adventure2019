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
    Door(unsigned int  id, unsigned int  destinatedRoomId, std::string direction);
    void addDescription(std::string description);
    void addKeyword(std::string keyword);
private:
    unsigned int  id;
    unsigned int  destinatedRoomId;
    std::string  direction;
    std::vector<std::string> descriptions;
    std::vector<std::string> keywords;

};


#endif //WEBSOCKETNETWORKING_DOOR_H
