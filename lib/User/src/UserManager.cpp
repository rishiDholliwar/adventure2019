#include "../include/UserManager.h"

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

bool UserManager::passwordMatchesUsername(std::string password, const std::set<User>::iterator it) {

	auto hashedPassword = std::hash<std::string>{}(password);

	if ((*it).User::isHashedPasswordEqual(hashedPassword)) {
		return true;
	}

	return false;
}

bool UserManager::login(std::string userName, std::string password) {

	const std::set<User>::iterator it = findUsername(userName);

	//username doesn't exist
	if (it == UserManager::users.end()) {
		return false;
		//return error_return_code
	}

	if (passwordMatchesUsername(password, it)) {
		return true;
		//return success_return_code
	} else {
		return false;
		//return error_return_code
	}
}

bool UserManager::createUser(std::string userName, std::string password) {

	std::set<User>::iterator it = findUsername(userName);

	//username already exists
	if (it != UserManager::users.end()) {
		return false;
		//return error_return_code
	}

	//username does not exist
	auto hashedPassword = std::hash<std::string>{}(password);
	User newUser(userName, hashedPassword);
	UserManager::users.insert(newUser);

	if (findUsername(userName) != users.end()) {
		return true;
		//return success_return_code
	} else {
		return false;
		//return error_return_code
	}
}

void UserManager::loadUsers() {
	//
}

User UserManager::lookUpUser(std::string userName, std::string password) {
	//just a dummy user for stableness
	User tempUser(userName);

	return tempUser;
}

User UserManager::getUserByUsername(std::string userName) {
	std::set<User>::iterator it = findUsername(userName);

	return *it;
}
