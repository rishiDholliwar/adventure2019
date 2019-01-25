/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
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
      std::string output = _gameController->receiveText(message.text, dummyUser);
      Message msg{message.connection, output};
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

Game::Game(Server& server, GameController& gc, UserManager& um) 
{
  _server = &server;
  _gameController = &gc;
  _userManager = &um;
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
    std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
              << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
    return 1;
  }

  unsigned short port = std::stoi(argv[1]);
  auto webpage = getHTTPMessage(argv[2]);

  Config config = {.port = port, .webpage = webpage};
  Server server = Server(config.port, config.webpage, onConnect, onDisconnect);
  GameController gameController = GameController();
  UserManager userManager = UserManager();

  // Because we 
  game = std::make_unique<Game>(server, gameController, userManager);
  game->run();

  return 0;
}

