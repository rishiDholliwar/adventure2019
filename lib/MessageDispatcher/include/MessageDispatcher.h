//
// Created by ximinz on 16/01/19.
//

#ifndef WEBSOCKETNETWORKING_MESSAGEDISPATCHER_H
#define WEBSOCKETNETWORKING_MESSAGEDISPATCHER_H


#include <string>
#include "../../User/include/UserManager.h"
#include "../../WorldManager/include/WorldManager.h"

class MessageDispatcher {
    public:
    void onReceive(std::string text, networking::Connection connection);
    std::deque<networking::Message> pour();

    private:
    UserManager _userManager{};
    WorldManager _worldManager{};
    std::vector<std::pair<networking::Connection, User>> _userPools{};
    std::deque<networking::Message> _messagePool{};
};


#endif //WEBSOCKETNETWORKING_MESSAGEDISPATCHER_H
