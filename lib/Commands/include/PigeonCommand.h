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
    RoomController* roomController;
    PigeonMail* pigeonMail;
    ObjectController* objectController;
    Name username;
    Input input;
    Name pigeonUsername;
public:
    explicit
    PigeonMail(CharacterController* characterController, RoomController* roomController, PigeonMail* pigeonMail, ObjectController* objectController, Name username = "", Input input = "", Connection connection = Connection{})
        : roomController(roomController), pigeonMail(pigeonMail), objectController(objectController), username(std::move(username)), input(std::move(input)) {
            this->characterController = characterController;
           };

    ~PigeonMail() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> callback() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};


#endif //ALTERSPACE_PIGEONCOMMAND_H
