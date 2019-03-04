#include <UserCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <ReturnCodes.h>
#include <Server.h>

using networking::Connection;

std::pair<std::vector<Response>, bool> Login::execute() {
    auto result = userController->login(username, input, connection);
    if(result.returnCode == ReturnCode::LOGIN_SUCCESS) {
        gameController->loadCharacter(username);
    }
    std::string returnMessage = Return::ReturnCodeToString(result.returnCode);
    std::vector<Response> res;
    res.emplace_back(returnMessage, username);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Login::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<Login>(this->userController, this->gameController, username, input, connection);
}

std::unique_ptr<Command> Login::clone() const {
    return std::make_unique<Login>(this->userController, this->gameController, this->username, this->input, this->connection);
}

std::string Login::help() {
    return "/login [username] [password] - login as user with password";
}
