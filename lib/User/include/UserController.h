
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <unordered_map>
// #include <boost/multi_index_container.hpp>
// #include <boost/multi_index/hashed_index.hpp>
// #include <boost/multi_index/member.hpp>
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
		std::string username;
		ReturnCode returnCode;
	};

	std::unordered_map<std::string, Connection> getActiveUsers();

	void addActiveUser(const std::string& username, Connection connection);

	bool isUserActive(const std::string& username);

	bool isConnectionLoggedIn(const Connection connection);

	std::string getUsernameWithConnection(const Connection connection);

	Connection getConnectionWithUsername(const std::string& username);

	UserData login(const std::string& username, std::string password, const Connection connection);

	UserData createUser(const std::string& username, std::string password, const Connection connection);

	UserData logoutUser(const std::string& username);

	UserData logoutUser(const std::string& username, std::string password, const Connection connection);

private:
	std::unordered_map<std::string, Connection> activeUsers = {};
	// unordered_string_map<std::string, Connection, std::less<>> activeUsers = {};

	std::size_t hashPassword(std::string password);

	ReturnCode parseLoginUserData(const std::string_view username, std::string password);

	ReturnCode parseNewUserData(const std::string_view username, std::string password);
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
