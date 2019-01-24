#include "MessageDispatcher.h"
#include "Utility.h"
#include <boost/algorithm/string.hpp>
#include "CommandUtil.hpp"
#include <iostream>
void MessageDispatcher::onReceive(std::string text, networking::Connection connection) {
    std::string userName;
    if (getBeforeFirstSpace(text) == "!login") {
        userName = login(getBeforeFirstSpace(getAfterFirstSpace(text)), "");
        _connectionPool.insert(std::pair<networking::Connection, std::string>{connection, userName});
        _messagePool.emplace_back(networking::Message{connection, "You have logged in as "+ userName});
        return;
    }

    auto it = this->_connectionPool.find(connection);
    if( it == this->_connectionPool.end() )
    {
        addNotLoginMessage(connection);
        return;
    }
    gameController.receiveText(
            std::move(text), it->second, [&](std::string userName, std::string message){addMessage(userName, message);});
}

void MessageDispatcher::addMessage(std::string userName, std::string message)
{
    auto iterator = _connectionPool.begin();
    while(iterator != _connectionPool.end()){
        if (iterator->second == userName){
            this->_messagePool.push_back(networking::Message{iterator->first, message});
        }
        iterator++;
    }
}

std::deque<networking::Message> MessageDispatcher::pour() {
    auto dq = std::deque<networking::Message>{_messagePool};
    _messagePool.clear();
    return dq;
}

std::string MessageDispatcher::login(std::string userName, std::string password) {
    return "MockUserOne";
}

void MessageDispatcher::addNotLoginMessage(networking::Connection connection) {
    this->_messagePool.emplace_back(networking::Message{connection, "You are not logged in, try !login or !signup"});
}
