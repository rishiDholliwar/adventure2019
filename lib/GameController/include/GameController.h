
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H

#include <CharacterController.h>
#include <ObjectController.h>
#include <RoomController.h>
#include <Response.h>

#include <vector>
#include <map>

class GameController {
private:
    CharacterController characterController;
    ObjectController objectController;
    RoomController roomController;

    std::map<std::string, Direction> directionMap;

public:
    GameController():characterController{}, objectController{}{
        directionMap = {{"north", Direction::NORTH}, {"south", Direction::SOUTH}, {"east", Direction::EAST},
                        {"west", Direction::WEST}};
    }

    std::vector<Response> say(std::string userName, std::string message);

    std::vector<Response> broadcast(std::string userName, std::string message);

    /* Move:
     *
     * Function: Moves the user that sent the message in the direction of their choice (if valid)
     *
     * Pre-Condition: requires the userName of the person issuing the command and their direction of choice
     * Post: If direction is a valid one, user will move to the room with the specified direction
     *
     * */
    std::vector<Response> move(std::string userName, std::string direction);

    /* PickUp:
     *
     * Function: adds the picked up item to user's inventory
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item the picked up
     * Post: adds item to inventory unless there is no space
     *
     * */
    std::vector<Response> pickUp(std::string userName, std::string itemName);

    /* Drop:
     *
     * Function: Drops the item specified from the user's inventory into the room
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item dropped
     * Post: drops the item into the room unless the person doesn't have the item
     *
     * */
    std::vector<Response> drop(std::string userName, std::string itemName);

    std::vector<Response> inventory(std::string userName, std::string message);

    /* Logout:
     *
     * Function: Removes user from characterController
     *
     * Pre-Condition: requires the userName of the person
     * Post: user is removed from logged in users in character controller
     *
     * */
    std::vector<Response> logout(std::string userName, std::string input);

    std::vector<Response> formulateResponse(Response &userResponse, std::vector<std::string> characterList, std::string message);

    std::vector<Response> formulateResponse(Response &userResponse);

};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
