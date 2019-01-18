#include <utility>

#ifndef WEBSOCKETNETWORKING_USER_H
#define WEBSOCKETNETWORKING_USER_H


#include <Server.h>
#include <string>

class User {

public:
    User(){};

    User(std::string userName)
    :_userName(userName) { };
    
    User(long connectionId, std::string userName, size_t hashedPassword)
    :_connectionId(connectionId), _userName(userName), _hashedPassword(hashedPassword), _roomNumber(0) { };

    void setConnection(const long connectionId) const;

    long getConnectionId() const;

    void clearConnection() const;

    bool isUsernameEqual(const std::string userName) const;

    bool isHashedPasswordEqual(const size_t hashedPassword) const;

    std::string getUsername() const;

    std::size_t getHashedPassword() const;

    bool isSameUser(User user) const;

    void startSession(const long connectionId) const;

    void moveToRoom(int roomNumber);

    int getRoomNumber() const;

private:
    mutable long _connectionId;

    std::string _userName;
    
    std::size_t _hashedPassword;

    mutable int _roomNumber;

};

bool operator<(const User& t, const User& o);


#endif //WEBSOCKETNETWORKING_USER_H
