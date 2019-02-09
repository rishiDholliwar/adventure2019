//
// Created on 1/23/2019.
//

#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H


#include <string>
#include <Inventory.h>
#include <Object.h>

class Character {
private:
    std::string name;

    unsigned int characterID;

    unsigned int roomID;

    Inventory inventory;

    public:

    Character(const std::string &name, unsigned int characterID, unsigned int roomID);

    std::string getName();

    unsigned int getRoomID();

    unsigned int getCharacterID() const;

    void setRoomID(unsigned int roomID);

    /*
     * Checks to see if character has the item in question
     *
     * Pre-Condition: ID of the Object
     *
     * Post-Condition: Returns true if item exists in inventory
    */
    bool hasItem(unsigned int objectId);

    /*
     * Adds the specified item to inventory (as a copy)
     *
     * Pre-Condition: The object that you want to add to inventory
     *
     * Post-Condition: Returns true if addition was successful
    */
    bool addItemToInventory(Object obj);

    /*
     * Removes specified object from inventory
     *
     * Pre-Condition: ID of the Object
     *
     * Post-Condition: Item will be dropped if it exists
    */
    void dropItem(unsigned int objectId);

    std::string listInventory();
};


#endif //ALTERSPACE_CHARACTER_H
