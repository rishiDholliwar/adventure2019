//
// Created by ximinz on 16/01/19.
//

#include "../include/MessageDispatcher.h"
#include "../../Ultility/Ultility.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
void MessageDispatcher::onReceive(std::string text, networking::Connection connection) {

    auto it = this->_connectionPool.find(connection.id);
    // std::map<uintptr_t, networking::Connection>::iterator it = this->connectionPool.find(connection.id);
    if( it == this->_connectionPool.end() )
    {
        this->_connectionPool.insert( std::pair<uintptr_t, networking::Connection>(connection.id, connection) );
    }
    _worldManager.receiveText(connection.id, text, [&](const uintptr_t conn_id, std::string message){addMessage(conn_id, message);});
}

void MessageDispatcher::addMessage(const uintptr_t conn_id, std::string message)
{
    networking::Connection conn;
    auto it = this->_connectionPool.find(conn_id);
    if( it == this->_connectionPool.end() )
    {
        std::cout << "Connection could not be found" << std::endl;
        return;
    }
    conn = (*it).second;
    networking::Message msg = {.connection = conn, .text = message};
    this->_messagePool.push_back(msg);
}

std::deque<networking::Message> MessageDispatcher::pour() {
    auto dq = std::deque<networking::Message>{_messagePool};
    _messagePool.clear();
    return dq;
}
