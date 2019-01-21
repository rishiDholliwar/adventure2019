#include "WorldManager.h"

void WorldManager::receiveText(User user, std::string input, std::function<void (const User user, const std::string feedback)> callBack) {
    this->_users.emplace_back(user);
    if(input.find("!say ") == 0){
        for(const auto &each : this->_users){
            if(user.User::getRoomNumber() == each.User::getRoomNumber()){
                callBack(user, user.getUsername() + " said: " +input.substr(4));
            }
        }
    }
}