#include <UserController.h>

std::map<std::string, std::string> UserController::getActiveUsers() {
	return activeUsers;
}

void UserController::addActiveUser(std::string username, std::string connectionId) {
	activeUsers.insert(std::pair<std::string, std::string>(username, connectionId));
}

bool UserController::isThisUserActive(std::string username) {
	//check if username exists in activeUsers.
	//if true, return true. else, this user is not yet logged in or created.
	std::map<std::string, std::string>::iterator it = activeUsers.find(username);

	if (it != activeUsers.end()) {
		return true;
	}

	return false;
}

bool UserController::isConnectionLoggedIn(std::string connectionId) {
	bool isLoggedIn = false;

	for(auto userConnection : activeUsers) {
		if (userConnection.second == connectionId) {
			isLoggedIn = true;
		}
	}

	return isLoggedIn;
}

std::string UserController::getUsernameWithConnectionId(std::string connectionId) {

	for (auto user : activeUsers) {
		if (user.second == connectionID) {
			return user.first;
		}
	} return std::string();
}

std::string UserController::getConnectionIdWithUsername(std::string username) {
	//
}

auto UserController::hashPassword(std::string password) {

	auto hashedPassword = std::hash<std::string>{}(password);

	return hashedPassword;
}

UserData UserController::login(std::string username, std::string password, std::string connectionId) {

	UserData result;
	result.username = username;

	//check if user is already logged in:
	if (isThisUserActive(username)) {
		result.returnCode = ReturnCode::USER_ACTIVE;
		// + character data

	} else {

		ReturnCode isLoginSuccess = parseLoginUserData(username, password);

		if (isLoginSuccess == ReturnCode::LOGIN_SUCCESS) {
			result.returnCode = ReturnCode::LOGIN_SUCCESS;
			result.characterData = parseLoginCharacterData(username);
			addActiveUser(username, connectionId);

		} else {
			std::vector<std::string> blankCharData;
			result.returnCode = isLoginSuccess; // USERNAME_FAIL or PASSWORD_FAIL
			result.characterData = blankCharData;
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

std::vector<std::string> UserController::parseLoginCharacterData(std::string username) {
	std::vector<std::string> charData;

	//dummy value for testing.
	charData.push_back("charName");

	//when json parser library is implemented, find username.json in user/chardata/ directory
	//read in the .json file to the library, get back the array or vector or some return type of info
	//return the chardata info to login.

	return charData;
}

UserData UserController::createUser(std::string username, std::string password) {

	UserData result;
	result.username = username;

	//check if user is already logged in:
	if (isThisUserActive(username)) {
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

UserData UserController::logoutUser(std::string username, std::vector<std::string> newCharData) {

	UserData result;
	result.username = username;

	if (!(isThisUserActive(username))) {
		result.returnCode = ReturnCode::LOGOUT_FAIL;
		// + character data

	} else {
		result.returnCode = saveCharacterDataBeforeLogout(username, newCharData);
		// + character data
	}

	activeUsers.erase(username);
	return result;
}

ReturnCode UserController::saveCharacterDataBeforeLogout(std::string username, std::vector<std::string> newCharData) {
	//find username.json file in chardata directory
	//write in the changed vector of char data after gameplay
	//if success, ReturnCode::SAVE_SUCCESS. else, ReturnCode::SAVE_FAIL
	return ReturnCode::SAVE_SUCCESS;
}
