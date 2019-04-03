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
void removeExtraWhiteSpaces(Input &input); //removes all extra whitespaces to correct user errors when typing
std::string toMSG(const Name &name);
std::string fromMSG(const Name &name);
void removeTargets(std::vector<std::string> &characterList, Name username);

class CombatExamine : public Command {
private:
    const unsigned int CHECK_INTERACT = 0;
    const unsigned int INTERACT_CHOICE = 1;
    RoomController *roomController;
    CombatController *combatController;
    Name username;
    Input target;
    Connection connection;
     std::vector<std::string> interactions;
    void setInteractions(std::vector<std::string> i);
public:
    explicit
    CombatExamine(CharacterController *characterController, RoomController *roomController,
                  CombatController *combatController,
                  Name username = "", Input target = "", Connection connection = Connection{})
            : roomController(roomController), combatController(combatController),
              username(std::move(username)), target(std::move(target)), connection(connection) {
        this->characterController = characterController;
    };

    ~CombatExamine() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> interact();
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input target, Connection connection) const override;
    std::string help() override;
};

class CombatAttack: public Command {
private:
    const unsigned int CHECK_INTERACT = 0;
    const unsigned int INTERACT_CHOICE = 1;
    const int ROUND_DURATION = 20;

    RoomController *roomController;
    CombatController *combatController;
    Name username;
    Input targetInput;
    Connection connection;
     std::vector<std::string> interactions;
     Name npcAttack;
     //Character npc;
    void setInteractions(std::vector<std::string> i,Name npcAttack);

public:
    explicit
    CombatAttack(CharacterController *characterController, RoomController *roomController,
                      CombatController *combatController,
                      Name username = "", Input input = "", Connection connection = Connection{})
            : roomController(roomController), combatController(combatController),
              username(std::move(username)), targetInput(std::move(input)), connection(connection) {
        this->characterController = characterController;
          registerInteraction = true;
    };

    ~CombatAttack() = default;
    std::pair<std::vector<Response>, bool> execute() override;
     std::pair<std::vector<Response>, bool> interact();
    std::pair<std::vector<Response>, bool> callback() override;
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


class CombatFlee : public Command {
private:
    RoomController *roomController;
    CombatController *combatController;
    Name username;
    Input input;

    Connection connection;

public:
    explicit
    CombatFlee(CharacterController *characterController, RoomController *roomController,
                  CombatController *combatController,
                  Name username = "", Input input = "", Connection connection = Connection{})
            : roomController(roomController), combatController(combatController),
              username(std::move(username)), input(std::move(input)), connection(connection) {
        this->characterController = characterController;
    };

    ~CombatFlee() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};
#endif //ALTERSPACE_COMBATCOMMANDS_H
