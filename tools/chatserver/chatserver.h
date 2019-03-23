#ifndef GAME_H
#define GAME_H

#include "Server.h"
#include "GameController.h"
#include <UserController.h>
#include <CharacterController.h>
#include <RoomController.h>
#include <ObjectController.h>
#include <CommandHandler.h>
#include <Scheduler.h>

using networking::Server;
using networking::Connection;
using networking::Message;

struct Config
{
  int port{0};
  std::string webpage{""};
  long heartbeat{200};
};

class Game
{
private:
  GameController _gameController;
  UserController _userController;
  CharacterController _characterController;
  RoomController _roomController;
  ObjectController _objectController;
  NPCController _npcController;
  std::unique_ptr<Server> _server;
  CommandHandler _commandHandler;
  std::unique_ptr<Scheduler> _scheduler;

  std::vector<Connection> _clients;
  long _heartbeat = 1000;
  int _port;
  std::string _webpage;
  std::deque<Message> processMessages(const std::deque<Message>&, bool&);
  Game(const Game&) = delete;
  void registerCommands();

public:

  void addConnection(Connection);
  void removeConnection(Connection);
  bool run();

  Game(Config config);

  ~Game(){};

};

#endif //GAME_H
