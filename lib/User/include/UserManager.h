
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <set>
#include "User.h"

class UserManager {

public:

	std::set<std::string, User> users; 

	User findUser(std::string userName, std::string hashedPassword);

	bool userExists(std::string username, std::string password);

	void tryLoginAgain();

	void login(std::string userName, std::string password);

    void loadUsers();

    

};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
