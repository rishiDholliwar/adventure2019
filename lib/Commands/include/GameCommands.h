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

// say
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

// inventory
class DisplayInventory : public Command
{
private:
    Name username;
    Input input;
public:
    explicit
    DisplayInventory(CharacterController* characterController, Name username = "", Input input = "", Connection connection = Connection{})
            : username(std::move(username)), input(std::move(input)) {
        this->characterController = characterController;
    };

    ~DisplayInventory() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

// give
class Give : public Command
{
private:
    const unsigned int TARGET_CHARACTER_NAME = 0;
    const unsigned int GIFT_NAME = 1;

    const unsigned int CHECK_INTERACT = 0;
    const unsigned int MULTIPLE_ITEMS = 1;

    const unsigned int INTERACT_CHOICE = 1;

    Name username;
    Input input;
    RoomController* roomController;
    ObjectController* objectController;
    std::vector<ID> interactionsCharacters;
    std::vector<Object> interactionsGifts;

    // int interactItemChoice;
    ID interactCharacterTargetID;
    Name interactGiftTarget;

    void setInteractions(std::vector<ID> iC, std::vector<Object> iG, ID interactC, Name interactG);
public:
    explicit
    Give(CharacterController* characterController, RoomController* roomController, ObjectController* objectController, Name username = "", Input input = "", Connection connection = Connection{})
            : roomController(roomController), objectController(objectController), username(std::move(username)), input(std::move(input)) {
        this->characterController = characterController;
        registerInteraction = true;
    };

    ~Give() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> interact();
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
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
    const unsigned int CHECK_INTERACT = 0;
    const unsigned int INTERACT_CHOICE = 1;

    const unsigned int TARGET_CHARACTER_NAME = 0;

    RoomController* roomController;

    Name username;
    Input target;
    void setInteractions(std::vector<std::string> i);

    std::vector<Name> interactions;

    Name originalUsername;
    Name originalTargetUsername;

    Name swappedCharacterName;
    Name swappedTargetCharacterName;

public:
    explicit
    Swap(CharacterController* characterController, RoomController* roomController, Name username = "", Input target = "", Connection connection = Connection{})
            : roomController(roomController), username(std::move(username)), target(std::move(target)) {
        this->characterController = characterController;
        registerInteraction = true;
        registerCallback = true;
        callbackAfterHeartbeats = 150;
    };

    ~Swap() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> callback() override;
    std::pair<std::vector<Response>, bool> interact();
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input target, Connection connection) const override;
    std::string help() override;
};


//look
class Look : public Command
{
private:
    const unsigned int CHECK_INTERACT = 0;
    const unsigned int INTERACT_TARGET = 1;

    RoomController* roomController;
    ObjectController* objectController;
    Name username;
    Input target;
    std::vector<std::string> interactions;
    const std::string line = "---------------------------\n";


    void setInteractions(std::vector<std::string> i);
public:
    explicit
    Look(CharacterController* characterController, RoomController* roomController, ObjectController* objectController,
         Name username = "", Input target = "", Connection connection = Connection{})
            : roomController(roomController), username(std::move(username)), target(std::move(target)) {
        this->characterController = characterController;
        this->objectController = objectController;
        registerInteraction = true;
    };

    ~Look() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> interact();
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input target, Connection connection) const override;
    std::string help() override;
};

//examine
class Examine : public Command
{
private:
    const unsigned int CHECK_INTERACT = 0;
    const unsigned int INTERACT_TARGET = 1;

    RoomController* roomController;
    ObjectController* objectController;
    Name username;
    Input target;
    std::string line = "---------------------------\n";
    std::vector<std::string> interactions;

    void setInteractions(std::vector<std::string> i);
public:
    explicit
    Examine(CharacterController* characterController, RoomController* roomController, ObjectController* objectController,
            Name username = "", Input target = "", Connection connection = Connection{})
            : roomController(roomController), username(std::move(username)), target(std::move(target)) {
        this->characterController = characterController;
        this->objectController = objectController;
        registerInteraction = true;
    };

    ~Examine() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> interact();
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

//move
class Move : public Command
{
private:
    Name username;
    Input direction;
    std::vector<std::string> interactions;
    RoomController* roomController;
public:
    explicit
    Move(CharacterController* characterController,RoomController* roomController, Name username = "", Input direction = "", Connection connection = Connection{})
            : username(std::move(username)), direction(std::move(direction)) {
        this->characterController = characterController;
        this->roomController = roomController;;
    };

    ~Move() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input target, Connection connection) const override;
    std::string help() override;

    void removeTargets(std::vector<std::string> &characterList, Name username);
};

// Info
class Info : public Command
{
private:
    Name username;
    Input input;
public:
    explicit
    Info(CharacterController* characterController, Name username = "", Input input = "", Connection connection = Connection{})
        : username(std::move(username)), input(std::move(input)) {
            this->characterController = characterController;
           };

    ~Info() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

// Wear
class Wear : public Command
{
private:
    const unsigned int CHECK_INTERACT = 0;
    const unsigned int MULTIPLE_ITEMS = 1;
    const unsigned int INTERACT_CHOICE = 1;

    Name username;
    Input input;
    std::vector<Object> interactions;
    void setInteractions(std::vector<Object> i);

public:
    explicit
    Wear(CharacterController* characterController, Name username = "", Input input = "", Connection connection = Connection{})
        : username(std::move(username)), input(std::move(input)) {
            this->characterController = characterController;
            registerInteraction = true;
           };

    ~Wear() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> interact();
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

// Takeoff
class Takeoff : public Command
{
private:
    const unsigned int CHECK_INTERACT = 0;
    const unsigned int MULTIPLE_ITEMS = 1;
    const unsigned int INTERACT_CHOICE = 1;

    Name username;
    Input input;
    ObjectController* objectController;
    std::vector<Object> interactions;
    void setInteractions(std::vector<Object> i);

public:
    explicit
    Takeoff(CharacterController* characterController, ObjectController* objectController, Name username = "", Input input = "", Connection connection = Connection{})
        : username(std::move(username)), input(std::move(input)) {
            this->characterController = characterController;
            this->objectController = objectController;
            registerInteraction = true;
           };
    ~Takeoff() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> interact();
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};




#endif //ALTERSPACE_GAMECOMMANDS_H
