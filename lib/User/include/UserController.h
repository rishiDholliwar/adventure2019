
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <unordered_map>
#include <vector>
#include <User.h>
#include "Server.h"
#include <functional>

using networking::Connection;

enum class ReturnCode {

    USER_ACTIVE,      // User is currently logged in
    LOGIN_SUCCESS,    // User login authenticated
    LOGOUT_SUCCESS,   // User logout success
    LOGOUT_FAIL,      // User attempting logout is not active
    SAVE_SUCCESS,     // Succesfully saved character data before logout
    SAVE_FAIL,        // Unable to save character data
    PASSWORD_FAIL,    // Password incorrect (does not match username)
    USERNAME_EXISTS,  // Cannot create a user with this username; username taken
    USERNAME_FAIL,    // Account (Username.json) does not exist for this username
    CREATE_SUCCESS,   // User creation was success
};

namespace Return
{

    static const std::unordered_map<ReturnCode, std::string>
    ReturnCodeResponses = {
        { ReturnCode::USER_ACTIVE,    "User is active" },
        { ReturnCode::LOGIN_SUCCESS,  "Logged in succesfully" },
        { ReturnCode::LOGOUT_SUCCESS, "Logged out succesfully" },
        { ReturnCode::LOGOUT_FAIL,    "Failed to logout" },
        { ReturnCode::SAVE_SUCCESS,   "Saved succesfully" },
        { ReturnCode::SAVE_FAIL,      "Failed to save" },
        { ReturnCode::PASSWORD_FAIL,  "Incorrect password" },
        { ReturnCode::USERNAME_EXISTS, "Username already taken" },
        { ReturnCode::USERNAME_FAIL,  "Username does not exist" },
        { ReturnCode::CREATE_SUCCESS, "Succesfully created character"}
    };

    inline std::string ReturnCodeToString( ReturnCode rc )
    {
        if( ReturnCodeResponses.find(rc) == ReturnCodeResponses.end() )
        {
            return "Unknown response";
        }
        return ReturnCodeResponses.at(rc);
    }
}


class UserController {

public:
	struct UserData {
		User::Name username;
		ReturnCode returnCode;
	};

	std::unordered_map<std::string, Connection> getActiveUsers();

	void addActiveUser(const User::Name username, Connection connection);

	bool isUserActive(const User::Name& username);

	bool isConnectionLoggedIn(const Connection connection);

	std::string getUsernameWithConnection(const Connection connection);

	Connection getConnectionWithUsername(const User::Name& username);

	 
    /* if username exists and isn't logged in already, logs them in and returns the outcome
     *
     * Pre-Condition: username as const reference User::Name type, password as string and a const Connection object
     * 
     * Post-Condition: a struct of username and a login result
     */
	
	UserData login(const User::Name& username, std::string password, const Connection connection);

	/* 
     * if no such username exists already, creates a user with such username and password
     *
     * Pre-Condition: username as const reference User::Name type, password as string and a const Connection object
     * 
     * Post-Condition: a struct of username and a user creation result
	*/
	UserData createUser(const User::Name& username, std::string password, const Connection connection);

	/* 
     * logs out a username by deleting it from the map of activeUsers
     *
     * Pre-Condition: username as const reference User::Name type
     * 
     * Post-Condition: a struct of username and a logout result
	*/
	UserData logoutUser(const User::Name& username);

	UserData logoutUser(const std::string& username, std::string password, const Connection connection);

private:
	std::unordered_map<std::string, Connection> activeUsers = {};
	// unordered_string_map<std::string, Connection, std::less<>> activeUsers = {};

	auto getIteratorWithConnection(const Connection connection);

	std::size_t hashPassword(std::string password);

	/* 
     * In the process of login,
     * looks for a json file for the username, compares login information for accuracy
     * If a user is already logged in with such username or if the password is inaccurate, login fails
     * Password passed in is hashed for security
     *
     * Pre-Condition: username as const reference User::Name type, password as string
     * 
     * Post-Condition: a result value of whether a user is found and validated successfully
	*/
	ReturnCode validateLoginUserData(const User::Name username, std::string password);

	/* 
     * In the process of creating user,
     * checks to see a user isn't already logged in with such username
     * looks for a json file for the username to make sure no such user exists already
	 * creates a file to store the login information for the future
	 * password is hashed for security before being stored
     *
     * Pre-Condition: username as const reference User::Name type, password as string
     * 
     * Post-Condition: a result value of whether a new user is created succesfully
	*/
	ReturnCode validateNewUserData(const User::Name username, std::string password);
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
