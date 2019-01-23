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

    User(std::string userName, size_t hashedPassword)
    :_userName(userName), _hashedPassword(hashedPassword), _roomNumber(0) { };

    bool isUsernameEqual(const std::string userName) const;

    bool isHashedPasswordEqual(const size_t hashedPassword) const;

    std::string getUsername() const;

    std::size_t getHashedPassword() const;

    void moveToRoom(int roomNumber);

    int getRoomNumber() const;

    //UserManager uses set<User> and requires a < operator overload for comparison
    bool operator<(const User& t, const User& o);

private:

    std::string _userName;

    std::size_t _hashedPassword;

    mutable int _roomNumber;

};

#endif //WEBSOCKETNETWORKING_USER_H
