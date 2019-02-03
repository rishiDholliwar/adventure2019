#include <UserController.h>

std::unordered_map<std::string, Connection> UserController::getActiveUsers() {
	return activeUsers;
}

void UserController::addActiveUser(const std::string& username, Connection connection) {
	activeUsers.insert(std::pair<std::string, Connection>(std::move(username), connection));
}

bool UserController::isUserActive(const std::string& username) {
	//check if username exists in activeUsers.
	//if true, return true. else, this user is not yet logged in or created.

	return activeUsers.find(username) != activeUsers.end();
}

bool UserController::isConnectionLoggedIn(const Connection connection) {
	bool isLoggedIn = false;

	for(auto userConnection : activeUsers) {
		if (userConnection.second == connection) {
			isLoggedIn = true;
		}
	}

	return isLoggedIn;
}

std::string UserController::getUsernameWithConnection(const Connection connection) {

	for (auto user : activeUsers) {
		if (user.second == connection) {
			return user.first;
		}
	}
	return std::string();
}

Connection UserController::getConnectionWithUsername(const std::string& username) {
	//
}

std::size_t UserController::hashPassword(std::string password) {

	auto hashedPassword = std::hash<std::string>{}(password);

	return hashedPassword;
}

UserController::UserData UserController::login(const std::string& username, std::string password, const Connection connection) {

	UserData result;
	result.username = username;

	//check if user is already logged in:
	if (isUserActive(username)) {
		result.returnCode = ReturnCode::USER_ACTIVE;
		return result;

	}

	result.returnCode = parseLoginUserData(username, password);

	if (result.returnCode == ReturnCode::LOGIN_SUCCESS) {
		addActiveUser(username, connection);
	}

	return result;
}

ReturnCode UserController::parseLoginUserData(const std::string_view username, std::string password) {

	auto hashedPassword = hashPassword(password);
	//look for username.json in some .../user/userdata/ directory
	//using json library api parser that will eventually be created by the group,

	//if username.json doesn't exist, ReturnCode::USERNAME_FAIL

	// Check if hashedPassword matches hashedPassword in username.json
	// If true, ReturnCode::LOGIN_SUCCESS, else ReturnCode::PASSWORD_FAIL

	return ReturnCode::LOGIN_SUCCESS;
}

UserController::UserData UserController::createUser(const std::string& username, std::string password,  const Connection connection) {

	UserData result;
	result.username = username;

	//check if user is already logged in:
	if (isUserActive(username)) {
		result.returnCode = ReturnCode::USER_ACTIVE;
		// + character data?
		return result;

	}

	result.returnCode = parseNewUserData(username, password);

	return result;
}

ReturnCode UserController::parseNewUserData(const std::string_view username, std::string password) {

	//make sure no .json file exists with that username.
	//if such file already exists, return ReturnCode::USERNAME_EXISTS

	//if no file already exists, hash password.
	auto hashedPassword = hashPassword(password);

	//create username.json file, read in username and hashed password

	return ReturnCode::LOGIN_SUCCESS;
}

UserController::UserData UserController::logoutUser(const std::string& username) {

	UserData result;
	result.username = username;

	if (!(isUserActive(username))) {
		result.returnCode = ReturnCode::LOGOUT_FAIL;
		return result;

	}
	
	activeUsers.erase(username);
	// + character data
	result.returnCode = ReturnCode::LOGOUT_SUCCESS;

	return result;
}
