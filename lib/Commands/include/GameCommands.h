#ifndef ALTERSPACE_GAMECOMMANDS_H
#define ALTERSPACE_GAMECOMMANDS_H

#include <AlterSpace.h>
#include <Command.h>

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

// tell
class Tell : public Command
{
private:
    const unsigned int TARGET_CHARACTER_NAME = 0;
    const unsigned int MESSAGE = 1;

    Name username;
    Input target;
public:
    explicit
    Tell(CharacterController* characterController, Name username = "", Input target = "", Connection connection = Connection{})
            : username(std::move(username)), target(std::move(target)) {
        this->characterController = characterController;
    };

    ~Tell() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

// whisper
class Whisper : public Command
{
private:
    const unsigned int TARGET_CHARACTER_NAME = 0;
    const unsigned int MESSAGE = 1;

    RoomController* roomController;
    Name username;
    Input input;
public:
    explicit
    Whisper(CharacterController* characterController, RoomController* roomController, Name username = "", Input input = "", Connection connection = Connection{})
            : roomController(roomController) ,username(std::move(username)), input(std::move(input)) {
        this->characterController = characterController;
    };

    ~Whisper() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;

    void removeTargets(std::vector<std::string> &characterList, Name username, Name targetName);
};

// confuse
class Confuse : public Command
{
private:
    RoomController* roomController;
    Name username;
    Input target;
public:
    explicit
    Confuse(CharacterController* characterController, RoomController* roomController, Name username = "", Input target = "", Connection connection = Connection{})
            : roomController(roomController), username(std::move(username)), target(std::move(target)) {
        this->characterController = characterController;
        registerInteraction = true;
        registerCallback = true;
        callbackAfterHeartbeats = 300;
    };

    ~Confuse() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> callback() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input target, Connection connection) const override;
    std::string help() override;
};

// swap
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




#endif //ALTERSPACE_GAMECOMMANDS_H