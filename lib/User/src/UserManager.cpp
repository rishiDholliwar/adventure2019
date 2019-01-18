#include "../include/UserManager.h"

// User UserManager::findUser(std::string userName, std::size_t hashedPassword) {
//     if(userName == "a"){
//         User a(networking::Connection{2}, "a", "b");
//         a.moveToRoom(5);
//         return a;
//     }
//     return User(networking::Connection{1}, "b", "b");
// }

std::set<User> UserManager::getUsers() {
	return users;
}

void UserManager::addUser(User user) {
	users.insert(user);
}


std::set<User>::iterator UserManager::findUsername(std::string username) {
	User tempUser(username);

	std::set<User>::iterator it = users.find(tempUser);

	return it;
}

bool UserManager::passwordMatchesUsername(std::string password, std::set<User>::iterator it) {

	auto hashedPassword = std::hash<std::string>{}(password);

	if ((*it).User::isHashedPasswordEqual(hashedPassword)) {
		return true;
	}

	return false;
}

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

void UserManager::login(long connectionId, std::string userName, std::string password) {
	std::set<User>::iterator it = findUsername(userName);

	if (it != UserManager::users.end()) {
		//username exists
		if (passwordMatchesUsername(password, it)) {

			(*it).User::startSession(connectionId);
		} else {
			// throw e //planning to write a custom error class: login invalid
		}
				
	} else {
		//username does not exist
		// throw e; //might not be syntatically correct rn
	}

	// if (userExists(username, password)) {

	// 	std::set<User>::iterator it = users.find(username);

	// 	*it.startSession(connectionId);

	// } else {
	// 	tryLoginAgain();
	// }
}

void UserManager::createUser(long connectionId, std::string userName, std::string password) {

	std::set<User>::iterator it = findUsername(userName);

	if (it != UserManager::users.end()) {
		//username exists
		// throw e;	
	} else {
		//username does not exist
		auto hashedPassword = std::hash<std::string>{}(password);
		User newUser(connectionId, userName, hashedPassword);
		UserManager::users.insert(newUser);
	}
}

void UserManager::loadUsers() {
	//
}

User UserManager::lookUpUser(std::string userName, std::string password) {
	//
}

User UserManager::getUserByUsername(std::string userName) {
	std::set<User>::iterator it = findUsername(userName);

	return *it;
}
