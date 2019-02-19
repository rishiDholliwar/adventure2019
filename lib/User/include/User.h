#ifndef WEBSOCKETNETWORKING_USER_H
#define WEBSOCKETNETWORKING_USER_H

#include <string>

#include <AlterSpace.h>

using AlterSpace::Name;

class User {

public:
    User() = default;

    User(Name username)
    :_username(std::move(username)) { };

    User(Name username, size_t hashedPassword)
    :_username(std::move(username)), _hashedPassword(std::move(hashedPassword)) { };

    bool isusernameEqual(const Name username) const;

    bool isHashedPasswordEqual(const size_t hashedPassword) const;

    std::string getusername() const;

    std::size_t getHashedPassword() const;

private:
    Name _username;

    std::size_t _hashedPassword;

};

//UserManager uses set<User> and requires a < operator overload for comparison
bool operator<(const User& t, const User& o);

#endif //WEBSOCKETNETWORKING_USER_H
