/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "Server.h"
#include "../../lib/MessageDispatcher/include/MessageDispatcher.h"

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>


using networking::Server;
using networking::Connection;
using networking::Message;


std::vector<Connection> clients;


void
onConnect(Connection c) {
  std::cout << "New connection found: " << c.id << "\n";
  clients.push_back(c);
}


void
onDisconnect(Connection c) {
  std::cout << "Connection lost: " << c.id << "\n";
  auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
  clients.erase(eraseBegin, std::end(clients));
}


std::deque<Message>
processMessages(Server &server, MessageDispatcher &messageDispatcher, const std::deque<Message> &incoming, bool &quit) {
  std::deque<Message> result{};
  for (auto& message : incoming) {
    if (message.text == "quit") {
      server.disconnect(message.connection);
    } else if (message.text == "shutdown") {
      std::cout << "Shutting down.\n";
      quit = true;
    } else {
        messageDispatcher.onReceive(message.text, message.connection);
    }
  }
  return messageDispatcher.pour();
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

  bool done = false;
  unsigned short port = std::stoi(argv[1]);
  Server server{port, getHTTPMessage(argv[2]), onConnect, onDisconnect};
  auto msgDispatcher = MessageDispatcher{};

  while (!done) {
    try {
      server.update();
    } catch (std::exception& e) {
      std::cerr << "Exception from Server feedUpdate:\n"
                << " " << e.what() << "\n\n";
      done = true;
    }

    auto incoming = server.receive();
    auto log = processMessages(server, msgDispatcher, incoming, done);
    server.send(log);
    sleep(1);
  }

  return 0;
}

