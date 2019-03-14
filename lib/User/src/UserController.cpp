#include <UserController.h>
#include <User.h>
#include <JSONUser.h>

std::unordered_map<Name, Connection> UserController::getActiveUsers() {
    return activeUsers;
}

void UserController::addActiveUser(const Name username, Connection connection) {
    activeUsers.insert(std::pair<std::string, Connection>(std::move(username), connection));
}

bool UserController::isUserActive(const Name& username) {

    return activeUsers.find(username) != activeUsers.end();
}

auto UserController::getIteratorWithConnection(const Connection connection) {

    auto itrToUsername = find_if(activeUsers.begin(), activeUsers.end(),
                                 [&connection](const std::pair<std::string, Connection> &userConnection) {
                                     return userConnection.second == connection;
                                 });

    return itrToUsername;
}

bool UserController::isConnectionLoggedIn(const Connection connection) {

    return (getIteratorWithConnection(connection) != activeUsers.end());
}

std::string UserController::getUsernameWithConnection(const Connection connection) {

    if (isConnectionLoggedIn(connection) == false) {
        return std::string();
    }

    auto itrToUsername = getIteratorWithConnection(connection);


    return itrToUsername->first;

}

Connection UserController::getConnectionWithUsername(const Name &username) {

    auto userItr = activeUsers.find(username);

    if (userItr != activeUsers.end()) {
        return userItr->second;

    }

    //chatserver.cpp checks for whether or not connection is logged in before calling this function
    //...so this return statement should never be needed.
    return Connection{};
}

std::size_t UserController::hashPassword(Password password) {

    auto hashedPassword = std::hash<std::string>{}(password);

    return hashedPassword;
}

UserController::UserData UserController::login(const Name &username, Password password, const Connection connection) {

    UserData result;
    result.username = username;

    result.returnCode = validateLoginUserData(username, password);

    std::cout << "UserController::login, username is : " << username << std::endl;
    std::cout << "UserController::login, connection id is : " << connection.id << std::endl; 

    if (result.returnCode == ReturnCode::LOGIN_SUCCESS) {
        addActiveUser(username, connection);
    }

    return result;
}

ReturnCode UserController::validateLoginUserData(const Name username, Password password) {

    //check if user is already logged in:
    if (isUserActive(username)) {

        return ReturnCode::USER_ACTIVE;
    }

	   auto hashedPassword = hashPassword(password);

    //if username.json doesn't exist, ReturnCode::USERNAME_FAIL
    if (!JSONUser::doesFileExist(username)) {
        return ReturnCode::USERNAME_FAIL;
    }
    // Check if hashedPassword matches hashedPassword in username.json
    // If true, ReturnCode::LOGIN_SUCCESS, else ReturnCode::PASSWORD_FAIL

    if (JSONUser::getUser(username).getHashedPassword() != hashedPassword) {
        return ReturnCode::PASSWORD_FAIL;
    }

    return ReturnCode::LOGIN_SUCCESS;
}

UserController::UserData
UserController::createUser(const Name &username, Password password, const Connection connection) {

    UserData result;
    result.username = username;

    result.returnCode = validateNewUserData(username, password);

    if (result.returnCode == ReturnCode::CREATE_SUCCESS) {
        login(username, password, connection);
    }

    return result;
}

ReturnCode UserController::validateNewUserData(const Name username, Password password) {

    //check if user is already logged in:
    if (isUserActive(username)) {

        return ReturnCode::USER_ACTIVE;
    }

    //make sure no .json file exists with that username.
    //if such file already exists, return ReturnCode::USERNAME_EXISTS
    if (JSONUser::doesFileExist(username)) {
        return ReturnCode::USERNAME_EXISTS;
    }

    //if no file already exists, hash password.
    auto hashedPassword = hashPassword(password);

    //create username.json file, read in username and hashed password
    JSONUser::createNewUser(username, hashedPassword);

    return ReturnCode::CREATE_SUCCESS;
}

UserController::UserData UserController::logoutUser(const Name &username) {

    UserData result;
    result.username = username;

    if (activeUsers.erase(username) != 1) {
        result.returnCode = ReturnCode::LOGOUT_FAIL;
        return result;
    }

    result.returnCode = ReturnCode::LOGOUT_SUCCESS;

    return result;
}

UserController::UserData
UserController::logoutUser(const Name &username, Password password, const Connection connection) {
    return logoutUser(username);
}
