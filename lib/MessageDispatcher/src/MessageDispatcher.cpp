#include "MessageDispatcher.h"
#include "Utility.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
void MessageDispatcher::onReceive(std::string text, networking::Connection connection) {
    User found_user{};
    bool existingUser;
    for(const auto &each : this->_userPools){
        if(each.first.id == connection.id){
            existingUser = true;
            break;
        }
    }
    if(text.find("!login ") != std::string::npos || !existingUser){
        std::vector<std::string> textParts;
        boost::split(textParts, text, [](char c){return ' ' == c;});
        found_user = this->_userManager.lookUpUser(textParts[1], textParts[2]);
        this->_userPools.emplace_back(connection, found_user);
    }


    _worldManager.receiveText(found_user, text, [&](const User user, const std::string feedback){_messagePool.push_back(networking::Message{this->_userPools.front().first, feedback});});
}

std::deque<networking::Message> MessageDispatcher::pour() {
    return std::deque<networking::Message>{_messagePool};
}
