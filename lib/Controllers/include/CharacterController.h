//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H


#include "../../Model/Character.h"

class CharacterController {

public:

    /* Constructor */
    CharacterController();

    /* Level Up Character:
     *
     * Function: levels up a character once they have the required amount of experience
     *
     * Pre-Condition: Requires a character to level up
     * Post: Returns true on a successful level up, returns false otherwise
     *
     * */
    bool levelUpCharacter(Character &character);


    /* Update Room ID:
     *
     * Function: Updates the character's current room based on the roomID of the destination
     *
     * Pre-Condition: requires the character that wants to move and the destination room ID
     * Post: Updates the character's current location to the new room and returns true if successful
     *
     * */
    bool updateRoomID(Character &character, unsigned int &destinationRoomID);


    /* Add Item To Inventory:
     *
     * Function: Adds the item to the character's inventory
     *
     * Pre-Condition: requires the character that receives the item and the item
     * Post: adds item to users inventory and fails if inventory is full
     *
     * */
    template <typename T>
    bool addItemToInventory(Character &character, T &item);

};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
