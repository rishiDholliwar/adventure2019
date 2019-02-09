//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H



#include <map>
#include <Character.h>
#include <RoomController.h>

//dummy values
#define CHARACTER_ID 90
#define ROOM_ID 1000

class CharacterController {

private:

    std::map<std::string, Character> onlineUsers;

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
    bool addToOnlineUsers(std::string &username, RoomController &roomController);

    /*
     * Remove user from the list of characters
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if removal is successful
    */
    bool removeFromOnlineUsers(std::string &username);

    /*
     * Returns a character object of the specified username
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if removal is successful
    */
    Character &getCharacter(std::string &username);

    /*
     * Checks to see if character exists in online users
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: Returns true if the character exists
    */
    bool doesCharacterExist(std::string &userName);

    std::vector<std::string> getNamesOfOnlineUsers();


    void swapCharacters( Character &userCharacter,  Character &targetCharacter);
};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
