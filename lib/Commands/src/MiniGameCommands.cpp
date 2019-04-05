#include <MiniGameCommands.h>
#include <iostream>
#include <Server.h>

using networking::Connection;

std::pair<std::vector<Response>, bool> tttBrowser::execute() {
    Response userResponse = Response(
            miniGameController->getResults(username, input, miniGameController->Browser, miniGameController->TTT),
            username);

    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> tttBrowser::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<tttBrowser>(this->characterController, this->miniGameController, username, input,
                                        connection);
}

std::unique_ptr<Command> tttBrowser::clone() const {
    return std::make_unique<tttBrowser>(this->characterController, this->miniGameController, this->username,
                                        this->input,
                                        this->connection);
}

std::string tttBrowser::help() {
    return "/ttt - Opens tic tac toe game in browser";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<std::vector<Response>, bool> tttTerminal::execute() {
    Response userResponse = Response(
            miniGameController->getResults(username, input, miniGameController->Terminal, miniGameController->TTT),
            username);

    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> tttTerminal::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<tttTerminal>(this->characterController, this->miniGameController, username, input,
                                         connection);
}

std::unique_ptr<Command> tttTerminal::clone() const {
    return std::make_unique<tttTerminal>(this->characterController, this->miniGameController, this->username,
                                         this->input,
                                         this->connection);
}

std::string tttTerminal::help() {
    return "/tttt - Opens tic tac toe game in terminal\n"
           "/tttt [0-2,0-2] - Make move on the game board. Coordinates are y,x\n"
           "/tttt reset -  Resets the game board\n"
           "/tttt quitGame - Quits the game\n";
}