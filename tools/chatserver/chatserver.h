#ifndef GAME_H
#define GAME_H

#include "Server.h"
#include "GameController.h"
#include <UserController.h>

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
  GameController* _gameController;
  UserController* _userController;
  Server* _server;
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
  Game(Server&, GameController&, UserController&);
  ~Game(){};
  
};

#endif //GAME_H
