
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <unordered_map>
#include <vector>
#include <User.h>
#include <ReturnCode.h>

class UserController {

public:
	struct UserData {
		std::string username;
		ReturnCode returnCode;
	};

	std::unordered_map<std::string, uintptr_t> getActiveUsers();

	void addActiveUser(std::string username, uintptr_t connectionId);

	bool isUserActive(std::string username);

	bool isConnectionLoggedIn(uintptr_t connectionId);

	std::string getUsernameWithConnectionId(uintptr_t connectionId);

	uintptr_t getConnectionIdWithUsername(std::string username);

	UserData login(std::string username, std::string password, uintptr_t connectionId);

	UserData createUser(std::string username, std::string password);

	UserData logoutUser(std::string username);

private:
	std::unordered_map<std::string, uintptr_t> activeUsers = {};

	auto hashPassword(std::string password);

	ReturnCode parseLoginUserData(std::string username, std::string password);

	ReturnCode parseNewUserData(std::string username, std::string password);
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
