#include <UserCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>
#include <ReturnCodes.h>
#include <Server.h>
#include <JSONThingy.h>

using networking::Connection;

//Login
std::pair<std::vector<Response>, bool> Login::execute() {
    auto result = userController->login(username, input, connection);

    if(result.returnCode == ReturnCode::LOGIN_SUCCESS) {
        Character tmpChar;
        JSONThingy jt;
        jt.load(username, tmpChar);
        characterController->addCharacter(tmpChar);
        objectController->addObjectsToList(tmpChar.getInventory().getObjects());

        roomController->addCharacterToRoom(tmpChar.getName(), tmpChar.getRoomID());
    }



    std::string returnMessage = Return::ReturnCodeToString(result.returnCode);
    std::vector<Response> res;
    res.emplace_back(returnMessage, username, connection);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Login::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<Login>(this->userController, this->characterController, this->roomController, this->objectController, username, input, connection);
}

std::unique_ptr<Command> Login::clone() const {
    return std::make_unique<Login>(this->userController, this->characterController, this->roomController, this->objectController, this->username, this->input, this->connection);
}

std::string Login::help() {
    return "/login [username] [password] - login as user with password";
}

//Logout
std::pair<std::vector<Response>, bool> Logout::execute() {

    std::vector<Response> res;
    auto currentUsername = characterController->getUsernameOfCharacter(username);
    if(currentUsername != username) {
        res.emplace_back("User is currently swapped", username, connection);
        return std::make_pair(res, false);
    }
    auto result = userController->logoutUser(username);
    if(result.returnCode == ReturnCode::LOGOUT_SUCCESS) {
        JSONThingy jt;
        jt.save(characterController->getCharacter(username));
        auto roomID = characterController->getCharacterRoomID(username);
        characterController->removeCharacter(username);
        roomController->removeCharacterFromRoom(username, roomID);
    }
    std::string returnMessage = Return::ReturnCodeToString(result.returnCode);

    res.emplace_back(returnMessage, username, connection);
    return std::make_pair(res, result.returnCode == ReturnCode::LOGOUT_SUCCESS);
}

std::unique_ptr<Command> Logout::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<Logout>(this->userController, this->characterController, this->roomController, username, input, connection);
}

std::unique_ptr<Command> Logout::clone() const {
    return std::make_unique<Logout>(this->userController, this->characterController, this->roomController, this->username, this->input, this->connection);
}

std::string Logout::help() {
    return "/logout - logout user";
}

//_ForcedLogout - DO NOT REGISTER
std::pair<std::vector<Response>, bool> _ForcedLogout::execute() {
    auto res = _logout->execute();
    res.second = ! res.second;
    return res;
}

std::pair<std::vector<Response>, bool> _ForcedLogout::callback() {
    auto res = _logout->execute();
    if(! res.second) {
        this->registerCallback = true;
    }
    return res;
}

std::unique_ptr<Command> _ForcedLogout::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<_ForcedLogout>(this->userController, this->characterController, this->roomController, username, input, connection);
}

std::unique_ptr<Command> _ForcedLogout::clone() const {
    return std::make_unique<_ForcedLogout>(this->userController, this->characterController, this->roomController, this->username, this->input, this->connection);
}

std::string _ForcedLogout::help() {
    return "You really shouldn't see this...";
}

//Signup
std::pair<std::vector<Response>, bool> Signup::execute() {

    auto result = userController->createUser(username, input, connection);

    if(result.returnCode == ReturnCode::CREATE_SUCCESS) {

        characterController->addCharacter(username, *(roomController), *(objectController));
        JSONThingy jt;
        std::cout << characterController->getCharacter(username).getName() << std::endl;
        jt.save(characterController->getCharacter(username));
    }

    std::string returnMessage = Return::ReturnCodeToString(result.returnCode);

    std::vector<Response> res;
    res.emplace_back(returnMessage, username, connection);

    return std::make_pair(res, true);
}

std::unique_ptr<Command> Signup::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<Signup>(this->userController, this->characterController, this->roomController, this->objectController, username, input, connection);
}

std::unique_ptr<Command> Signup::clone() const {
    return std::make_unique<Signup>(this->userController, this->characterController, this->roomController, this->objectController, this->username, this->input, this->connection);
}

std::string Signup::help() {
    return "/signup [username] [password] - signup as user with password";
}