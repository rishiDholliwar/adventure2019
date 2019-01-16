//
// Created by ximinz on 16/01/19.
//

#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include "User.h"

class UserManager {
public:
    void loadUsers();
    User lookUpUser(std::string userName, std::string hashedPassword);

};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
