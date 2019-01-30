//
// Created on 1/23/2019.
//

#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H


#include <string>
#include "../../Object/include/Inventory.h"
#include "../../Object/include/Object.h"

/*
 * Character class
 * A character class holds the information of a user's character
 */

class Character {
private:
    std::string roomID;
    std::string name;
    std::string const STARTING_ROOM = "0000";
    Inventory inventory;

    public:
    /*
     * Default constructor
     */
    Character();
    Character(std::string name);

    /*
     * Getter functions
     */
    std::string getCharacterName();
    std::string getCharacterRoomID();


    /*
     * Setter functions
     */

    void setCharacterRoomId(std::string id);

    /*
     * Character inventory functions
     */
    void addItemtoInventory(Object obj);
    void removeItemFromInventory(std::string name);
    //FOR NOW ONLY RETURNING A LONG STRING OF ITEMS
    void listInventory();

};


#endif //ALTERSPACE_CHARACTER_H
