#include <utility>

//
// Created by ximinz on 16/01/19.
//

#ifndef WEBSOCKETNETWORKING_USER_H
#define WEBSOCKETNETWORKING_USER_H


#include <Server.h>

class User {

public:
    User(){};
    
    User(networking::Connection connection, std::string userName, std::string hashedPassword)
    :_connection{connection},_userName{std::move(userName)},_hashedPassword{std::move(hashedPassword)},_roomNumber(0) { }

    void setConnection(const long connectionId);

    long getConnectionId();

    void clearConnection();

    bool isUsernameEqual(std::string userName);

    bool isHashedPasswordEqual(std::string hashedPassword);

    std::string getUsername();

    std::string getHashedPassword();

    bool isSameUser(User user);

    void moveToRoom(int roomNumber);

    int _roomNumber;

private:
    long _connectionId;

    std::string _userName;
    
    std::string _hashedPassword;

};


#endif //WEBSOCKETNETWORKING_USER_H
