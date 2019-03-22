#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H

#include <string>
#include <vector>
#include <AlterSpace.h>
#include <Inventory.h>
#include <UniqueID.h>
#include <Object.h>
#include <utility>

using AlterSpace::ID;
using AlterSpace::Name;

class Character : public UniqueID {
private:
    Name name;
    ID roomID;
    Inventory inventory;
    std::vector<Object> wearing;
    bool confused;

    std::vector<Object>::iterator getWearingIterator(ID objectId);
    std::vector<Object>::iterator getWearingIterator(Name objectName);

public:
    Character() = default;
    Character(const Name &name, ID roomID);

    Character(const Name &name, ID roomID, const Inventory &inventory, const std::vector<Object> &wearing,
              bool confused);

    Name getName() const;
    ID getRoomID() const;
    ID getID() const;
    std::string getInfo() const;
    bool isConfused() const;

    const Inventory &getInventory() const;

    void setInventory(const Inventory &inventory);

    const std::vector<Object> &getWearing() const;

    void setWearing(const std::vector<Object> &wearing);

    void setRoomID(ID roomID);

    Object getItemFromInventory(Name objectName);

    Object getItemFromInventory(ID objectId);

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
    bool hasItem(Name &objectName);

    /*
     * checks to see if character is wearing specified item
     *
     * Pre-Condition: id of the item
     *
     * Post-Condition: Returns true if the item is being worn
    */
    bool isWearing(ID objectId);

    /*
     * overloaded
     */
    bool isWearing(Name objectName);

    /*
     * the user wears the specified item
     *
     * Pre-Condition: the item
     *
     * Post-Condition: Returns true if the item is worn
    */
    bool wear(ID objectId);

    /*
     * unwears the specified item
     *
     * Pre-Condition: the item
     *
     * Post-Condition: Returns true if the item is taken off
    */
    bool remove(Object obj);

    ID getWearingID(Name objectName);

    /*
     * Adds the specified item to inventory (as a copy)
     *
     * Pre-Condition: The object that you want to add to inventory
     *
     * Post-Condition: Returns true if addition was successful
    */
    void addItemToInventory(Object obj);

    /*
     * Removes specified object from inventory
     *
     * Pre-Condition: ID of the Object
     *
     * Post-Condition: Item will be dropped if it exists, returns true if dropped
    */
    bool dropItem(ID objectId);


    std::string listWearing() const;


    // This should be getInventory
    // This should exist inside of CharacterController
    // CharacterController should generate the response
    // based on the Character's inventory
    std::string listInventory();

    // look and examine
    std::string look();
    std::string examine();

    void confuse();
};


#endif //ALTERSPACE_CHARACTER_H
