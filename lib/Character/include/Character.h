#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H

#include <string>
#include <vector>
#include <AlterSpace.h>
#include <Inventory.h>
#include <UniqueID.h>
#include <Object.h>
#include <utility>
#include "Spells.h"

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
    std::vector<std::string> characterSpells;

    /*
     * Character stats
     */
    unsigned int currentHP;
    unsigned int currentMP;
    unsigned int attack = 1;
    unsigned int defense = 1;

    unsigned int maxHP = 100;
    unsigned int maxMP = 100;


public:
    Character(const Name &name, ID roomID);
    Name getName() const;
    ID getRoomID() const;
    ID getID() const;
    std::string getInfo() const;
    bool isConfused();

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


    /*
     * Returns a string list of character known spells
     *
     * Pre-condition: Character has a list of spells
     *
     * Post-Condition: Return string of all character known spells
     */
    std::string getListOfSpells();

    /*
     * Returns a string list of character spells based on spell type
     *
     * Pre-Condition: Character has a list of spells of said type
     *
     * Post-Condition: Return all character spells of said type
     */
    std::string getListOfSpells(Spells::SpellType spellType);

    /*
     * Returns true or false depending if the character has a given spell name
     *
     * Pre-Condition: Character has a list of spells
     *
     * Post-Condition: True if character has spell learned
     */
    bool doesSpellExist(std::string &spellName);

    /*
     * Add a spell to the character
     *
     * Pre-Condition: Valid spell name
     *
     * Post-Condition: The character learns a new spell
     *
     */
    void addSpellToCharacter(std::string &spellName);


    //Set up characters default spell
    void addDefaultSpells();


    /*
     * Character Stats
     */

    unsigned int getCharacterCurrentHP();
    unsigned int getCharacterCurrentMP();
    void setCharacterCurrentHP(unsigned int hp);
    void setCharacterCurrentMP(unsigned int mp);


    void confuse();
};


#endif //ALTERSPACE_CHARACTER_H
