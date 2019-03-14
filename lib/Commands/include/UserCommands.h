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