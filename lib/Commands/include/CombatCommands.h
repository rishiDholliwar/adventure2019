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
bool isTargetInRoom(RoomController *rc, Character &instigator, Name target);

//removes all extra whitespaces to correct user errors when typing
void removeExtraWhiteSpaces(Input &input); //todo put in utility
std::string toMSG(const Name &name); //todo put in utility
std::string fromMSG(const Name &name); //todo put in utility

class CombatExamine : public Command
{
private:
    UserController* userController;
    RoomController* roomController;
    ObjectController* objectController;
    CombatController* combatController;
    Name username;
    Input input;
    Connection connection;

public:
    explicit
    CombatExamine(UserController* userController, CharacterController* characterController, RoomController* roomController, ObjectController* objectController, CombatController* combatController ,
                  Name username = "", Input input = "", Connection connection = Connection{})
            : userController(userController), roomController(roomController), objectController(objectController), combatController(combatController),
              username(std::move(username)), input(std::move(input)), connection(connection) {
        this->characterController = characterController;
    };

    ~CombatExamine() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

class CombatAttack : public Command
{
private:
    UserController* userController;
    RoomController* roomController;
    ObjectController* objectController;
    CombatController* combatController;
    Name username;
    Input input;
    Connection connection;

public:
    explicit
    CombatAttack(UserController* userController, CharacterController* characterController, RoomController* roomController, ObjectController* objectController, CombatController* combatController ,
                 Name username = "", Input input = "", Connection connection = Connection{})
            : userController(userController), roomController(roomController), objectController(objectController), combatController(combatController),
              username(std::move(username)), input(std::move(input)), connection(connection) {
        this->characterController = characterController;
    };

    ~CombatAttack() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

class CombatBattles : public Command
{
private:
    UserController* userController;
    RoomController* roomController;
    ObjectController* objectController;
    CombatController* combatController;
    Name username;
    Input input;
    Connection connection;

public:
    explicit
    CombatBattles(UserController* userController, CharacterController* characterController, RoomController* roomController, ObjectController* objectController, CombatController* combatController ,
                  Name username = "", Input input = "", Connection connection = Connection{})
            : userController(userController), roomController(roomController), objectController(objectController), combatController(combatController),
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
