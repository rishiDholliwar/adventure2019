
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H

#include <AlterSpace.h>
#include <CharacterController.h>
#include <ObjectController.h>
#include <RoomController.h>
#include <NPCController.h>
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
    NPCController npcController;

public:
    GameController();

    std::vector<Response> info(Name username, Input message);

    /*
     * loadCharacter:
     *
     * Pre-Condition: username of the character that we are loading
     *
     * Post-Condition: Returns true if successfully loaded character
     *                         false if character already loaded
    */
    bool loadCharacter(Name username);

    bool removeCharacter(Name username);

    /*
     * say:
     *
     * Pre-Condition: username of the user sending the message and the message
     *
     * Post-Condition: Returns a vector of messages to whomever it may concern
    */
    std::vector<Response> say(Name username, Input message);

    /*
     * whisper:
     *
     * Pre-Condition: username of the user sending the message, the message and their target
     *
     * Post-Condition: Returns a message to the target it may concern
    */
    std::vector<Response> whisper(Name username, Input inputs);

    /*
     * Broadcast:
     *
     * Pre-Condition: username of the user sending the message and the message
     *
     * Post-Condition: Returns a vector of messages to whomever it may concern (Global)
    */
    std::vector<Response> broadcast(Name username, Input message);

    /* Move:
     *
     * Function: Moves the user that sent the message in the direction of their choice (if valid)
     *
     * Pre-Condition: requires the userName of the person issuing the command and their direction of choice
     * Post: If direction is a valid one, user will move to the room with the specified direction
     *
     * */
    std::vector<Response> move(Name username, Input direction);

    /* Look:
     *
     * Function: Show the brief description of the target.
     *
     * Pre-Condition: message is the target, if the message is empty, then the target is room.
     *
     * Post-Condition: show the brief description of the target. If the target is the room, show the brief description
     * of the room as well as a short description of the characters, objects, and cardinal/ordinal/vertical exits within the room
     */
    std::vector<Response> look(Name username, Input target);

    /* Look:
     *
     * Function: Show the detailed description of the room.
     *
     * Pre-Condition: message is the target, if the message is empty, then the target is room.
     *
     * Post-Condition: show the brief description of the target. If the target is the room, show the brief description
     * of the room as well as a short description of the characters, objects, and cardinal/ordinal/vertical exits within the room
     */
    std::vector<Response> examine(Name username, Input message);

    /* PickUp:
     *
     * Function: adds the picked up item to user's inventory
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item the picked up
     * Post: adds item to inventory unless there is no space
     *
     * */
    std::vector<Response> pickUp(Name username, Input itemName);

     Drop:
     *
     * Function: Drops the item specified from the user's inventory into the room
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item dropped
     * Post: drops the item into the room unless the person doesn't have the item
     *
     * 
    std::vector<Response> drop(Name username, Input itemName);

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
    std::vector<Response> wear(Name username, Input itemName);

     /* Take off:
     *
     * Function: Takes off an item that a user is wearing
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item being given
     * Post: Takes off the item that the user is wearing
     *
     * */
    std::vector<Response> takeOff(Name username, Input itemName);

    /* Inventory:
     *
     * Function: username of the person invoking this method
     *
     * Pre-Condition: requires the userName of the person issuing the command
     * Post: sends back a response to the caller and lists out their inventory
     *
     * */
    std::vector<Response> inventory(Name username, Input message);

    std::vector<Response> confuse(Name username, Input target);

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
