
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

	std::unordered_map<std::string, Connection> getActiveUsers();

	void addActiveUser(std::string username, Connection connectionId);

	bool isUserActive(const std::string_view username);

	bool isConnectionLoggedIn(const Connection connectionId);

	std::string getUsernameWithConnectionId(const Connection connectionId);

	Connection getConnectionIdWithUsername(const std::string_view username);

	UserData login(const std::string_view username, std::string password, const Connection connectionId);

	UserData createUser(const std::string_view username, std::string password);

	UserData logoutUser(std::string username);

private:
	std::unordered_map<std::string, Connection> activeUsers = {};

	auto hashPassword(std::string password);

	ReturnCode parseLoginUserData(const std::string_view username, std::string password);

	ReturnCode parseNewUserData(const std::string_view username, std::string password);
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
