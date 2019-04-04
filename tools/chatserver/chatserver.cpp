/////////////////////////////////////////////////////////////////////////////
//                                                 Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "json.hpp"
#include "chatserver.h"
// #include <JSONObjects.h>

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <Utility.h>
#include <Scheduler.h>
#include <ReturnCodes.h>
#include <JSONThingy.h>

#include <GameCommands.h>
#include <UserCommands.h>
#include <CombatCommands.h>
#include <MiniGameCommands.h>

#include <ResetCommand.h>
#include <PigeonCommand.h>
#include <JSONThingy.h>


void Game::registerCommands() {
    _commandHandler.registerCommand(CommandType::SAY, Say(&_characterController, &_roomController).clone());
    _commandHandler.registerCommand(CommandType::TELL, Tell(&_characterController).clone());
    _commandHandler.registerCommand(CommandType::WHISPER, Whisper(&_characterController,&_roomController).clone());
    _commandHandler.registerCommand(CommandType::INVENTORY, DisplayInventory(&_characterController).clone());
    _commandHandler.registerCommand(CommandType::GIVE, Give(&_characterController, &_roomController, &_objectController).clone());
    _commandHandler.registerCommand(CommandType::SWAP, Swap(&_characterController, &_roomController).clone());
    _commandHandler.registerCommand(CommandType::CONFUSE, Confuse(&_characterController, &_roomController).clone());
    _commandHandler.registerCommand(CommandType::LOGIN, Login(&_userController, &_characterController, &_roomController, &_objectController).clone());
    _commandHandler.registerCommand(CommandType::LOGOUT, Logout(&_userController, &_characterController, &_roomController).clone());
    _commandHandler.registerCommand(CommandType::SIGNUP, Signup(&_userController, &_characterController, &_roomController, &_objectController).clone());
    _commandHandler.registerCommand(CommandType::HELP, Help(&_characterController, &_commandHandler).clone());
    _commandHandler.registerCommand(CommandType::LOOK, Look(&_characterController,&_roomController, &_objectController).clone());
    _commandHandler.registerCommand(CommandType::EXAMINE, Examine(&_characterController,&_roomController, &_objectController).clone());
    _commandHandler.registerCommand(CommandType::MOVE, Move(&_characterController,&_roomController).clone());
    _commandHandler.registerCommand(CommandType::PIGEONMAIL, PigeonMail(&_characterController,&_roomController, &_pigeonEXE).clone());
    _commandHandler.registerCommand(CommandType::INFO, Info(&_characterController).clone());
    _commandHandler.registerCommand(CommandType::WEAR, Wear(&_characterController).clone());
    _commandHandler.registerCommand(CommandType::TAKEOFF, Takeoff(&_characterController, &_objectController).clone());

    //For combat
    _commandHandler.registerCommand(CommandType::COMBAT, CombatExamine(&_characterController, &_roomController, &_combatController).clone());
    _commandHandler.registerCommand(CommandType::ATTACK, CombatAttack(&_characterController, &_roomController, &_combatController).clone());
    _commandHandler.registerCommand(CommandType::BATTLES, CombatBattles(&_characterController, &_roomController, &_combatController).clone());
    _commandHandler.registerCommand(CommandType::FLEE, CombatFlee(&_characterController, &_roomController, &_combatController).clone());

    //For mini game
    _commandHandler.registerCommand(CommandType::TTT, tttBrowser(&_characterController,  &_miniGameController).clone());
    _commandHandler.registerCommand(CommandType::TTTT, tttTerminal(&_characterController,  &_miniGameController).clone());

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

        if(_combatController.isBattleState(username)){
            Name targetName = _combatController.getTargetName(username);
            _combatController.setTargetLogoutState(targetName);
            std::cout << "delete combat for: " << username << std::endl;
        }


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

        auto invocation = _commandTranslator.translateMe(invocationWord);

        // TODO: Add a command parser around here in the future
        // Should return an enum on the type of the command
        // CommandHandler should map enums to Commands
        // This "/login" will be changed to the login enum
        if ( (! _userController.isConnectionLoggedIn(message.connection)) && ((invocation != CommandType::LOGIN) && (invocation != CommandType::SIGNUP)) )
        {
            result.push_back(Message{message.connection, std::string{"System: Please login first"}});
            return result;
        }

        std::string username = _userController.getUsernameWithConnection(message.connection);
        std::string output = "Invalid command";

        if (username.empty()) {

            std::vector<std::string> tempInputParser = utility::tokenizeString(text);

            if (tempInputParser.size() != 2) {
                result.push_back(Message{message.connection, std::string{"Fill in all fields"}});
                return result;
            }

            username = tempInputParser.at(0);
            text = tempInputParser.at(1);
        }

      //  PERMISSIONS COULD BE CHECKED HERE
        if(invocation != CommandType::LOGIN && invocation != CommandType::SIGNUP){
           // _characterController.toggleCharacterCombat(username);
            if(_characterController.isCharacterInCombat(username)){
                std::cout <<  "---------User: " << username << " is in combat---------\n";
                if(invocation != CommandType::FLEE){
                    std::cout << "You are in combat. You can only flee";
                    result.push_back(Message{message.connection, std::string{"You are in combat. You can only flee"}});
                    return result;
                }

            }
        }

        auto command = _commandHandler.getCommand(username, invocation, text, message.connection);
        // TODO: Maybe return an "Invalid" Command later on
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
    _commandTranslator = CommandTranslator();
    _scheduler      = std::make_unique<Scheduler>(config.heartbeat);
    _resetController = ResetController(&_roomController, &_characterController, &_objectController);

    JSONThingy jt;
    jt.load("mirkwood", _objectController);
    jt.load("mirkwood", _roomController);
    jt.load("mirkwood", _resetController);

    _pigeonEXE = PigeonEXE(&_roomController);
    _pigeonEXE.getShortestDirection(8865, 8865);

    this->registerCommands();
    _scheduler->schedule(std::make_shared<ResetCommand>(&_resetController, 300), 0);
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

    unsigned short port = std::stoi(argv[1]);
    auto webpage = getHTTPMessage(argv[2]);

    Config config = {.port = port, .webpage = webpage};

    auto game = std::make_unique<Game>(config);
    game->run();

    return 0;
}
