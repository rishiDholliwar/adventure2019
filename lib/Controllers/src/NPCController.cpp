#include <iostream>
#include <algorithm>
#include <NPCController.h>
#include <sstream>
#include <ios>

bool NPCController::addNPCToList(const NPC &npc) {
	//
}

// look and examine
std::string NPCController::lookNPC(ID roomId, ID npcID) {
	//
}

std::string NPCController::examineNPC(ID roomId, ID npcID) {
	//
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