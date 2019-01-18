#include "../include/UserManager.h"

User UserManager::findUser(std::string userName, std::string hashedPassword) {
    if(userName == "a"){
        User a{networking::Connection{2}, "a", "b"};
        a.moveToRoom(5);
        return a;
    }
    return User{networking::Connection{1}, "b", "b"};
}

bool UserManager::userExists(std::string username, std::string password) {

	std::set<User>::iterator it = users.find(username);

	if (it != users.end()) {

		auto hashedPassword = std::hash<std::string>{}(password);

		if (*it.isHashedPasswordEqual(hashedPassword)) {
			return true;
		}
	}
	return false;
}

void UserManager::tryLoginAgain() {
	// Output to screen
}

void UserManager::login(std::string username, std::string password) {

	if (userExists(username, password)) {

		startSession();
	} else {
		tryLoginAgain();
	}
}

void UserManager::loadUsers() {

}
