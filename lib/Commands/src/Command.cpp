#include <Command.h>
#include <iostream>
#include <stdexcept>

std::vector<Response> noResponse() {
    return std::vector<Response>{};
}

std::pair<std::vector<Response>, bool> Command::execute() {
    throw std::runtime_error("No execute... Did you implement one...?");
    return std::make_pair(noResponse(), false);
}

std::string Command::help() {
    throw std::runtime_error("No help implemented...");
    return "";
}

std::pair<std::vector<Response>, bool> Command::callback() {
    std::cout << "No callback... Did you implement one...?" << std::endl;
    return std::make_pair(noResponse(), false);
}

std::pair<std::vector<Response>, bool> Command::interact() {
    std::cout << "Using base interact..." << std::endl;
    return std::make_pair(noResponse(), false);
}

bool Command::hasCallback() const {
    return registerCallback;
}

int Command::getCallbackTime() const {
    return callbackAfterHeartbeats;
}

bool Command::runCallback() const {
    return ! this->ranCallback;
}

void Command::setCallback(bool callback) {
    this->ranCallback = callback;
}

bool Command::isInteractable() const{
    return this->registerInteraction;
}
