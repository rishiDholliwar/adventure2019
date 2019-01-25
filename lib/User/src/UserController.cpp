#include "../include/UserController.h"

std::set<User> UserController::getUsers() {
	return users;
}

void UserController::addUser(User user) {
	users.insert(user);
}


std::set<User>::iterator UserController::findusername(std::string username) {
	User tempUser(username);

	std::set<User>::iterator it = users.find(tempUser);

	return it;
}

bool UserController::passwordMatchesusername(std::string password, const std::set<User>::iterator it) {

	auto hashedPassword = std::hash<std::string>{}(password);

	if ((*it).User::isHashedPasswordEqual(hashedPassword)) {
		return true;
	}

	return false;
}

bool UserController::login(std::string username, std::string password) {

	const std::set<User>::iterator it = findusername(username);

	//username doesn't exist
	if (it == UserController::users.end()) {
		return false;
		//return error_return_code
	}

	if (passwordMatchesusername(password, it)) {
		return true;
		//return success_return_code
	} else {
		return false;
		//return error_return_code
	}
}

bool UserController::createUser(std::string username, std::string password) {

	std::set<User>::iterator it = findusername(username);

	//username already exists
	if (it != UserController::users.end()) {
		return false;
		//return error_return_code
	}

	//username does not exist
	auto hashedPassword = std::hash<std::string>{}(password);
	User newUser(std::move(username), std::move(hashedPassword));
	UserController::users.insert(newUser);

	if (findusername(username) != users.end()) {
		return true;
		//return success_return_code
	} else {
		return false;
		//return error_return_code
	}
}

void UserController::loadUsers() {
	//
}

User UserController::lookUpUser(std::string username, std::string password) {
	//just a dummy user for stableness
	User tempUser(username);

	return tempUser;
}

User UserController::getUserByusername(std::string username) {
	std::set<User>::iterator it = findusername(username);

	return *it;
}
