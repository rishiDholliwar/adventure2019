#include <utility>

#ifndef WEBSOCKETNETWORKING_USER_H
#define WEBSOCKETNETWORKING_USER_H


#include <Server.h>
#include <string>

class User {

public:
    User(){};

    User(std::string userName)
    :_userName{std::move(userName)};
    
    User(networking::Connection connection, std::string userName, size_t hashedPassword)
    :_connection{connection},_userName{std::move(userName)},_hashedPassword{std::move(hashedPassword)},_roomNumber(0){};

    void setConnection(const long connectionId);

    long getConnectionId();

    void clearConnection();

    bool isUsernameEqual(std::string userName);

    bool isHashedPasswordEqual(size_t hashedPassword);

    std::string getUsername();

    std::size_t getHashedPassword();

    bool isSameUser(User user);

    void startSession(long connectionId);

    void moveToRoom(int roomNumber);

    bool operator<(const User& other);

    int _roomNumber;

private:
    long _connectionId;

    std::string _userName;
    
    std::size_t _hashedPassword;

};


#endif //WEBSOCKETNETWORKING_USER_H
