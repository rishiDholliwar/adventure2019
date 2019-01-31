#include <UserController.h>

std::unordered_map<std::string, uintptr_t> UserController::getActiveUsers() {
	return activeUsers;
}

void UserController::addActiveUser(std::string username, uintptr_t connectionId) {
	activeUsers.insert(std::pair<std::string, uintptr_t>(username, connectionId));
}

bool UserController::isUserActive(std::string username) {
	//check if username exists in activeUsers.
	//if true, return true. else, this user is not yet logged in or created.
	std::unordered_map<std::string, uintptr_t>::iterator it = activeUsers.find(username);

	if (it != activeUsers.end()) {
		return true;
	}

	return false;
}

bool UserController::isConnectionLoggedIn(uintptr_t connectionId) {
	bool isLoggedIn = false;

	for(auto userConnection : activeUsers) {
		if (userConnection.second == connectionId) {
			isLoggedIn = true;
		}
	}

	return isLoggedIn;
}

std::string UserController::getUsernameWithConnectionId(uintptr_t connectionId) {

	for (auto user : activeUsers) {
		if (user.second == connectionId) {
			return user.first;
		}
	}

	return std::string();
}

uintptr_t UserController::getConnectionIdWithUsername(std::string username) {
	//
}

auto UserController::hashPassword(std::string password) {

	auto hashedPassword = std::hash<std::string>{}(password);

	return hashedPassword;
}

UserController::UserData UserController::login(std::string username, std::string password, uintptr_t connectionId) {

	UserData result;
	result.username = username;

	//check if user is already logged in:
	if (isUserActive(username)) {
		result.returnCode = ReturnCode::USER_ACTIVE;

	} else {

		ReturnCode isLoginSuccess = parseLoginUserData(username, password);

		if (isLoginSuccess == ReturnCode::LOGIN_SUCCESS) {
			result.returnCode = ReturnCode::LOGIN_SUCCESS;
			addActiveUser(username, connectionId);

		} else {
			result.returnCode = isLoginSuccess; // USERNAME_FAIL or PASSWORD_FAIL
		}
	}
	return result;
}

ReturnCode UserController::parseLoginUserData(std::string username, std::string password) {

	auto hashedPassword = hashPassword(password);
	//look for username.json in some .../user/userdata/ directory
	//using json library api parser that will eventually be created by the group,

	//if username.json doesn't exist, ReturnCode::USERNAME_FAIL

	// Check if hashedPassword matches hashedPassword in username.json
	// If true, ReturnCode::LOGIN_SUCCESS, else ReturnCode::PASSWORD_FAIL

	return ReturnCode::LOGIN_SUCCESS;
}

UserController::UserData UserController::createUser(std::string username, std::string password) {

	UserData result;
	result.username = username;

	//check if user is already logged in:
	if (isUserActive(username)) {
		result.returnCode = ReturnCode::USER_ACTIVE;
		// + character data?

	} else {

		ReturnCode userCreateSuccess = parseNewUserData(username, password);

		if (userCreateSuccess == ReturnCode::USERNAME_EXISTS) {
			result.returnCode == ReturnCode::USERNAME_EXISTS;
			// + dummy character data or empty vector

		} else {
			result.returnCode = ReturnCode::CREATE_SUCCESS;
			// + default character data?
		}
	}
	return result;
}

ReturnCode UserController::parseNewUserData(std::string username, std::string password) {

	//make sure no .json file exists with that username.
	//if such file already exists, return ReturnCode::USERNAME_EXISTS

	//if no file already exists, hash password.
	auto hashedPassword = hashPassword(password);

	//create username.json file, read in username and hashed password

	return ReturnCode::LOGIN_SUCCESS;
}

UserController::UserData UserController::logoutUser(std::string username) {

	UserData result;
	result.username = username;

	if (!(isUserActive(username))) {
		result.returnCode = ReturnCode::LOGOUT_FAIL;

	} else {
		activeUsers.erase(username);
		// + character data
		result.returnCode = ReturnCode::LOGOUT_SUCCESS;
	}

	return result;
}
