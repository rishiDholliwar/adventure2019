
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

    /*
     * say:
     *
     * Pre-Condition: username of the user sending the message and the message
     *
     * Post-Condition: Returns a vector of messages to whomever it may concern
    */
    std::vector<Response> say(std::string username, std::string message);

    /*
     * Broadcast:
     *
     * Pre-Condition: username of the user sending the message and the message
     *
     * Post-Condition: Returns a vector of messages to whomever it may concern (Global)
    */
    std::vector<Response> broadcast(std::string username, std::string message);

    /* Move:
     *
     * Function: Moves the user that sent the message in the direction of their choice (if valid)
     *
     * Pre-Condition: requires the userName of the person issuing the command and their direction of choice
     * Post: If direction is a valid one, user will move to the room with the specified direction
     *
     * */
    std::vector<Response> move(std::string username, std::string direction);

    /* PickUp:
     *
     * Function: adds the picked up item to user's inventory
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item the picked up
     * Post: adds item to inventory unless there is no space
     *
     * */
    std::vector<Response> pickUp(std::string username, std::string itemName);

    /* Drop:
     *
     * Function: Drops the item specified from the user's inventory into the room
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item dropped
     * Post: drops the item into the room unless the person doesn't have the item
     *
     * */
    std::vector<Response> drop(std::string username, std::string itemName);

    /* Inventory:
     *
     * Function: username of the person invoking this method
     *
     * Pre-Condition: requires the userName of the person issuing the command
     * Post: sends back a response to the caller and lists out their inventory
     *
     * */
    std::vector<Response> inventory(std::string username, std::string message);

    std::vector<Response> swap(std::string username, std::string target);

    /* Formulate Response:
     *
     * Function: Constructs messages to send to every player
     *
     * Pre-Condition: requires the userName of the person issuing the command and the message they want to send
     * Post: vector of responses for every person it may concern
     *
     * */
    std::vector<Response> formulateResponse(Response &userResponse);

    std::vector<Response> formulateResponse(Response &userResponse, Response &targetResponse);

    /* Formulate Response:
     * Overloaded function of the formulateResponse(Response)
     * */
    std::vector<Response> formulateResponse(Response &userResponse, std::vector<std::string> characterList, std::string message);



};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
