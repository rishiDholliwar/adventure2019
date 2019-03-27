/////////////////////////////////////////////////////////////////////////////
//                                                 Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "json.hpp"
#include "chatserver.h"
#include <JSONObjects.h>

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

void Game::registerCommands() {

    _commandHandler.registerCommand("/say", Say(&_characterController, &_roomController).clone());
    _commandHandler.registerCommand("/tell", Tell(&_characterController).clone());
    _commandHandler.registerCommand("/whisper", Whisper(&_characterController,&_roomController).clone());
    _commandHandler.registerCommand("/inventory", DisplayInventory(&_characterController).clone());
    _commandHandler.registerCommand("/give", Give(&_characterController, &_objectController).clone());
    _commandHandler.registerCommand("/swap", Swap(&_characterController).clone());
    _commandHandler.registerCommand("/confuse", Confuse(&_characterController, &_roomController).clone());
    _commandHandler.registerCommand("/move", Move(&_characterController,&_roomController).clone());
    _commandHandler.registerCommand("/look", Look(&_characterController,&_roomController, &_objectController).clone());
    _commandHandler.registerCommand("/examine", Examine(&_characterController,&_roomController, &_objectController).clone());
    _commandHandler.registerCommand("/login", Login(&_userController, &_characterController, &_roomController, &_objectController).clone());
    _commandHandler.registerCommand("/logout", Logout(&_userController, &_characterController, &_roomController).clone());
    _commandHandler.registerCommand("/signup", Signup(&_userController, &_characterController, &_roomController, &_objectController).clone());
    _commandHandler.registerCommand("/help", Help(&_characterController, &_commandHandler).clone());
    _commandHandler.registerCommand("/info", Info(&_characterController).clone());
    _commandHandler.registerCommand("/wear", Wear(&_characterController).clone());
    _commandHandler.registerCommand("/takeoff", Takeoff(&_characterController).clone());
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
        auto forcedLogout = std::make_shared<_ForcedLogout>(&_userController, &_characterController, &_roomController, username, "", c);
        _scheduler->schedule(forcedLogout, 0);
        //save character data here, maybe?
        std::cout << "logged out yo" << std::endl;

    }
    auto eraseBegin = std::remove(std::begin(_clients), std::end(_clients), c);
    _clients.erase(eraseBegin, std::end(_clients));
}


std::deque<Message>
Game::processMessages(const std::deque<Message> &incoming, bool &quit) {
    std::deque<Message> result{};
    for (auto &message : incoming) {
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

        // TODO: Add a command parser around here in the future
        // Should return an enum on the type of the command
        // CommandHandler should map enums to Commands
        // This "/login" will be changed to the login enum
        if ( (! _userController.isConnectionLoggedIn(message.connection)) && ((invocationWord != "/login") && (invocationWord != "/signup")) )
        {
            result.push_back(Message{message.connection, std::string{"System: Please login first"}});
            return result;
        }

        std::string username = _userController.getUsernameWithConnection(message.connection);
        std::string output = "Invalid command";

        if (username.empty()) {

            std::vector<std::string> tempInputParser = utility::tokenizeString(text);

            if (tempInputParser.size() != 2) {
                result.push_back(Message{message.connection, std::string{"System: temp input size is not 2"}});
                return result;
            }

            username = tempInputParser.at(0);
            text = tempInputParser.at(1);
        }

        auto command = _commandHandler.getCommand(username, invocationWord, text, message.connection);
        // TODO: Maybe return an "Invalid" Command later on
        if ( command == nullptr ) {
            std::cout << "command is nullptr" << std::endl;
            Message msg{message.connection, output};
            result.push_back(msg);
            continue;
        }

        _scheduler->schedule(command, 0);

    }

    auto responses = _scheduler->update();
    for ( auto& res : responses )
    {
        Connection conn = res.connection;
        if(! conn.id){
            conn = _userController.getConnectionWithUsername(res.username);
        }
        std::cout << conn.id << std::endl;
        result.push_back(Message{conn.id, res.message});
    }

    return result;
}

bool
Game::run() {
    bool done = false;
    while (!done) {
        try {
            _server->update();
        } catch (std::exception &e) {
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
    _server = std::make_unique<Server>(config.port, config.webpage,
                                        [this](Connection c){this->addConnection(c);},
                                        [this](Connection c){this->removeConnection(c);});
    _userController = UserController();
    _commandHandler = CommandHandler();
    _scheduler      = std::make_unique<Scheduler>(config.heartbeat);
    this->registerCommands();
}

std::string
getHTTPMessage(const char *htmlLocation) {
    if (access(htmlLocation, R_OK) != -1) {
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
main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage:\n    " << argv[0] << " <port> <html response>\n"
                  << "    e.g. " << argv[0] << " 4002 ./webchat.html\n";
        return 1;
    }
    using namespace std;
////////////////////////////

    std::string fileName = "mirkwood";

    if (JSONObjects::fileExists(fileName)) {
        cout << "file exists\n";
    } else {
        cout << "error, no such file\n";
    }

    std::vector<Object> objects = JSONObjects::getObjects(fileName);

    // for (auto &obj : objects) {
    //     std::cout << "ID: " << obj.getID() << std::endl;

    //     std::cout << "Type: " << obj.getName() << std::endl;

    //     std::cout << "Abilities: " << std::endl;
    //     for (auto &a : obj.getAbilities()) {
    //       std::cout << "\t" << a.first << ", " << a.second << std::endl;
    //     }

    //     std::cout << " Keywords: " << std::endl;
    //     for (auto &kw : obj.getKeywords()) {
    //         std::cout << "\t" << kw << std::endl;
    //     }

    //     std::cout << " Shortdesc: " << obj.getShortDesc() << std::endl;

    //     std::cout << " Longdesc: " << std::endl;
    //     for (auto &ld : obj.getLongDesc()) {
    //         std::cout << "\t" << ld << std::endl;
    //     }

    //     std::cout << " Extra: " << std::endl;
    //     std::cout << "\tKeywords: " << std::endl;
    //     for (auto &ekw : obj.getExtraKeywords()) {
    //         std::cout << " \t" << ekw << std::endl;
    //     }

    //     std::cout << std::endl;

    //     std::cout << "\tDesc: " << std::endl;
    //     for (auto &ed : obj.getExtraDesc()) {
    //         std::cout << " \t" << ed << std::endl;
    //     }

    //     std::cout << std::endl;
    // }

/////////////////////////////
    unsigned short port = std::stoi(argv[1]);
    auto webpage = getHTTPMessage(argv[2]);

    Config config = {.port = port, .webpage = webpage};

    auto game = std::make_unique<Game>(config);
    game->run();

    return 0;
}
