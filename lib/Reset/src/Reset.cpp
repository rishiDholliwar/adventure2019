#include <Reset.h>

const std::string &Reset::getAction() const {
	return action;
}

int Reset::getID() const {
	return id;
}

int Reset::getLimit() const {
	return limit;
}

int Reset::getRoomID() const {
	return roomID;
}

const std::string &Reset::getState() const {
	return state;
}