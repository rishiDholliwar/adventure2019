#ifndef ALTERSPACE_USERCOMMANDS_H
#define ALTERSPACE_USERCOMMANDS_H

#include <AlterSpace.h>
#include <Command.h>
#include <UserController.h>
#include <RoomController.h>
#include <ObjectController.h>

#include <memory>
#include <string>

using AlterSpace::Name;
using AlterSpace::Input;

//Login
class Login : public Command
{
private:
    UserController* userController;
    RoomController* roomController;
    ObjectController* objectController;
    Name username;
    Input input;
    Connection connection;
public:
    explicit
    Login(UserController* userController, CharacterController* characterController, RoomController* roomController, ObjectController* objectController,
            Name username = "", Input input = "", Connection connection = Connection{})
        : userController(userController), roomController(roomController), objectController(objectController),
            username(std::move(username)), input(std::move(input)), connection(connection) {
                this->characterController = characterController;
            };

    ~Login() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

//Logout
class Logout : public Command
{
private:
    UserController* userController;
    RoomController* roomController;
    Name username;
    Input input;
    Connection connection;
public:
    explicit
    Logout(UserController* userController, CharacterController* characterController, RoomController* roomController,
            Name username = "", Input input = "", Connection connection = Connection{})
        : userController(userController), roomController(roomController),
            username(username), input(std::move(input)), connection(connection) {
                this->characterController = characterController;
            };

    ~Logout() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

//Logout
class _ForcedLogout : public Command
{
private:
    std::unique_ptr<Logout> _logout;
    UserController* userController;
    RoomController* roomController;
    Name username;
    Input input;
    Connection connection;
public:
    explicit
    _ForcedLogout(UserController* userController, CharacterController* characterController, RoomController* roomController,
            Name username = "", Input input = "", Connection connection = Connection{})
        : userController(userController), roomController(roomController),
            username(username), input(std::move(input)), connection(connection) {
                _logout = std::make_unique<Logout>(userController, characterController, roomController, username, input, connection);
                this->characterController = characterController;
                registerCallback = true;
                callbackAfterHeartbeats = 50;
            };

    ~_ForcedLogout() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> callback() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

//Signup
class Signup : public Command
{
private:
    UserController* userController;
    RoomController* roomController;
    ObjectController* objectController;
    Name username;
    Input input;
    Connection connection;
public:
    explicit
    Signup(UserController* userController, CharacterController* characterController, RoomController* roomController, ObjectController* objectController,
            Name username = "", Input input = "", Connection connection = Connection{})
        : userController(userController), roomController(roomController), objectController(objectController),
            username(std::move(username)), input(std::move(input)), connection(connection) {
                this->characterController = characterController;
            };

    ~Signup() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};
#endif //ALTERSPACE_USERCOMMANDS_H
