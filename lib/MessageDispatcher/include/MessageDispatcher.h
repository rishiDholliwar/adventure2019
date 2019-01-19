//
// Created by ximinz on 16/01/19.
//

#ifndef WEBSOCKETNETWORKING_MESSAGEDISPATCHER_H
#define WEBSOCKETNETWORKING_MESSAGEDISPATCHER_H


#include <string>
#include <map>
#include "../../User/include/UserManager.h"
#include "../../WorldManager/include/WorldManager.h"

class MessageDispatcher {
    public:
    void onReceive(std::string text, networking::Connection connection);
    void addMessage(std::string userName, std::string message);
    std::deque<networking::Message> pour();

    private:
    WorldManager _worldManager{};
    std::map<networking::Connection, std::string> _connectionPool{};
    std::deque<networking::Message> _messagePool{};

    std::string login(std::string userName, std::string password);

    void addNotLoginMessage(networking::Connection connection);
};


#endif //WEBSOCKETNETWORKING_MESSAGEDISPATCHER_H
