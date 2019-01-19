//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H


#include "../Model/Character.h"

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

    /* Equip Weapon:
     *
     * Function: Equips a weapon into the weapon slot
     *
     * Pre-Condition: Requires a character and the weapon he/she wants to equip
     * Post: Returns true on a successful equip, returns false otherwise
     * */
    bool equipWeapon(Character &character, Item &anItem);

    /* Equip Armor:
     *
     * Function: Equips a armor into the armor slot
     *
     * Pre-Condition: Requires a character and the armor he/she wants to equip
     * Post: Returns true on a successful equip, returns false otherwise
     * */
    bool equipArmor(Character &character, Item &item);



};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
