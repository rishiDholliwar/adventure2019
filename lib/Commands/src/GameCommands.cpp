#include <GameCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>

std::pair<std::vector<Response>, bool> Say::execute() {
    if (interactions.size() > 1 && interactions.at(0) == "interact") {
        return this->interact();
    }
    interactions = utility::tokenizeString(input);
    std::stringstream ss;
    ss << "Possible interactions:\n";
    int counter = 0;
    for ( auto& word : interactions ) {
        ss << "\t" << ++counter << ". " << word << "\n";
    }
    auto res = gameController->say(username, input);
    // res.emplace_back(ss.str(), username);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Say::callback() {
    std::string callbackString = "Callback: " + input;
    return std::make_pair(gameController->say(username, callbackString), true);
}

std::pair<std::vector<Response>, bool> Say::interact() {
    std::vector<std::string> v = utility::tokenizeString(input);
    if ( v.size() != 2 ) {
        std::cout << "Too many arguments..." << std::endl;
        return std::make_pair(gameController->say(username, input), false);
    }
    std::cout << v.at(0) << std::endl;
    std::cout << v.at(1) << std::endl;
    std::stringstream ss{v.at(1)};
    int index = -1;
    ss >> index;
    index--;
    if ( index > interactions.size() || index < 0 ) {
        std::cout << "Invalid argument..." << index << std::endl;
        return std::make_pair(gameController->say(username, input), false);
    }

    return std::make_pair(gameController->say(username, "interaction: " + interactions[index]), true);
}

std::unique_ptr<Command> Say::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto say = std::make_unique<Say>(this->gameController, username, input);
    say->setInteractions(this->interactions);
    say->setCallback(this->ranCallback);
    return std::move(say);
}

std::unique_ptr<Command> Say::clone() const {
    auto say = std::make_unique<Say>(this->gameController, this->username, this->input);
    say->setInteractions(this->interactions);
    say->setCallback(this->ranCallback);
    return std::move(say);
}

std::string Say::help() {
    return "/say [message] - sends message to other players in the room";
}

void Say::setInteractions(std::vector<std::string> i) {
    interactions = i;
}
