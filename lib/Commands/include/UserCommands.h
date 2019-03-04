#ifndef ALTERSPACE_USERCOMMANDS_H
#define ALTERSPACE_USERCOMMANDS_H

#include <AlterSpace.h>
#include <Command.h>
#include <UserController.h>
#include <GameController.h>

#include <memory>
#include <string>

using AlterSpace::Name;
using AlterSpace::Input;

class Login : public Command
{
private:
    UserController* userController;
    GameController* gameController;
    Name username;
    Input input;
    Connection connection;
public:
    Login(UserController* userController, GameController* gameController,
            Name username = "", Input input = "", Connection connection = Connection{})
        : userController(userController), gameController(gameController),
            username(username), input(input), connection(connection) {};

    ~Login() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

#endif //ALTERSPACE_USERCOMMANDS_H