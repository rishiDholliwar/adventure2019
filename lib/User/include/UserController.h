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
<<<<<<< HEAD
     * Pre-Condition: login credentials for user attempting login
=======
     * Pre-Condition: username as const reference Name objectName, password as string and a const Connection object
>>>>>>> inventory
     *
     * Post-Condition: returns username and success/failure of user login
     */

	UserData login(const Name& username, Password password, const Connection connection);

	/*
     * if no such username exists already, creates a user with such username and password
     *
<<<<<<< HEAD
     * Pre-Condition: login credentials for user being created
=======
     * Pre-Condition: username as const reference Name objectName, password as string and a const Connection object
>>>>>>> inventory
     *
     * Post-Condition: returns username and success/failure code for user created
	*/
	UserData createUser(const Name& username, Password password, const Connection connection);

	/*
     * logs out a username by deleting it from the map of activeUsers
     *
<<<<<<< HEAD
     * Pre-Condition: username of user logging out
=======
     * Pre-Condition: username as const reference Name objectName
>>>>>>> inventory
     *
     * Post-Condition: returns username and success/failure of user logout
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
<<<<<<< HEAD
     * Pre-Condition: login credentials to authenticate user
=======
     * Pre-Condition: username as const reference Name objectName, password as string
>>>>>>> inventory
     *
     * Post-Condition: returns a success/failure code for finding and validating user
	*/
	ReturnCode validateLoginUserData(const Name username, Password password);

	/*
     * In the process of creating user,
     * checks to see a user isn't already logged in with such username
     * looks for a json file for the username to make sure no such user exists already
	 	 * creates a file to store the login information for the future
	 	 * password is hashed for security before being stored
     *
<<<<<<< HEAD
     * Pre-Condition: login credentials for new user
=======
     * Pre-Condition: username as const reference Name objectName, password as string
>>>>>>> inventory
     *
     * Post-Condition: returns a success/failure code for validating new user
	*/
	ReturnCode validateNewUserData(const Name username, Password password);
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
