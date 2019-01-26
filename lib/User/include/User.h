#ifndef WEBSOCKETNETWORKING_USER_H
#define WEBSOCKETNETWORKING_USER_H

#include <string>

class User {

public:
    User(){};

    User(std::string username)
    :_username(std::move(username)) { };

    User(std::string username, size_t hashedPassword)
    :_username(std::move(username)), _hashedPassword(std::move(hashedPassword)), _roomNumber(0) { };

    bool isusernameEqual(const std::string username) const;

    bool isHashedPasswordEqual(const size_t hashedPassword) const;

    std::string getusername() const;

    std::size_t getHashedPassword() const;

    void moveToRoom(int roomNumber);

    int getRoomNumber() const;

private:

    std::string _username;

    std::size_t _hashedPassword;

    mutable int _roomNumber;

};

//UserManager uses set<User> and requires a < operator overload for comparison
bool operator<(const User& t, const User& o);

#endif //WEBSOCKETNETWORKING_USER_H
