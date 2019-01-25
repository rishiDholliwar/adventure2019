
#ifndef WEBSOCKETNETWORKING_WORLDMANAGER_H
#define WEBSOCKETNETWORKING_WORLDMANAGER_H


#include <deque>
#include <vector>
#include "User.h"
#include "../../Controllers/include/CharacterController.h"
#include <functional>
#include <map>



class WorldManager {

    using FunctionMap = std::map<std::string, std::string(WorldManager::*)(std::string, std::string)>;

private:
    std::vector<User> _users;
    static FunctionMap _funcMap;
    CharacterController charController;
    //Areas
    //other objects

public:
    WorldManager()
    :_users{}{}
    //handles real user input
    void receiveText(std::string input,std::string userName, std::function<void (std::string userName, std::string message)> callBack);
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

    /* Consume:
     *
     * Function: The user uses a consumable item in their inventory
     *
     * Pre-Condition: requires the userName of the person issuing the command and the name of the item being consumed
     * Post: consumes said item unless they dont have it or it is not consumable
     *
     * */
    std::string consume(std::string userName, std::string input);


};


#endif //WEBSOCKETNETWORKING_WORLDMANAGER_H
