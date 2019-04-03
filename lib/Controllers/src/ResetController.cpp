#include <ResetController.h>

#include <algorithm>
#include <iostream>

const std::vector<Reset> &ResetController::getResets() const {
	return resets;
}

void ResetController::addResets(std::vector<Reset> resetVect) {
	for (auto &r : resetVect) {
		resets.push_back(r);
	}
}

void ResetController::addNPCs(std::vector<Character> npcVect) {
	for (auto &npc : npcVect) {
		npcs.emplace(npc.getCharacterID(), npc);
	}
}

void ResetController::reset() {

	for ( auto reset = resets.begin(); reset != resets.end(); reset++ ) {

		if (reset->getAction() == "npc") {
			ID npcid = reset->getID();
			
			if (npcs.find(npcid) == npcs.end()) {
				continue;
			}

			Name npcName = npcs[npcid].getName();
			ID roomID = reset->getRoomID();
			//check how many of this npc is in the room (from room controller)
			std::vector<Name> charactersInRoom = roomController->getCharacterList(reset->getRoomID());
			int count = std::count_if(charactersInRoom.begin(), charactersInRoom.end(), [ &npcName ]( const Name& npc ){ return (npcName == npc ); });
			//if number of that npc is less than reset limit, create one npcs with the same info as the npc in npcs, equip and give whatever items that follow
			if (count < reset->getLimit()) {
				auto characterID = npcs[npcid].getCharacterID();
				auto keywords = npcs[npcid].getKeywords();
				auto shortdesc = npcs[npcid].getShortDesc();
				auto longdesc = npcs[npcid].getLongDesc();
				auto desc = npcs[npcid].getDescription();
				Character newNPC(characterID, keywords, shortdesc, longdesc, desc);
				newNPC.setRoomID(roomID);

				while( reset != resets.end() ) {

					if(reset++; reset->getAction() != "equip" && reset->getAction() != "give") {
						reset--;
						break;
					}
					else if( reset->getAction() == "equip") {
						ID objectid = reset->getID();

						Object newObject = objectController->getObjectFromListByJSONObjectID(objectid);
						objectController->addObjectToList(newObject);
						newNPC.addItemToInventory(newObject);

						if (newNPC.hasItem(newObject.getID())) {
							newNPC.wear(newObject.getID());
						}

					}
					else if( reset->getAction() == "give" ) {
						ID objectid = reset->getID();

						Object newObject = objectController->getObjectFromListByJSONObjectID(objectid);
						objectController->addObjectToList(newObject);
						newNPC.addItemToInventory(newObject);
					}
				}

				characterController->addNPC(newNPC);
				roomController->addCharacterToRoom(npcName, roomID);
			}
		}

		if (reset->getAction() == "object") {
			ID objectid = reset->getID();

			std::vector<ID> objectsInRoom = roomController->getObjectList(reset->getRoomID());

			Object newObject(objectController->getObjectFromListByJSONObjectID(objectid));
			Name newObjectName = newObject.getName();

			auto objInRoom = std::find_if(objectsInRoom.begin(), objectsInRoom.end(), [ &newObjectName, this ]( const ID& objID ){ return newObjectName == objectController->getObjectName(objID); });
			
			if (objInRoom == objectsInRoom.end() ) {
				objectController->addObjectToList(newObject);

				roomController->addObjectToRoom(newObject.getID(), reset->getRoomID());
			}
			
		}

		if (reset->getAction() == "door") {
			ID roomid = reset->getRoomID();

			int direction = reset->getID();
			std::string directionString = "";

			if (direction == 0) {
				directionString = "north";
			} else if (direction == 1) {
				directionString = "east";
			} else if (direction == 2) {
				directionString = "south";
			} else if (direction == 3) {
				directionString = "west";
			}

			if (reset->getState() == "locked") {
				roomController->lockDoor(roomid, directionString);
			}
		}
	}

	std::cout << "reset done" << std::endl;

}