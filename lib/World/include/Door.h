//
// Created by evan on 17/01/19.
//

#ifndef WEBSOCKETNETWORKING_DOOR_H
#define WEBSOCKETNETWORKING_DOOR_H

#include <vector>
#include <string>

using namespace std;

class Door {
public:
    Door();

private:
    unsigned int id;
    unsigned int destinatedRoomId;
    string direction;
    vector<string> descriptions;
    vector<string> keywords;

};


#endif //WEBSOCKETNETWORKING_DOOR_H
