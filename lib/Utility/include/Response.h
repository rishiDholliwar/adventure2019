

#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <vector>
#include <utility>

struct Response {
    std::string message;
    std::string username;

    Response(std::string message, std::string username) : message(std::move(message)), username(std::move(username)) {}
};

#endif
