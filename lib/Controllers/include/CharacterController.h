#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H

#include <unordered_map>
#include <algorithm>

#include <AlterSpace.h>
#include <Character.h>
#include <RoomController.h>
#include <ObjectController.h>

using AlterSpace::ID;
using AlterSpace::Name;

//dummy values
#define ROOM_ID 8800

class CharacterController {
private:
    std::unordered_map<Name, Character> _characters;

public:
    /* Constructor */
    CharacterController() = default;

    /*
     * Adds new users to the list of characters
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if addition is successful
    */
    void addCharacter(Name &username, RoomController &roomController, ObjectController &objectController);

    void addCharacter(Character &aCharacter);

    Name addNPC(Character& aNPC);

    /*
     * Remove user from the list of characters
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if removal is successful
    */
    void removeCharacter(Name &username);

    ID getNPCID(Name &npcKey);

    std::vector<Name> getUsernamesOfCharacter(Name characterName);

    std::vector<Name> getUsernamesOfCharacter(ID charID);

    std::vector<ID> getUniqueIDsOfCharacter(Name characterName);

    /*
     * Returns a character object of the specified username
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if removal is successful
    */
    Character &getCharacter(Name &username);

    Character &getCharacter(ID uniqueID);

    Name getUsernameOfCharacter(Name &charName);

    Name getUsernameOfCharacter(ID charID);

    // Character &getCharacterByCharName(Name &charName);

    Name getCharName(Name &username);

    ID getCharID(Name &username);

    bool isCharacterNPC(Name &npcKey);

    /*
     * Checks to see if character exists in online users
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if the character exists
    */
    bool doesCharacterExist(Name &userName);

    bool doesCharacterExist(ID uniqueID);

    /*
     * Obtain a list of all users currently in the game
     *
     * Pre-Condition:
     *
     * Post-Condition: Returns all users in the game
    */
    std::vector<Name> getAllCharacterNames();

    /*
     * obtain character info
     *
     * Pre-Condition: info of the specified user
     *
     * Post-Condition: string of the user's info
    */
    std::string getCharacterInfo(Name &username);

    /*
     * obtain room id of the character in question
     *
     * Pre-Condition: name of the user
     *
     * Post-Condition: current room id of the user
    */
    ID getCharacterRoomID(Name &username);

    /*
     * modify the room id of the character in question
     *
     * Pre-Condition: username of the character and the new room id
     *
     * Post-Condition:
    */
    void setCharacterRoomID(Name &username, ID roomID);

    /*
     * checks to see if character has specified item
     *
     * Pre-Condition: username of the person and the id of the item
     *
     * Post-Condition: Returns true if the item exists
    */
    bool characterHasItem(Name &username, ID itemID);

    /*
     * checks to see if character has specified item
     *
     * Pre-Condition: username of the person and the name of the item
     *
     * Post-Condition: Returns true if the item exists
    */
    bool characterHasItem(Name &username, Name itemName);

    /*
     * adds specified item to character inventory
     *
     * Pre-Condition: username of the person and the item
     *
     * Post-Condition:
    */
    void addItemToCharacterInventory(Name &username, Object item);

    /*
     * deletes item from the character inventory
     *
     * Pre-Condition: username of the person and the id of the item
     *
     * Post-Condition: Returns true if the item has been dropped
    */
    void dropItemFromCharacterInventory(Name &username, ID objectID);

    std::vector<Object> getItemsFromCharacterInventory(Name &username, Name itemName);

    std::vector<Object> getItemsFromCharacterWearing(Name &username, Name itemName);

    /*
     * obtain item from users inventory
     *
     * Pre-Condition: username of the person and the name of the item
     *
     * Post-Condition: Returns the item if it exists
    */
    Object getItemFromCharacterInventory(Name &username, Name itemName);

    Object getItemFromCharacterInventory(Name &username, ID itemID);

    ID getItemIDFromCharacterInventory(Name &username, Name itemName);

    /*
     * checks to see if character is wearing specified item
     *
     * Pre-Condition: username of the person and the id of the item
     *
     * Post-Condition: Returns true if the item is being worn
    */
    bool characterIsWearingItem(Name &username, ID objectID);

    /*
     * overloaded (by item name)
     */
    bool characterIsWearingItem(Name &username, Name itemName);

    /*
     * the user equips the specified item
     *
     * Pre-Condition: username of the person and the item
     *
     * Post-Condition: Returns true if the item is equipped
    */
    void characterWearItem(Name &username, ID itemID);

    /*
     * unequips the specified item
     *
     * Pre-Condition: username of the person and the item
     *
     * Post-Condition: Returns true if the item is unequipped
    */
    void characterRemoveItem(Name &username, Object item);

    ID getItemIDFromCharacterWearing(Name &username, Name itemName);

    /*
     * lists (in order) the items in a users inventory
     *
     * Pre-Condition: username of the character
     *
     * Post-Condition: Returns a modified string listing inventory of user
    */
    std::string characterListInventory(Name &username);

    // look and examine
    std::string lookCharacter(Name& userName);
    std::string examineCombatCharacter(Name& userName);
    std::string examineCharacter(Name& userName);

    void swapCharacter(Name &userCharacterName, Name &targetCharacterName);

    void confuseCharacter(Name &targetCharacterName);

    bool isCharacterConfused(Name &username);

    //for combat
    void setCharacterHP(Name &username,unsigned int hp);

    bool isCharacterInCombat(Name &username);

    void setCharacterCombat(Name &username, Name &targetname,bool state);

    void setCharacterCombat(Name &username,bool state);

};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
