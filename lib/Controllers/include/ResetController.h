#ifndef ALTERSPACE_RESETCONTROLLER_H
#define ALTERSPACE_RESETCONTROLLER_H

#include <vector>
#include <unordered_map>
#include <string>

#include <RoomController.h>
#include <CharacterController.h>
#include <ObjectController.h>
#include <Reset.h>

using AlterSpace::Name;
using AlterSpace::ID;

class ResetController {
private:
	RoomController* roomController;
	CharacterController* characterController;
	ObjectController* objectController;

	std::vector<Reset> resets;
	std::unordered_map<ID, Character> npcs;
public:
	ResetController() = default;
	
	explicit ResetController(RoomController* roomController, CharacterController* characterController, ObjectController* objectController)
	: roomController(roomController), characterController(characterController), objectController(objectController)
	{ };

	const std::vector<Reset> &getResets() const;

	void addResets(std::vector<Reset> resetVect);

	void addNPCs(std::vector<Character> npcVect);

	void reset();
};

#endif //ALTERSPACE_RESETCONTROLLER_H