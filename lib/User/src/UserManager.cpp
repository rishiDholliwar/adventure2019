#include "../include/UserManager.h"

// User UserManager::findUser(std::string userName, std::size_t hashedPassword) {
//     if(userName == "a"){
//         User a(networking::Connection{2}, "a", "b");
//         a.moveToRoom(5);
//         return a;
//     }
//     return User(networking::Connection{1}, "b", "b");
// }

// bool UserManager::userExists(std::string username, std::string password) {

// 	std::set<User>::iterator it = users.find(username);

// 	if (it != users.end()) {

// 		auto hashedPassword = std::hash<std::string>{}(password);

// 		if (*it.isHashedPasswordEqual(hashedPassword)) {
// 			return true;
// 		}
// 	}
// 	return false;
// }

void UserManager::tryLoginAgain() {
	// Output to screen
}

// Return iterator to user with matching username, if exists
std::set<User>::iterator UserManager::findUsername(std::string username) {
	User tempUser(username);

	std::set<User>::iterator it = UserManager::users.find(tempUser);

	return it;
}

bool UserManager::passwordMatchesUsername(std::string password, std::set<User>::iterator it) {

	auto hashedPassword = std::hash<std::string>{}(password);

	if (*it.isHashedPasswordEqual(hashedPassword)) {
		return true;
	}

	return false;
}


void UserManager::login(long connectionId, std::string userName, std::string password) {
	
	std::set<User>::iterator it = findUsername(userName);

	if (it != UserManager::users.end()) {
		//username exists
		if (passwordMatchesUsername(password, it)) {

			*it.startSession(connectionId);
		} else {
			throw std::invalid_argument("Account does not exist"); // TBD custom exception class
		}
				
	} else {
		throw std::invalid_argument("Account does not exist");
	}
}

void UserManager::createUser(long connectionId, std::string userName, std::string password) {

	std::set<User>::iterator it = findUsername(userName);

	if (it != UserManager::users.end()) {
		throw std::invalid_argument("Username is taken")
	} else {
		//username does not exist
		auto hashedPassword = std::hash<std::string>{}(password);
		User newUser(connectionId, username, hashedPassword);
		UserManager::users.insert(newUser);
	}
}

void UserManager::loadUsers() {
	//
}

User UserManager::lookUpUser(std::string userName, std::string password) {
	//
}
