//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H



#include <map>
#include <Character.h>

class CharacterController {

private:

    std::map<std::string, Character> loggedInUsers;

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
    bool addToLoggedInUsers(std::string &username);


    Character &getCharacter(std::string &userName);

    /*
     * Removes user from logged in users
     *
     * Pre-Condition: username of the person sending the command
     *
     * Post-Condition: The user will no longer exist in the list
    */
    void logoutUser(std::string &username);

    bool doesExist(std::string &userName);
};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
