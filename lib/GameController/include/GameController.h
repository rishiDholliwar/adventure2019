
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H


#include <deque>
#include <vector>

#include <CharacterController.h>
#include <ObjectController.h>
#include <RoomController.h>
#include <Room.h>
#include <Response.h>


#include <functional>
#include <map>
#include <User.h>

class GameController {

    using FunctionMap = std::map<std::string, std::string(GameController::*)(std::string, std::string)>;

private:
    static FunctionMap _funcMap;

    CharacterController characterController;
    ObjectController objectController;
    RoomController roomController;

    std::map<std::string, Direction> directionMap;

public:
    GameController():characterController{}, objectController{}{
        directionMap = {{"north", Direction::NORTH}, {"south", Direction::SOUTH}, {"east", Direction::EAST},
                        {"west", Direction ::WEST}};
    }

    //handles real user input
    Response receiveText(std::string input,std::string userName);
    Response say(std::string userName, std::string input);

    /* Move:
     *
     * Function: Moves the user that sent the message in the direction of their choice (if valid)
     *
     * Pre-Condition: requires the userName of the person issuing the command and their direction of choice
     * Post: If direction is a valid one, user will move to the room with the specified direction
     *
     * */
    Response move(std::string userName, std::string input);

    /* PickUp:
     *
     * Function: adds the picked up item to user's inventory
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item the picked up
     * Post: adds item to inventory unless there is no space
     *
     * */
    Response pickUp(std::string userName, std::string input);

    /* Drop:
     *
     * Function: Drops the item specified from the user's inventory into the room
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item dropped
     * Post: drops the item into the room unless the person doesn't have the item
     *
     * */
    Response drop(std::string userName, std::string input);

    /* Logout:
     *
     * Function: Removes user from characterController
     *
     * Pre-Condition: requires the userName of the person
     * Post: user is removed from logged in users in character controller
     *
     * */
    Response logout(std::string userName, std::string input);




};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
