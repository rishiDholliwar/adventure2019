#ifndef ALTERSPACE_COMMAND_H
#define ALTERSPACE_COMMAND_H

#include <AlterSpace.h>
#include <Response.h>
#include <Server.h>
#include <stringModifier.h>

#include <CharacterController.h>

#include <string>
#include <vector>
#include <utility>
#include <memory>

using AlterSpace::Input;
using AlterSpace::Name;

using networking::Connection;

class Command
{
protected:
    CharacterController* characterController;
    bool registerInteraction = false;
    bool registerCallback = false;
    bool _isCallback = false;
    int callbackAfterHeartbeats = 0;
public:
    Command() = default;
    virtual ~Command() = default;
    virtual std::pair<std::vector<Response>, bool> execute() = 0;
    virtual std::pair<std::vector<Response>, bool> callback();
    std::pair<std::vector<Response>, bool> runCallback();
    virtual std::string help() = 0;
    virtual std::unique_ptr<Command> clone() const = 0;
    virtual std::unique_ptr<Command> clone(Name username, Input input, Connection connection) const = 0;

    bool isCallback() const;
    bool callbackable() const;
    int getCallbackTime() const;
    void setCallback(bool callback);
    bool isInteractable() const;

    std::vector<Response> formulateResponse(Response &userResponse, std::vector<Name> characterList, Input message);
    std::vector<Response> formulateResponse(Response &userResponse, Response &targetResponse);
    std::vector<Response> formulateResponse(Response &userResponse);
};

#endif //ALTERSPACE_COMMAND_H