
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H

#include <AlterSpace.h>
#include <CharacterController.h>
#include <ObjectController.h>
#include <RoomController.h>
#include <Response.h>

#include <algorithm>
#include <vector>
#include <map>

using AlterSpace::Input;
using AlterSpace::Name;

class GameController {
private:
    CharacterController characterController;
    ObjectController objectController;
    RoomController roomController;

    bool isDigit(const std::string& str);

public:
    GameController();

    /*
     * loadCharacter:
     *
     * Pre-Condition: username of the character that we are loading
     *
     * Post-Condition: Returns true if successfully loaded character
     *                         false if character already loaded
    */
    bool loadCharacter(Name username);

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

    /* Inspect:
     *
     * Function: Display the information of the current room
     *
     * Pre-Condition: None
     * Post-Condition: Display the information of the current room on user's windows
     */
    std::vector<Response> inspect(Name username, Input message);

    /* Move:
     *
     * Function: Moves the user that sent the message in the direction of their choice (if valid)
     *
     * Pre-Condition: requires the userName of the person issuing the command and door ID of choice
     * Post: If door ID is a valid one, user will move to the room with the specified door.
     *
     * */
    std::vector<Response> move(Name username, std::string inputDoorId);


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
