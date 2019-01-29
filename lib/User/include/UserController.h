
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <map>
#include <vector>
#include <User.h>

class UserController {

public:

	struct ReturnType {
		std::string username;
		ReturnCode returnCode;
		std::vector<std::string> characterData;
	};

	std::map<std::string, std::string> getActiveUsers();

	void addActiveUser(std::string username, std::string connectionId);

	bool isThisUserActive(std::string username);

	std::string getUsernameWithConnectionId(std::string connectionId);

	std::string getConnectionIdWithUsername(std::string username);

	auto hashPassword(std::string password);

	ReturnType login(std::string username, std::string password, std::string connectionId);

	ReturnCode parseLoginUserData(std::string username, std::string password);

	std::vector<std::string> parseLoginCharacterData(std::string username);

	ReturnType createUser(std::string username, std::string password);

	ReturnCode parseNewUserData(std::string username, std::string password);

	ReturnType logoutUser(std::string username, std::vector<std::string> newCharData);

	ReturnCode saveCharacterDataBeforeLogout(std::string username, std::vector<std::string> newCharData);

private:
	std::map<std::string, std::string> activeUsers = {};
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
