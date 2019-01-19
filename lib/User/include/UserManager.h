
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <set>
#include "User.h"

class UserManager {

public:

	std::set<User> getUsers();

	void addUser(User user);

	// User findUser(std::string userName, std::size_t hashedPassword);

	std::set<User>::iterator findUsername(std::string username);

	bool passwordMatchesUsername(std::string password, const std::set<User>::iterator it);

	// bool userExists(std::string username, std::string password);

	bool login(std::string userName, std::string password);

	bool createUser(std::string userName, std::string password);

    void loadUsers();

    User lookUpUser(std::string userName, std::string password);

    User getUserByUsername(std::string userName);

private:
	std::set<User> users = {};
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
