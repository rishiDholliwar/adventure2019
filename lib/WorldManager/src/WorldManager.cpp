//
// Created by ximinz on 16/01/19.
//

#include "../include/WorldManager.h"
#include <iostream>
WorldManager::FunctionMap WorldManager::_funcMap = []
{
    std::map<std::string, bool(WorldManager::*)(uintptr_t, std::string, std::string&)> mapping;
    mapping["!login"] = &WorldManager::login;
    mapping["!say"]   = &WorldManager::say;
    return mapping;
}();

bool WorldManager::login(const uintptr_t conn_id, std::string input, std::string& output)
{
    std::cout << "Login" << std::endl;
    output = "Logging in " + input;
    return true;
}

bool WorldManager::say(const uintptr_t conn_id, std::string input, std::string& output)
{
    std::cout << "Say " << input << std::endl;
    output = "Saying " + input;
    return true;
}

void WorldManager::receiveText(const uintptr_t conn_id, std::string input, std::function<void (const uintptr_t conn_id, std::string message)> callBack) {
    auto command = input.substr(0, input.find(' '));
    auto inpt = input.substr(input.find(' ') + 1, std::string::npos);
    std::string output;
    bool ret;
    std::string error = "Unknown";
    if(_funcMap.find(command) != _funcMap.end())
    {
        ret = (this->*_funcMap[command])(conn_id, inpt, output);
    }
    else
    {
        error = "Invalid command";
    }
    if(!ret)
    {
        output = "Error occurred - " + error;
    }
    std::cout << output << std::endl;
    callBack(conn_id, output);
}

// Test main
// int main(int argc, char const *argv[])
// {
//     uintptr_t test = 1231231;
//     std::string input = "!login WOW";
//     WorldManager w = WorldManager();
//     w.receiveText(test, input);
//     w.receiveText(test, "!say KAPPA");
//     return 0;
// }