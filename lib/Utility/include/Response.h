#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <vector>
#include <utility>
#include <AlterSpace.h>
#include "Server.h"

using networking::Connection;
using AlterSpace::Name;

struct Response {
    std::string message;
    Name username;
    Connection connection = Connection{};

    Response(std::string message, Name username, Connection connection) : message(std::move(message)), username(std::move(username)), connection(std::move(connection)) {}
    Response(std::string message, Name username) : message(std::move(message)), username(std::move(username)) {}
    Response() : message(""), username(""){}
};

#endif
