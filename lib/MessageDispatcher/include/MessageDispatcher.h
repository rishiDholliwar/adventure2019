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
    void addMessage(const uintptr_t conn_id, std::string message);
    std::deque<networking::Message> pour();

    private:
    UserManager _userManager{};
    WorldManager _worldManager{};
    std::map<uintptr_t, networking::Connection> _connectionPool{};
    std::deque<networking::Message> _messagePool{};
};


#endif //WEBSOCKETNETWORKING_MESSAGEDISPATCHER_H
