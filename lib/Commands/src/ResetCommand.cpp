#include <ResetCommand.h>
//ResetCommand - DO NOT REGISTER
std::pair<std::vector<Response>, bool> ResetCommand::execute() {
    resetController->reset();
    std::vector<Response> v;
    return make_pair(v, true);
}

std::pair<std::vector<Response>, bool> ResetCommand::callback() {
    auto res = this->execute();
    this->registerCallback = true;
    return std::make_pair(res.first, false);
}

std::unique_ptr<Command> ResetCommand::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<ResetCommand>(this->resetController, this->callbackAfterHeartbeats);
}

std::unique_ptr<Command> ResetCommand::clone() const {
    return std::make_unique<ResetCommand>(this->resetController, this->callbackAfterHeartbeats);
}

std::string ResetCommand::help() {
    return "You really shouldn't see this...";
}
