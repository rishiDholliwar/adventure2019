//
// Created by ximinz on 16/01/19.
//

#include "../include/UserManager.h"

User UserManager::lookUpUser(std::string userName, std::string hashedPassword) {
    if(userName == "a"){
        User a{networking::Connection{2}, "a", "b"};
        a.moveToRoom(5);
        return a;
    }
    return User{networking::Connection{1}, "b", "b"};
}

void UserManager::loadUsers() {

}
