/////////////////////////////////////////////////////////////////////////////
//                                                 Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "json.hpp"
#include "chatserver.h"

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <Utility.h>
#include <Scheduler.h>
#include <ReturnCodes.h>

#include <GameCommands.h>
#include <UserCommands.h>

// We must decide on how to handle onConnect and onDisconnect
// The reason why our game is a global is because the methods
// can not reference the Game class easily
std::unique_ptr<Game> game;

void onConnect(Connection c) {
    game->addConnection(c);
}

void onDisconnect(Connection c) {
    game->removeConnection(c);
}

void Game::registerCommands() {
    _commandHandler->registerCommand("/say", Say(&_gameController).clone());
    _commandHandler->registerCommand("/login", Login(&_userController, &_gameController).clone());
}

void
Game::addConnection(Connection c) {
    std::cout << "New connection found: " << c.id << "\n";
    _clients.push_back(c);
}


void
Game::removeConnection(Connection c) {
    std::cout << "Connection lost: " << c.id << "\n";
    if (_userController.isConnectionLoggedIn(c)) {
        std::string username = _userController.getUsernameWithConnection(c);
        _userController.logoutUser(username);
        //save character data here, maybe?
        std::cout << "logged out yo" << std::endl;
    }
    auto eraseBegin = std::remove(std::begin(_clients), std::end(_clients), c);
    _clients.erase(eraseBegin, std::end(_clients));
}


std::deque<Message>
Game::processMessages(const std::deque<Message> &incoming, bool &quit) {
    std::deque<Message> result{};
    for (auto& message : incoming) {
        if (message.text == "quit") {
            _server->disconnect(message.connection);
        } else if (message.text == "shutdown") {
            std::cout << "Shutting down.\n";
            quit = true;
        }

        std::string trimmed = utility::trimStringToLength(message.text, 2048);
        auto input = utility::popFront(trimmed);
        while ( input.size() < 2 ) {
            input.push_back("");
        }
        std::string invocationWord = input.at(0);
        std::string text = input.at(1);

        if ( (! _userController.isConnectionLoggedIn(message.connection)) && (invocationWord != "/login"))
        {
            result.push_back(Message{message.connection, std::string{"System: Please login first"}});
            return result;
        }

        std::string username = _userController.getUsernameWithConnection(message.connection);
        std::string output = "Invalid command";

        auto command = _commandHandler->getCommand(username, invocationWord, text, message.connection);
        if ( command == nullptr ) {
            Message msg{message.connection, output};
            result.push_back(msg);
            continue;
        }
        _scheduler->schedule(command, 0);
    }

    auto responses = _scheduler->update();
    for ( auto& res : responses )
    {
        Connection conn = _userController.getConnectionWithUsername(res.username);
        std::cout << conn.id << std::endl;
        result.push_back(Message{conn.id, res.message});
    }

    return result;
}

bool
Game::run()
{
    bool done = false;
    while (!done) {
        try {
            _server->update();
        } catch (std::exception& e) {
            std::cerr << "Exception from Server feedUpdate:\n"
                      << " " << e.what() << "\n\n";
            done = true;
        }

        auto incoming = _server->receive();
        auto log = processMessages(incoming, done);
        _server->send(log);
    }
    return done;
}

Game::Game(Config config)
{
    _server = std::make_unique<Server>(config.port, config.webpage, onConnect, onDisconnect);
    _gameController = GameController();
    _userController = UserController();
    _commandHandler = std::make_unique<CommandHandler>();
    _scheduler      = std::make_unique<Scheduler>(config.heartbeat);
    this->registerCommands();
}

std::string
getHTTPMessage(const char* htmlLocation) {
    if (access(htmlLocation, R_OK ) != -1) {
        std::ifstream infile{htmlLocation};
        return std::string{std::istreambuf_iterator<char>(infile),
                           std::istreambuf_iterator<char>()};

    } else {
        std::cerr << "Unable to open HTML index file:\n"
                  << htmlLocation << "\n";
        std::exit(-1);
    }
}


int
main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage:\n    " << argv[0] << " <port> <html response>\n"
                  << "    e.g. " << argv[0] << " 4002 ./webchat.html\n";
        return 1;
    }

    unsigned short port = std::stoi(argv[1]);
    auto webpage = getHTTPMessage(argv[2]);

    Config config = {.port = port, .webpage = webpage};

    game = std::make_unique<Game>(config);
    game->run();

    return 0;
}
