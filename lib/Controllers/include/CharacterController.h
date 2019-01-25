//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H


#include "../../Model/Character.h"

class CharacterController {

public:

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
     * Pre-Condition: requires the character that receives the item and the item name itself
     * Post: adds item to users inventory and fails if inventory is full
     *
     * */
    template <typename T>
    bool addItemToInventory(Character &character, T &item);


//    /* Equip Weapon:
//     *
//     * Function: Equips a weapon into the weapon slot
//     *
//     * Pre-Condition: Requires a character and the weapon he/she wants to equip
//     * Post: Returns true on a successful equip, returns false otherwise
//     * */
//    bool equipWeapon(Character &character, Item &anItem);
//
//    /* Equip Armor:
//     *
//     * Function: Equips a armor into the armor slot
//     *
//     * Pre-Condition: Requires a character and the armor he/she wants to equip
//     * Post: Returns true on a successful equip, returns false otherwise
//     * */
//    bool equipArmor(Character &character, Item &item);







};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
