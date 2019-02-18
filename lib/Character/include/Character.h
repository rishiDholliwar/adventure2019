#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H

#include <string>
#include <vector>
#include <AlterSpace.h>
#include <Inventory.h>
#include <Object.h>

using AlterSpace::ID;
using AlterSpace::Name;

class Character {
private:
    Name name;
    ID characterID;
    ID roomID;
    Inventory inventory;
    std::vector<Object> wearing;

public:
    Character(const Name &name, ID characterID, ID roomID);
    Name getName() const;
    ID getRoomID() const;
    ID getCharacterID() const;

    void setRoomID(ID roomID);

    Object getItemFromInventoryByName(Name objectName);

    /*
     * Checks to see if character has the item in question
     *
     * Pre-Condition: ID of the Object
     *
     * Post-Condition: Returns true if item exists in inventory
    */
    bool hasItem(ID objectId);

    /*
     * Checks to see if character has the item in question by name
     *
     * Pre-Condition: Name of the Object
     *
     * Post-Condition: Returns true if item exists in inventory
    */
    bool hasItemByName(Name &objectName);

    auto getWearingIteratorByID(ID objectId);

    bool isWearing(ID objectId);

    bool isWearingByName(Name objectName);

    bool wear(Object obj);

    bool takeOff(Object obj);

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
     * Post-Condition: Item will be dropped if it exists, returns true if dropped
    */
    bool dropItem(ID objectId);


    // This should be getInventory
    // This should exist inside of CharacterController
    // CharacterController should generate the response
    // based on the Character's inventory
    std::string listInventory();
};


#endif //ALTERSPACE_CHARACTER_H
