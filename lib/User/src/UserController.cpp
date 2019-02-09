#include <UserController.h>
#include <User.h>

std::unordered_map<std::string, Connection> UserController::getActiveUsers() {
	return activeUsers;
}

void UserController::addActiveUser(const User::Name username, Connection connection) {
	activeUsers.insert(std::pair<std::string, Connection>(std::move(username), connection));
}

bool UserController::isUserActive(const User::Name& username) {
	//check if username exists in activeUsers.
	//if true, return true. else, this user is not yet logged in or created.

	return activeUsers.find(username) != activeUsers.end();
}

auto UserController::getIteratorWithConnection(const Connection connection) {

	auto itrToUsername = find_if(activeUsers.begin(), activeUsers.end(),
		[&connection](const std::pair<std::string, Connection>& userConnection)
		{ return userConnection.second == connection; } );

	return itrToUsername;
}

bool UserController::isConnectionLoggedIn(const Connection connection) {
	bool isLoggedIn = false;

	if (getIteratorWithConnection(connection) != activeUsers.end()) {

		isLoggedIn = true;
	
	}

	return isLoggedIn;
}

std::string UserController::getUsernameWithConnection(const Connection connection) {

	if (isConnectionLoggedIn(connection) == false) {
		return std::string();
	}

	auto itrToUsername = getIteratorWithConnection(connection);


	return itrToUsername->first;

}

Connection UserController::getConnectionWithUsername(const User::Name& username) {

	auto userItr = activeUsers.find(username);

	if (userItr != activeUsers.end()) {
		return userItr->second;

	}

	//chatserver.cpp checks for whether or not connection is logged in before calling this function
	//...so this return statement should never be needed.
	return Connection();
}

std::size_t UserController::hashPassword(std::string password) {

	auto hashedPassword = std::hash<std::string> {}(password);

	return hashedPassword;
}

UserController::UserData UserController::login(const User::Name& username, std::string password, const Connection connection) {

	UserData result;
	result.username = username;

	result.returnCode = validateLoginUserData(username, password);

	if (result.returnCode == ReturnCode::LOGIN_SUCCESS) {
		addActiveUser(username, connection);
	}

	return result;
}

ReturnCode UserController::validateLoginUserData(const User::Name username, std::string password) {

	//check if user is already logged in:
	if (isUserActive(username)) {

		return ReturnCode::USER_ACTIVE;
	}

	auto hashedPassword = hashPassword(password);
	//look for username.json in some .../user/userdata/ directory
	//using json library api parser that will eventually be created by the group,

	//if username.json doesn't exist, ReturnCode::USERNAME_FAIL

	// Check if hashedPassword matches hashedPassword in username.json
	// If true, ReturnCode::LOGIN_SUCCESS, else ReturnCode::PASSWORD_FAIL

	return ReturnCode::LOGIN_SUCCESS;
}

UserController::UserData UserController::createUser(const User::Name& username, std::string password,  const Connection connection) {

	UserData result;
	result.username = username;

	result.returnCode = validateNewUserData(username, password);

	if (result.returnCode == ReturnCode::CREATE_SUCCESS) {
		login(username, password, connection);
	}

	return result;
}

ReturnCode UserController::validateNewUserData(const User::Name username, std::string password) {

	//check if user is already logged in:
	if (isUserActive(username)) {

		return ReturnCode::USER_ACTIVE;
	}

	//make sure no .json file exists with that username.
	//if such file already exists, return ReturnCode::USERNAME_EXISTS

	//if no file already exists, hash password.
	auto hashedPassword = hashPassword(password);

	//create username.json file, read in username and hashed password

	return ReturnCode::CREATE_SUCCESS;
}

UserController::UserData UserController::logoutUser(const User::Name& username) {

	UserData result;
	result.username = username;

	if (activeUsers.erase(username) != 1) {
		result.returnCode = ReturnCode::LOGOUT_FAIL;
		return result;
	}

	// + character data
	result.returnCode = ReturnCode::LOGOUT_SUCCESS;

	return result;
}

UserController::UserData UserController::logoutUser(const std::string& username, std::string password, const Connection connection)
{
	return logoutUser(username);
}
