#ifndef ALTERSPACE_NPCCONTROLLER_H
#define ALTERSPACE_NPCCONTROLLER_H

#include <string>
#include <unordered_map>

#include <NPC.h>
#include <AlterSpace.h>

// For future use
using AlterSpace::ID;
using AlterSpace::Name;

class NPCController
{
private:
    std::unordered_map<ID, NPC> _npcs;

public:
    NPCController() = default;

    bool addNPCToList(const NPC &npc);

    // look and examine
    std::string lookNPC(ID roomId, ID npcID);
    std::string examineNPC(ID roomId, ID npcID);

    bool swapNPC(ID swappingID, ID targetNPCID);

    bool findNPC(Name targetName);

    ID findNPCID(Name targetName);
};

#endif //ALTERSPACE_NPCCONTROLLER_H