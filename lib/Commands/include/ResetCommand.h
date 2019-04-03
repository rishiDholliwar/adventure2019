#ifndef ALTERSPACE_RESETCOMMAND_H
#define ALTERSPACE_RESETCOMMAND_H

#include <Command.h>
#include <ResetController.h>

//Reset - Do not register
class ResetCommand : public Command
{
private:
    ResetController* resetController;
public:
    explicit
    ResetCommand(ResetController* resetController, int heartbeat)
        : resetController(resetController) {
                registerCallback = true;
                callbackAfterHeartbeats = heartbeat;
            };

    ~ResetCommand() = default;
    std::pair<std::vector<Response>, bool> execute() override;
    std::pair<std::vector<Response>, bool> callback() override;
    std::unique_ptr<Command> clone() const override;
    std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const override;
    std::string help() override;
};

#endif //ALTERSPACE_RESETCOMMAND_H
