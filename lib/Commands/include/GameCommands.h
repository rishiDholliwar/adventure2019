#ifndef ALTERSPACE_GAMECOMMANDS_H
#define ALTERSPACE_GAMECOMMANDS_H

#include <AlterSpace.h>
#include <Command.h>
#include <GameController.h>

#include <memory>
#include <string>
#include <Server.h>

using AlterSpace::Name;
using AlterSpace::Input;

using networking::Connection;

class Say : public Command
{
private:
    GameController* gameController;
    Name username;
    Input input;
    std::vector<std::string> interactions;
    void setInteractions(std::vector<std::string> i);
public:
    Say(GameController* gameController, Name username = "", Input input = "", Connection connection = Connection{})
        : gameController(gameController), username(username), input(input) {
            registerInteraction = true;
            registerCallback = true;
            callbackAfterHeartbeats = 10;
           };

    ~Say() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> callback() override;
    std::pair<std::vector<Response>, bool> interact() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

#endif //ALTERSPACE_GAMECOMMANDS_H