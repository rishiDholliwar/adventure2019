
#ifndef WEBSOCKETNETWORKING_USERMANAGER_H
#define WEBSOCKETNETWORKING_USERMANAGER_H


#include <string>
#include <map>
#include <vector>
#include <User.h>

class UserController {

public:
	std::map<std::string, std::string> getActiveUsers();

	void addActiveUser(std::string username, std::string connectionId);

	bool isThisUserActive(std::string username);

	std::string getUsernameWithConnectionId(std::string connectionId);

	std::string getConnectionIdWithUsername(std::string username);

	auto hashPassword(std::string password);

	bool login(std::string username, std::string password, std::string connectionId);

	bool parseLoginUserData(std::string username, std::string password);

	std::vector<std::string> parseLoginCharacterData(std::string username);

	bool createUser(std::string username, std::string password);

	bool parseNewUserData(std::string username, std::string password);

	bool logoutUser(std::string username, std::vector<std::string> newCharData);

	bool saveCharacterDataBeforeLogout(std::string username, std::vector<std::string> newCharData);

private:
	std::map<std::string, std::string> activeUsers = {};

	struct returnType {
		std::string username;
		//enum class error code. for testing purpose only, using bool rn.
		bool returnCode;
		std::vector<std::string> characterData;
	};
};


#endif //WEBSOCKETNETWORKING_USERMANAGER_H
