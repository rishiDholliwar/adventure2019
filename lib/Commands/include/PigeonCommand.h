#ifndef ALTERSPACE_PIGEONCOMMAND_H
#define ALTERSPACE_PIGEONCOMMAND_H

#include <AlterSpace.h>
#include <Command.h>

#include <RoomController.h>
#include <PigeonEXE.h>

#include <memory>
#include <string>
#include <Server.h>

using AlterSpace::Name;
using AlterSpace::Input;

using networking::Connection;

// PigeonMail
class PigeonMail : public Command
{
private:
    const unsigned int INTERACT_CHOICE = 1;

    RoomController* roomController;
    PigeonEXE* pigeonEXE;
    Name username;
    Input input;
    Name targetUsername;
    Name pigeonUsername;
    Name pigeonName;
    ID itemUniqueID;
    ID objectID;
    std::vector<std::pair<Name, Object>> interactions;

    void setInteractions(std::vector<std::pair<Name, Object>> i);

public:
    explicit
    PigeonMail(CharacterController* characterController, RoomController* roomController, PigeonEXE* pigeonEXE, Name username = "", Input input = "", Connection connection = Connection{})
        : roomController(roomController), pigeonEXE(pigeonEXE), username(std::move(username)), input(std::move(input)) {
            this->characterController = characterController;
            registerInteraction = true;
            registerCallback = true;
            callbackAfterHeartbeats = 25;
           };

    ~PigeonMail() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> callback() override;
    std::pair<std::vector<Response>, bool> interact();
    void releaseThePigeon();
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};


#endif //ALTERSPACE_PIGEONCOMMAND_H
