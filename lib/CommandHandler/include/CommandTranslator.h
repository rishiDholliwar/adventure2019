#ifndef ALTERSPACE_COMMANDTRANSLATOR_H
#define ALTERSPACE_COMMANDTRANSLATOR_H

#include <AlterSpace.h>
#include <Utility.h>

#include <unordered_map>

using AlterSpace::Invocation;

enum CommandType
{
    //USE
    LOGIN = 0,
    LOGOUT,
    SIGNUP,

    //COMMUNICATION
    SAY,
    YELL,
    BROADCAST,
    TELL,
    WHISPER,

    //MOVEMENT
    MOVE,
    NORTH,
    SOUTH,
    WEST,
    EAST,
    NORTHWEST,
    NORTHEAST,
    SOUTHWEST,
    SOUTHEAST,

    //INFORMATION
    HELP,
    INFO,
    LOOK,
    EXAMINE,
    INVENTORY,

    //ITEMS
    PICKUP,
    DROP,
    GIVE,
    WEAR,
    TAKEOFF,
    PIGEONMAIL,

    //SPELLS
    SWAP,
    CONFUSE,
    DECOY,

    //COMBAT
    COMBAT,
    ATTACK,
    BATTLES,
    FLEE,

    //MINI GAME
    TTT,
    TTTT,


    UNKNOWN = -1
};


class CommandTranslator
{
private:
    std::unordered_map<Invocation, CommandType> translateMap;
public:
    CommandTranslator();
    ~CommandTranslator() = default;

    void registerTranslation(const Invocation& invocationWord, CommandType command);
    CommandType translateMe(const Invocation& invocationWord);
};


#endif //ALTERSPACE_COMMANDTRANSLATOR_H
