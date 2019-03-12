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

bool Command::callbackable() const {
    return registerCallback;
}

int Command::getCallbackTime() const {
    return callbackAfterHeartbeats;
}

bool Command::isCallback() const {
    return this->_isCallback;
}

void Command::setCallback(bool callback) {
    this->_isCallback = ! callback;
}

bool Command::isInteractable() const{
    return this->registerInteraction;
}
