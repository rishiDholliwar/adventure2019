//
// Created on 1/23/2019.
//

#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H


#include <string>
#include <Inventory.h>
#include <Object.h>
#include <Spells.h>


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
     * Character Stats
     */

    unsigned int getCharacterCurrentHP();
    unsigned int getCharacterCurrentMP();
    void setCharacterCurrentHP(unsigned int hp);
    void setCharacterCurrentMP(unsigned int mp);


private:
    std::string name;
    unsigned int characterID;
    unsigned int roomID;
    Inventory inventory;
    CharacterStatus status = CharacterStatus::DEFAULT;
    std::vector<Spells> characterSpells;

    /*
     * Character stats
     */
    unsigned int currentHP;
    unsigned int currentMP;
    unsigned int attack = 1;
    unsigned int defense = 1;

    unsigned int maxHP = 100;
    unsigned int maxMP = 100;

};


#endif //ALTERSPACE_CHARACTER_H
