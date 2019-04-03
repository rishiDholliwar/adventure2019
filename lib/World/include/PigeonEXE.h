#ifndef ALTERSPACE_PIGEONEXE_H
#define ALTERSPACE_PIGEONEXE_H

#include <AlterSpace.h>
#include <RoomController.h>

#include <unordered_map>

using AlterSpace::ID;

class PigeonEXE
{
private:

    int calculate(ID fromRoom, ID toRoom);

    using DirectionDistance = std::pair<std::string, int>;
    std::unordered_map<ID, std::unordered_map<ID, DirectionDistance>> shortestMap;

    RoomController* _roomController;


public:
    PigeonEXE(){};
    PigeonEXE(RoomController* _roomController) : _roomController(_roomController) {};

    DirectionDistance getShortestDirection(ID fromRoom, ID toRoom);


};


#endif //ALTERSPACE_PIGEONEXE_H
