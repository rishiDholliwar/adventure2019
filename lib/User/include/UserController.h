
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <set>
#include "User.h"

class UserManager {

public:

	std::set<User> getUsers();

	void addUser(User user);

	std::set<User>::iterator findusername(std::string username);

	bool passwordMatchesusername(std::string password, const std::set<User>::iterator it);

	bool login(std::string username, std::string password);

	bool createUser(std::string username, std::string password);

  void loadUsers();

  User lookUpUser(std::string username, std::string password);

  User getUserByusername(std::string username);

private:
	std::set<User> users = {};
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
