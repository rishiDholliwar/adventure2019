#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H

#include <unordered_map>

#include <AlterSpace.h>
#include <Character.h>
#include <RoomController.h>

using AlterSpace::ID;
using AlterSpace::Name;

//dummy values
#define CHARACTER_ID 90
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
    bool addCharacter(Name &username, RoomController &roomController);

    /*
     * Remove user from the list of characters
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if removal is successful
    */
    bool removeCharacter(Name &username);

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

    std::vector<Name> getAllCharacterNames();

    std::string getCharacterInfo(Name &username);

    ID getCharacterRoomID(Name &username);

    void setCharacterRoomID(Name &username, ID roomID);

    bool characterHasItem(Name &username, ID itemID);

    bool characterHasItem(Name &username, Name itemName);

    void addItemToCharacterInventory(Name &username, Object item);

    bool dropItemFromCharacterInventory(Name &username, ID objectID);

    Object getItemFromCharacterInventory(Name &username, Name itemName);

    bool characterIsWearingItem(Name &username, ID objectID);

    bool characterIsWearingItem(Name &username, Name itemName);

    bool characterWearItem(Name &username, Object item);

    bool characterRemoveItem(Name &username, Object item);

    std::string characterListInventory(Name &username);

    void swapCharacters(Name &userCharacterName, Name &targetCharacterName);
};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
