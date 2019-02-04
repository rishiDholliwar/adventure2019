#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <vector>

struct Response {
    std::string message;
    std::vector<std::string> usernames;
};

#endif
