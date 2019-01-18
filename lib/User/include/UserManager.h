
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <set>
#include "User.h"

class UserManager {

public:

	std::set<User> users = {};

	// User findUser(std::string userName, std::size_t hashedPassword);

	std::set<User>::iterator findUsername(std::string username);

	bool passwordMatchesUsername(std::string password, std::set<User>::iterator it);

	// bool userExists(std::string username, std::string password);

	void tryLoginAgain();

	void login(long connectionId, std::string userName, std::string password);

	void createUser(long connectionId, std::string userName, std::string password);

    void loadUsers();

    User lookUpUser(std::string userName, std::string password);

};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
