#ifndef ALTERSPACE_GAMECOMMANDS_H
#define ALTERSPACE_GAMECOMMANDS_H

#include <AlterSpace.h>
#include <Command.h>
#include <CommandHandler.h>

#include <RoomController.h>

#include <memory>
#include <string>
#include <Server.h>

using AlterSpace::Name;
using AlterSpace::Input;

using networking::Connection;

class Say : public Command
{
private:
    RoomController* roomController;
    Name username;
    Input input;
    std::vector<std::string> interactions;
    void setInteractions(std::vector<std::string> i);
public:
    explicit
    Say(CharacterController* characterController, RoomController* roomController, Name username = "", Input input = "", Connection connection = Connection{})
        : roomController(roomController), username(std::move(username)), input(std::move(input)) {
            this->characterController = characterController;
           };

    ~Say() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

class Swap : public Command
{
private:
    Name username;
    Input target;
    std::vector<std::string> interactions;
    void setInteractions(std::vector<std::string> i);
public:
    explicit
    Swap(CharacterController* characterController, Name username = "", Input target = "", Connection connection = Connection{})
        : username(std::move(username)), target(std::move(target)) {
            this->characterController = characterController;
            registerInteraction = true;
            registerCallback = true;
            callbackAfterHeartbeats = 300;
           };

    ~Swap() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> callback() override;
    // std::pair<std::vector<Response>, bool> interact();
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input target, Connection connection) const override;
    std::string help() override;
};

class Help : public Command
{
private:
    CommandHandler* commandHandler;
    Name username;
    Input input;
public:
    explicit
    Help(CharacterController* characterController, CommandHandler* commandHandler, Name username = "", Input input = "", Connection connection = Connection{})
        : commandHandler(commandHandler), username(std::move(username)), input(std::move(input)) {
            this->characterController = characterController;
           };

    ~Help() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};


#endif //ALTERSPACE_GAMECOMMANDS_H
