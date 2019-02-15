
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H

#include <AlterSpace.h>
#include <CharacterController.h>
#include <ObjectController.h>
#include <RoomController.h>
#include <Response.h>

#include <vector>
#include <map>

using AlterSpace::Input;
using AlterSpace::Name;

class GameController {
private:
    CharacterController characterController;
    ObjectController objectController;
    RoomController roomController;

public:
    GameController();

    /*
     * say:
     *
     * Pre-Condition: username of the user sending the message and the message
     *
     * Post-Condition: Returns a vector of messages to whomever it may concern
    */
    std::vector<Response> say(Name username, std::string message);

    /*
     * Broadcast:
     *
     * Pre-Condition: username of the user sending the message and the message
     *
     * Post-Condition: Returns a vector of messages to whomever it may concern (Global)
    */
    std::vector<Response> broadcast(Name username, std::string message);

    /* Move:
     *
     * Function: Moves the user that sent the message in the direction of their choice (if valid)
     *
     * Pre-Condition: requires the userName of the person issuing the command and their direction of choice
     * Post: If direction is a valid one, user will move to the room with the specified direction
     *
     * */
    std::vector<Response> move(Name username, std::string direction);

    /* Does the direction exist:
     *
     * Function: Checks to see if direction exists in the map
     *
     * Pre-Condition: requires the direction in question
     * Post: returns true if direction exists
     *
     * */
    bool directionExists(Name direction);

    /* PickUp:
     *
     * Function: adds the picked up item to user's inventory
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item the picked up
     * Post: adds item to inventory unless there is no space
     *
     * */
    std::vector<Response> pickUp(Name username, Name itemName);

    /* Drop:
     *
     * Function: Drops the item specified from the user's inventory into the room
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item dropped
     * Post: drops the item into the room unless the person doesn't have the item
     *
     * */
    std::vector<Response> drop(Name username, Name itemName);

     /* Give:
     *
     * Function: Gives an item from a user's inventory to another user
     *
     * Pre-Condition: requires the userName of the person issuing the command and the userName of the gift recipient and name of the item being given
     * Post: gives the item to target's inventory unless the person doesn't have the item
     *
     * */
    std::vector<Response> give(Name username, Input message);

     /* Wear:
     *
     * Function: Wears an item from a user's inventory
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item being given
     * Post: wears the item unless the item does not exist in inventory
     *
     * */
    std::vector<Response> wear(Name username, Input message);

     /* Take off:
     *
     * Function: Takes off an item that a user is wearing
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item being given
     * Post: Takes off the item that the user is wearing
     *
     * */
    std::vector<Response> takeOff(Name username, Input message);

    /* Inventory:
     *
     * Function: username of the person invoking this method
     *
     * Pre-Condition: requires the userName of the person issuing the command
     * Post: sends back a response to the caller and lists out their inventory
     *
     * */
    std::vector<Response> inventory(Name username, Input message);

    std::vector<Response> swap(Name username, Name target);

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
    std::vector<Response> formulateResponse(Response &userResponse, std::vector<Name> characterList, Input message);
};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
