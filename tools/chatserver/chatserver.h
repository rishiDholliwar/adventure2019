#ifndef GAME_H
#define GAME_H

#include "Server.h"
#include "GameController.h"
#include "UserManager.h"
#include <CommandHandler.h>

using networking::Server;
using networking::Connection;
using networking::Message;

struct Config
{
  int port{0};
  std::string webpage{""};
};

class Game
{
private:
  std::unique_ptr<GameController> _gameController;
  std::unique_ptr<UserManager> _userManager;
  std::unique_ptr<Server> _server;
  std::unique_ptr<CommandHandler> _commandHandler;
  std::vector<Connection> _clients;
  float _heartbeat = 1.0;
  int _port;
  std::string _webpage;
  std::deque<Message> processMessages(const std::deque<Message>&, bool&);
  Game(const Game&) = delete;
public:
  void addConnection(Connection);
  void removeConnection(Connection);
  bool run();
  Game(Config config);
  ~Game(){};

};

#endif //GAME_H
