#ifndef ALTERSPACE_COMBATCOMMANDS_H
#define ALTERSPACE_COMBATCOMMANDS_H

#include <AlterSpace.h>
#include <Command.h>
#include <UserController.h>
#include <RoomController.h>
#include <ObjectController.h>
#include <CombatController.h>

using AlterSpace::Name;
using AlterSpace::Input;

//Helper functions:
void getCharactersInCurrentRoom(RoomController *roomCtrl, CharacterController *characterCtrl, Character player,
                                std::vector<Character> &charactersInRoom);

void removeExtraWhiteSpaces(Input &input); //removes all extra whitespaces to correct user errors when typing
std::string toMSG(const Name &name);

std::string fromMSG(const Name &name);

class CombatExamine : public Command {
private:
    RoomController *roomController;
    CombatController *combatController;
    Name username;
    Input input;
    Connection connection;

public:
    explicit
    CombatExamine(CharacterController *characterController, RoomController *roomController,
                  CombatController *combatController,
                  Name username = "", Input input = "", Connection connection = Connection{})
            : roomController(roomController), combatController(combatController),
              username(std::move(username)), input(std::move(input)), connection(connection) {
        this->characterController = characterController;
    };

    ~CombatExamine() = default;

    std::pair<std::vector<Response>, bool> execute() override;

    std::unique_ptr<Command> clone() const override;

    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;

    std::string help() override;
};

class CombatAttack : public Command {
private:
    RoomController *roomController;
    CombatController *combatController;
    Name username;
    Input input;
    Connection connection;

public:
    explicit
    CombatAttack(CharacterController *characterController, RoomController *roomController,
                 CombatController *combatController,
                 Name username = "", Input input = "", Connection connection = Connection{})
            : roomController(roomController), combatController(combatController),
              username(std::move(username)), input(std::move(input)), connection(connection) {
        this->characterController = characterController;
    };

    ~CombatAttack() = default;

    std::pair<std::vector<Response>, bool> execute() override;

    std::unique_ptr<Command> clone() const override;

    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;

    std::string help() override;
};

class CombatBattles : public Command {
private:
    RoomController *roomController;
    CombatController *combatController;
    Name username;
    Input input;
    Connection connection;

public:
    explicit
    CombatBattles(CharacterController *characterController, RoomController *roomController,
                  CombatController *combatController,
                  Name username = "", Input input = "", Connection connection = Connection{})
            : roomController(roomController), combatController(combatController),
              username(std::move(username)), input(std::move(input)), connection(connection) {
        this->characterController = characterController;
    };

    ~CombatBattles() = default;

    std::pair<std::vector<Response>, bool> execute() override;

    std::unique_ptr<Command> clone() const override;

    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;

    std::string help() override;
};

#endif //ALTERSPACE_COMBATCOMMANDS_H