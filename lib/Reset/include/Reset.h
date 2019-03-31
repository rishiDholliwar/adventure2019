#ifndef ALTERSPACE_RESET_H
#define ALTERSPACE_RESET_H

#include <string>

class Reset {
private:
	std::string action;
	int id;
	int limit;
	int roomID;
	std::string state;

public:
	Reset() = default;

	explicit Reset(std::string action, int id) : action(std::move(action)), id(id) { };

	explicit Reset(std::string action, int id, int roomID) : action(std::move(action)), id(id), roomID(roomID) { };

	explicit Reset(std::string action, int id, int limit, int roomID) : action(std::move(action)), id(id), limit(limit), roomID(roomID) { };

	explicit Reset(std::string action, int id, int roomID, std::string state) : action(std::move(action)), id(id), roomID(roomID), state(std::move(state)) { };
	
	const std::string &getAction() const;

	int getID() const;

	int getLimit() const;

	int getRoomID() const;

	const std::string &getState() const;
};

#endif //ALTERSPACE_RESET_H