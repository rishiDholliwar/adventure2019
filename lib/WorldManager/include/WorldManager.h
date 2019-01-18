//
// Created by ximinz on 16/01/19.
//

#ifndef WEBSOCKETNETWORKING_WORLDMANAGER_H
#define WEBSOCKETNETWORKING_WORLDMANAGER_H


#include <deque>
#include <vector>
#include "../../User/include/User.h"
#include <map>

class WorldManager {

    using FunctionMap = std::map<std::string, bool(WorldManager::*)(uintptr_t, std::string, std::string&)>;

private:
    std::vector<User> _users;
    static FunctionMap _funcMap;
    //Areas
    //other objects

public:
    WorldManager()
    :_users{}{}
    //handles real user input
    void receiveText(const uintptr_t conn_id, std::string input, std::function<void (const uintptr_t conn_id, std::string message)> callBack);
    bool login(const uintptr_t conn_id, std::string input, std::string& output);
    bool say(const uintptr_t conn_id, std::string input, std::string& output);

};


#endif //WEBSOCKETNETWORKING_WORLDMANAGER_H
