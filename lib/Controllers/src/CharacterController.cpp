#include <iostream>
#include <CharacterController.h>

CharacterController::CharacterController() = default;



bool CharacterController::addToLoggedInUsers(std::string &username) {

    //find and load character based on username
    /* json work */

    /* if character not found one will be made and then loaded*/
    Character dummyCharacter(username, 91, 1000);
    return loggedInUsers.emplace(username,dummyCharacter).second;

}

Character &CharacterController::getCharacter(std::string &userName) {
    return loggedInUsers.find(userName)->second;
}






