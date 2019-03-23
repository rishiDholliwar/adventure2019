#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H

#include <unordered_map>

#include <AlterSpace.h>
#include <Character.h>
#include <RoomController.h>
#include <ObjectController.h>

using AlterSpace::ID;
using AlterSpace::Name;

//dummy values
#define ROOM_ID 1000

class CharacterController {

private:

    std::unordered_map<Name, Character> _characters;

public:

    /* Constructor */
    CharacterController();

    /*
     * Adds new users to the list of characters
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if addition is successful
    */
    bool addCharacter(Name &username, RoomController &roomController, ObjectController &objectController);

    /*
     * Remove user from the list of characters
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if removal is successful
    */
    bool removeCharacter(Name &username);

    bool findCharacter(Name username);

    Name getUsernameOfCharacter(Name &charName);


    Character &getCharacterByCharName(Name &charName);

    /*
     * Returns a character object of the specified username
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if removal is successful
    */
    Character &getCharacter(Name &username);

    /*
     * Checks to see if character exists in online users
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if the character exists
    */
    bool doesCharacterExist(Name &userName);

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
    bool dropItemFromCharacterInventory(Name &username, ID objectID);

    std::vector<Object> getItemsFromCharacterInventory(Name &username, Name itemName);

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
    bool characterWearItem(Name &username, Name itemName);

    /*
     * unequips the specified item
     *
     * Pre-Condition: username of the person and the item
     *
     * Post-Condition: Returns true if the item is unequipped
    */
    bool characterRemoveItem(Name &username, Object item);

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
    std::string examineCharacter(Name& userName);

    void swapCharacter(Name &userCharacterName, Name &targetCharacterName);

    void confuseCharacter(Name &targetCharacterName);

    bool isCharacterConfused(Name &username);

    //for combat
    void setCharacterHP(Name &username,unsigned int hp);
};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
