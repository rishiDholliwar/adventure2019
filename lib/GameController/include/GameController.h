
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H


#include <deque>
#include <vector>

#include "../../Controllers/include/CharacterController.h"
#include "../../Controllers/include/ObjectController.h"
#include "../../World/include/RoomController.h"
#include "../../World/include/Room.h"


#include <functional>
#include <map>
#include <User.h>

class GameController {

    using FunctionMap = std::map<std::string, std::string(GameController::*)(std::string, std::string)>;

private:
    std::vector<User> _users;
    static FunctionMap _funcMap;

    CharacterController characterController;
    ObjectController objectController;
    RoomController roomController;

    std::map<std::string, Direction> directionMap;

public:
    GameController():_users{}, characterController{}, objectController{}{
        directionMap = {{"north", Direction::NORTH}, {"south", Direction::SOUTH}, {"east", Direction::EAST},
                        {"west", Direction ::WEST}};
    }
    //handles real user input
    std::string receiveText(std::string input,std::string userName);
    std::string say(std::string userName, std::string input);

    /* Move:
     *
     * Function: Moves the user that sent the message in the direction of their choice (if valid)
     *
     * Pre-Condition: requires the userName of the person issuing the command and their direction of choice
     * Post: If direction is a valid one, user will move to the room with the specified direction
     *
     * */
    std::string move(std::string userName, std::string input);

    /* PickUp:
     *
     * Function: adds the picked up item to user's inventory
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item the picked up
     * Post: adds item to inventory unless there is no space
     *
     * */
    std::string pickUp(std::string userName, std::string input);

    /* Drop:
     *
     * Function: Drops the item specified from the user's inventory into the room
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item dropped
     * Post: drops the item into the room unless the person doesn't have the item
     *
     * */
    std::string drop(std::string userName, std::string input);


};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
