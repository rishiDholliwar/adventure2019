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

	std::cout << "entered reset" << std::endl;

	for ( auto reset = resets.begin(); reset != resets.end(); reset++ ) {

		std::cout << "entered reset for loop" << std::endl;

		if (reset->getAction() == "npc") {

			std::cout << "entered npc" << std::endl;
			ID npcid = reset->getID();

			if (npcs.find(npcid) == npcs.end()) {
				std::cout << "npc not found" << std::endl;
				continue;
			}

			Name npcName = npcs[npcid].getName();
			ID roomID = reset->getRoomID();
			//check how many of this npc is in the room (from room controller)
			std::vector<Name> charactersInRoom = roomController->getCharacterList(reset->getRoomID());
			int count = std::count_if(charactersInRoom.begin(), charactersInRoom.end(), [ &npcName ]( const Name& npc ){ return (npcName == npc ); });
			std::cout << "COUNT: " << count << " - " << npcName << std::endl;
			//if number of that npc is less than reset limit, create one npcs with the same info as the npc in npcs, equip and give whatever items that follow
			if (count < reset->getLimit()) {
				Character newNPC = npcs[npcid];
				newNPC.setRoomID(roomID);

				while( reset != resets.end() ) {
					std::cout << "entered while loop" << std::endl;

					if(reset++; reset->getAction() != "equip" && reset->getAction() != "give") {
						std::cout << "next isn't give or equip" << std::endl;
						reset--;
						break;
					}
					else if( reset->getAction() == "equip") {
						std::cout << "entered npc equip" << std::endl;
						ID objectid = reset->getID();

						std::cout << "objectid is " << objectid << std::endl;

						Object newObject = objectController->getObjectFromListByJSONObjectID(objectid);
						std::cout << "new objectid is " << newObject.getObjectID() << std::endl;
						std::cout << "new object unique id is " << newObject.getID() << std::endl;
						objectController->addObjectToList(newObject);
						std::cout << "add object to object controller" << std::endl;
						newNPC.addItemToInventory(newObject);
						std::cout << "add item to inventory"<< std::endl;

						if (newNPC.hasItem(newObject.getID())) {
							newNPC.wear(newObject.getID());
							std::cout << "wear item"<< std::endl;
						}

					}
					else if( reset->getAction() == "give" ) {
						std::cout << "entered npc give" << std::endl;
						ID objectid = reset->getID();

						Object newObject = objectController->getObjectFromListByJSONObjectID(objectid);
						objectController->addObjectToList(newObject);
						newNPC.addItemToInventory(newObject);
					}
				}

				characterController->addNPC(newNPC);
				roomController->addCharacterToRoom(npcName, roomID);
				std::cout << "added npc" << std::endl;
			}
		}

		if (reset->getAction() == "object") {
			std::cout << "entered object" << std::endl;
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
			std::cout << "entered door" << std::endl;
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
				std::cout << "door status is locked" << std::endl;
				roomController->lockDoor(roomid, directionString);
			}
		}
	}

	std::cout << "reset done" << std::endl;

}