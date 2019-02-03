//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_CHARACTERCONTROLLER_H
#define ALTERSPACE_CHARACTERCONTROLLER_H


#include <bits/unordered_map.h>
#include <map>
#include "../../Character/include/Character.h"

class CharacterController {

private:

    std::map<std::string, Character> loggedInUsers;

public:

    /* Constructor */
    CharacterController();


    bool addToLoggedInUsers(std::string &username);

    Character &getCharacter(std::string &userName);
};


#endif //ALTERSPACE_CHARACTERCONTROLLER_H
