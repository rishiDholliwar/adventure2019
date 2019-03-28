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

std::pair<std::vector<Response>, bool> Command::runCallback() {
    registerCallback = false;
    return this->callback();
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

std::vector<Response> Command::formulateResponse(Response &userResponse, std::vector<Name> characterList, Input message) {
    std::vector<Response> response;

    for(auto &character : characterList){
        if(character == userResponse.username || ! characterController->doesCharacterExist(character)){
            continue;
        }
        if(characterController->isCharacterConfused(character)) {
            response.emplace_back(translate(message), character);
        } else {
            response.emplace_back(message, character);
        }
    }

    if(!userResponse.username.empty() && characterController->isCharacterConfused(userResponse.username)){
        userResponse.message = translate(userResponse.message);
        response.push_back(userResponse);
    } else {
        response.push_back(userResponse);
    }

    return response;
}

std::vector<Response> Command::formulateResponse(Response &userResponse, Response &targetResponse) {
    std::vector<Response> response;

    response.push_back(userResponse);
    response.push_back(targetResponse);

    return response;
}

std::vector<Response> Command::formulateResponse(Response &userResponse) {
    return formulateResponse(userResponse, std::vector<std::string>{}, std::string{});
}