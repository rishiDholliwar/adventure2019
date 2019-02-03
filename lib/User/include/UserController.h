
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <unordered_map>
// #include <boost/multi_index_container.hpp>
// #include <boost/multi_index/hashed_index.hpp>
// #include <boost/multi_index/member.hpp>
#include <vector>
#include <User.h>
#include <ReturnCode.h>
#include "Server.h"
#include <functional>

using networking::Connection;

class UserController {

public:
	struct UserData {
		User::Name username;
		ReturnCode returnCode;
	};

	std::unordered_map<std::string, Connection> getActiveUsers();

	void addActiveUser(const User::Name& username, Connection connection);

	bool isUserActive(const User::Name& username);

	bool isConnectionLoggedIn(const Connection connection);

	std::string getUsernameWithConnection(const Connection connection);

	Connection getConnectionWithUsername(const User::Name& username);

	UserData login(const User::Name& username, std::string password, const Connection connection);

	UserData createUser(const User::Name& username, std::string password, const Connection connection);

	UserData logoutUser(const User::Name& username);

private:
	std::unordered_map<std::string, Connection> activeUsers = {};
	// unordered_string_map<std::string, Connection, std::less<>> activeUsers = {};

	std::size_t hashPassword(std::string password);

	ReturnCode parseLoginUserData(const User::Name username, std::string password);

	ReturnCode parseNewUserData(const User::Name username, std::string password);
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
