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

std::string UserController::getUsernameWithConnectionId(std::string connectionId) {
	//
}

std::string UserController::getConnectionIdWithUsername(std::string username) {
	//
}

auto UserController::hashPassword(std::string password) {

	auto hashedPassword = std::hash<std::string>{}(password);

	return hashedPassword;
}

//eventually will return a struct of username, returncode and character data?
bool UserController::login(std::string username, std::string password, std::string connectionId) {
	//check if user is already logged in:
	if (isThisUserActive(username)) {
		//return a struct with username, already logged in return code, and some character data
		return false;
	}

	//when enum codes are implemented, this bool will be an enum and check if return code is success or failure.
	bool isLoginSuccess = parseLoginUserData(username, password);

	if (isLoginSuccess) {
		parseLoginCharacterData(username);
		addActiveUser(username, connectionId);
		return true;
		//return struct? of username, success_return_code, vector? of character data
	}

	//if login is fail:
	std::vector<std::string> blankCharData;

	return false;
	//return struct of username, success_return_code, empty vector blankCharData
}

bool UserController::parseLoginUserData(std::string username, std::string password) {

	//when enum return codes get implemented, change both the return type of this function and loginSuccess to the enum type.
	bool loginSuccess = false;
	auto hashedPassword = hashPassword(password);
	//look for username.json in some .../user/userdata/ directory
	//using json library api parser that will eventually be created by the group,

	//if username.json doesn't exist, loginSuccess is username fail. return loginSuccess.

	//within userneame.json, see if hashedPassword matches hashedPassword in .json file
	//if false, return code is a password failure. return loginSuccess.

	//if both are true, loginSuccess is true.
	loginSuccess = true;
	return loginSuccess;
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

//later will have to return a struct of username, returncode, and some character data
bool UserController::createUser(std::string username, std::string password) {
	//check if user is already logged in:
	if (isThisUserActive(username)) {
		//return a struct with username, already logged in return code, and some character data
		return false;
	}

	//change this bool to enum later:
	bool userCreateSuccess = parseNewUserData(username, password);

	//if returnCode is "user already exists",
	if (!(userCreateSuccess)) {
		//create a struct of username, fail return code and some dummy character data or empty vector
		return false;
	}

	//if successful, return a struct of username, success return code and a basic character data?
	return true;
}

//will return a enum return code at some point in the future
bool UserController::parseNewUserData(std::string username, std::string password) {
	bool newUserDataParsed = false;

	//make sure no .json file exists with that username.
	//if such file already exists, return a return code that says something like "Username already exists"

	//if no file already exists, has password.
	auto hashedPassword = hashPassword(password);

	//create .json file, read in username and hashed password
	//if successfully created, return code is success as well.
	//return the return code.
	newUserDataParsed = true;
	return newUserDataParsed;
}

//eventually logoutUser will also return a struct of username and return code and some such.
bool UserController::logoutUser(std::string username, std::vector<std::string> newCharData) {
	//will eventually be enum
	bool returnCode;
	//check if user is logged in atm.
	if (!(isThisUserActive(username))) {
		//return struct of username, failed return code and maybe some char data.
	}

	//else if the user is logged in rn,
	returnCode = saveCharacterDataBeforeLogout(username, newCharData);
	//return struct of username, success return code and maybe some data if needed.
	return returnCode;
}

bool UserController::saveCharacterDataBeforeLogout(std::string username, std::vector<std::string> newCharData) {
	//find username.json file in chardata directory
	//write in the changed vector of char data after gameplay
	//if success, return success return code. else, return fail return code.
	return true;
}