#include <string>

static std::string getBeforeFirstSpace(const std::string &input){
    auto command = input.substr(0, input.find(' '));
    return command;
}

static std::string getAfterFirstSpace(const std::string &input){
    return input.substr(input.find(' ') + 1, std::string::npos);
}