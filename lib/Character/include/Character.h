#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H

#include <string>
#include <AlterSpace.h>
#include <Inventory.h>
#include <Object.h>
#include <Spells.h>


using AlterSpace::ID;
using AlterSpace::Name;

class Character {
public:
    /*
    * A Character has a status that limits the actions a character can do.
    */
    enum class CharacterStatus {
        UNDERSPELL,
        COMBAT,
        MINIGAME,
        DEFAULT
    };
private:
    Name name;
    ID characterID;
    ID roomID;
    Inventory inventory;
    CharacterStatus status = CharacterStatus::DEFAULT;
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
    Character(const Name &name, ID characterID, ID roomID);
    Name getName() const;
    ID getRoomID() const;
    ID getCharacterID() const;

    void setRoomID(ID roomID);

    /*
     * Checks to see if character has the item in question
     *
     * Pre-Condition: ID of the Object
     *
     * Post-Condition: Returns true if item exists in inventory
    */
    bool hasItem(ID objectId);

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
    void dropItem(ID objectId);


    // This should be getInventory
    // This should exist inside of CharacterController
    // CharacterController should generate the response
    // based on the Character's inventory
    std::string listInventory();

    /*
     * Updates a characters status
     *
     * Pre-Condition: A status requirement that doesn't conflict with another status.
     *
     * Post-Condition: Character status will be updated if possible
     */
    void updateCharacterStatus(CharacterStatus status);

    /*
     * Returns a string list of all character spells
     *
     * Pre-Condition: Character has a list of spells
     *
     * Post-Condition: Returns all character spells
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


};


#endif //ALTERSPACE_CHARACTER_H
