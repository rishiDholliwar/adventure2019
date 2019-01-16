#include <utility>

//
// Created by ximinz on 16/01/19.
//

#ifndef WEBSOCKETNETWORKING_USER_H
#define WEBSOCKETNETWORKING_USER_H


#include <Server.h>

class User {
public:
    networking::Connection _connection;
    std::string _userName;
    std::string _hashedPassword;
    User(){};
    User(networking::Connection connection, std::string userName, std::string hashedPassword)
    :_connection{connection},
    _userName{std::move(userName)},
    _hashedPassword{std::move(hashedPassword)},
    _roomNumber(0){}

    void moveToRoom(int roomNumber);

    int _roomNumber;
};


#endif //WEBSOCKETNETWORKING_USER_H
