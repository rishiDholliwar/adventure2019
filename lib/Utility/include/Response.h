#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <vector>
#include <utility>
#include <AlterSpace.h>

using AlterSpace::Name;

struct Response {
    std::string message;
    Name username;

    Response(std::string message, Name username) : message(std::move(message)), username(std::move(username)) {}
};

#endif
