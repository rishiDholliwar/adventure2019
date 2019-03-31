#ifndef ALTERSPACE_MINIGAMECOMMANDS_H
#define ALTERSPACE_MINIGAMECOMMANDS_H
#include <AlterSpace.h>
#include <Command.h>
#include <MiniGameController.h>

using AlterSpace::Name;
using AlterSpace::Input;

class tttBrowser : public Command {
private:
    MiniGameController *miniGameController;
    Name username;
    Input input;
    Connection connection;

public:
    explicit
    tttBrowser(CharacterController *characterController, MiniGameController *miniGameController,
               Name username = "", Input input = "", Connection connection = Connection{})
            : miniGameController(miniGameController),
              username(std::move(username)), input(std::move(input)), connection(connection) {
        this->characterController = characterController;

    };

    ~tttBrowser() = default;

    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

class tttTerminal : public Command {
private:
    MiniGameController *miniGameController;
    Name username;
    Input input;
    Connection connection;

public:
    explicit
    tttTerminal(CharacterController *characterController, MiniGameController *miniGameController,
                Name username = "", Input input = "", Connection connection = Connection{})
            : miniGameController(miniGameController),
              username(std::move(username)), input(std::move(input)), connection(connection) {
        this->characterController = characterController;
    };

    ~tttTerminal() = default;

    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

#endif //ALTERSPACE_MINIGAMECOMMANDS_H
