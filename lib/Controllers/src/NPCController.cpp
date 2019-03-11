#include <iostream>
#include <algorithm>
#include <NPCController.h>
#include <sstream>
#include <ios>
#include <Utility.h>

bool NPCController::addNPCToList(const NPC &npc) {
	//
}

std::string NPCController::getNPCName(ID npcId) {
    auto targetNPCItr = _npcs.find(npcId);

    if (targetNPCItr == _npcs.end()) {
        return "NPC not found";
    }

    return (*targetNPCItr).second.getName();;
}

// look and examine
std::string NPCController::lookNPC(ID npcID) {
	auto npc = (*_npcs.find(npcID)).second;
	return utility::lookEntity(npc);
}

std::string NPCController::examineNPC(ID npcID) {
    auto npc = (*_npcs.find(npcID)).second;
    return utility::examineEntity(npc);
}

bool NPCController::swapNPC(ID swappingID, ID targetNPCID) {
    auto targetNPCItr = _npcs.find(targetNPCID);

    if (targetNPCItr == _npcs.end()) {
        return false;
    }

    auto swapItr = _npcs.extract(targetNPCID);
    swapItr.key() = swappingID;
    _npcs.insert(move(swapItr));

    return true;
}

bool NPCController::findNPC(Name targetName) {
	auto itr = find_if(_npcs.begin(), _npcs.end(), [ targetName ] (std::pair<ID, NPC> const& npcPair )->bool {
		return npcPair.second.getName() == targetName;
	});

	return itr != _npcs.end();

}

ID NPCController::findNPCID(Name targetName) {
	auto itr = find_if(_npcs.begin(), _npcs.end(), [ targetName ] (std::pair<ID, NPC> const& npcPair )->bool {
		return npcPair.second.getName() == targetName;
	});

	return (*itr).first;
}