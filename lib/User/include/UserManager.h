
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <set>
#include "User.h"

class UserManager {

public:

	std::set<User> getUsers();

	void addUser(User user);

	std::set<User>::iterator findUsername(std::string username);

	bool passwordMatchesUsername(std::string password, const std::set<User>::iterator it);

	bool login(std::string userName, std::string password);

	bool createUser(std::string userName, std::string password);

  void loadUsers();

  User lookUpUser(std::string userName, std::string password);

  User getUserByUsername(std::string userName);

private:
	std::set<User> users = {};
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
