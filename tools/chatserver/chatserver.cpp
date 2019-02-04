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

void
Game::addConnection(Connection c) {
    std::cout << "New connection found: " << c.id << "\n";
    _clients.push_back(c);
}


void
Game::removeConnection(Connection c) {
    std::cout << "Connection lost: " << c.id << "\n";
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
        } else {
            // We need to get the user later on
            std::string dummyUser = "Bob";

            std::string output = "Unknown";
            CommandInfo info = _commandHandler->parseCommand(message.text);
            switch ( info.type )
            {
                case CommandType::GAMECONTROLLER:
                {
                    auto func = _commandHandler->getUserFunc(dummyUser, info.command);
                    if(func != nullptr)
                    {
                        // Copy of unique ptr
                        auto gc = &(*_gameController);
                        output = (gc->*func)(dummyUser, info.input);
                    }
                    else
                    {
                            output = "Invalid command";
                    }
                    break;
                }
                case CommandType::LOGIN:
                {
                    output = "Somehow you've entered login...";
                    break;
                }
                case CommandType::COMMANDHANDLER:
                {
                    auto func = _commandHandler->getCommFunc(dummyUser, info.command);
                    if(func != nullptr)
                    {
                        auto ch = &(*_commandHandler);
                        output = (ch->*func)(dummyUser, info.input);
                    }
                    else
                    {
                        output = "Invalid command";
                    }
                    break;
                }
                case CommandType::UNKNOWN:
                {
                    break;
                }
                default:
                {
                    std::cout << "I dont even know how" << std::endl;
                }
            }
            Message msg{message.connection, output + "\n"};
            result.push_back(msg);
        }
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
        sleep(_heartbeat);
    }
    return done;
}

Game::Game(Config config)
{
    _server = std::make_unique<Server>(config.port, config.webpage, onConnect, onDisconnect);
    _gameController = std::make_unique<GameController>();
    _userManager = std::make_unique<UserManager>();
    _commandHandler = std::make_unique<CommandHandler>();
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

