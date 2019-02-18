#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

#include <AlterSpace.h>
#include <User.h>
#include "Server.h"
#include <ReturnCodes.h>

using AlterSpace::Name;
using AlterSpace::Password;

using networking::Connection;

class UserController {

public:
	struct UserData {
		Name username;
		ReturnCode returnCode;
	};

	std::unordered_map<std::string, Connection> getActiveUsers();

	void addActiveUser(const Name username, Connection connection);

	bool isUserActive(const Name& username);

	bool isConnectionLoggedIn(const Connection connection);

	std::string getUsernameWithConnection(const Connection connection);

	Connection getConnectionWithUsername(const Name& username);


    /* if username exists and isn't logged in already, logs them in and returns the outcome
     *
     * Pre-Condition: username as const reference Name objType, password as string and a const Connection object
     *
     * Post-Condition: a struct of username and a login result
     */

	UserData login(const Name& username, Password password, const Connection connection);

	/*
     * if no such username exists already, creates a user with such username and password
     *
     * Pre-Condition: username as const reference Name objType, password as string and a const Connection object
     *
     * Post-Condition: a struct of username and a user creation result
	*/
	UserData createUser(const Name& username, Password password, const Connection connection);

	/*
     * logs out a username by deleting it from the map of activeUsers
     *
     * Pre-Condition: username as const reference Name objType
     *
     * Post-Condition: a struct of username and a logout result
	*/
	UserData logoutUser(const Name& username);

	UserData logoutUser(const Name& username, Password password, const Connection connection);

private:
	std::unordered_map<Name, Connection> activeUsers = {};
	// unordered_string_map<std::string, Connection, std::less<>> activeUsers = {};

	auto getIteratorWithConnection(const Connection connection);

	std::size_t hashPassword(Password password);

	/*
     * In the process of login,
     * looks for a json file for the username, compares login information for accuracy
     * If a user is already logged in with such username or if the password is inaccurate, login fails
     * Password passed in is hashed for security
     *
     * Pre-Condition: username as const reference Name objType, password as string
     *
     * Post-Condition: a result value of whether a user is found and validated successfully
	*/
	ReturnCode validateLoginUserData(const Name username, Password password);

	/*
     * In the process of creating user,
     * checks to see a user isn't already logged in with such username
     * looks for a json file for the username to make sure no such user exists already
	 * creates a file to store the login information for the future
	 * password is hashed for security before being stored
     *
     * Pre-Condition: username as const reference Name objType, password as string
     *
     * Post-Condition: a result value of whether a new user is created succesfully
	*/
	ReturnCode validateNewUserData(const Name username, Password password);
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
