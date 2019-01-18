//
// Created by ximinz on 16/01/19.
//

#include "../include/User.h"

void User::setConnection(const long connectionId) {
	_connectionId = connectionId;
}

long User::getConnectionId() const {
	return _connectionId;
}

void User::clearConnection() const {
	setConnection(0);
}

bool User::isUsernameEqual(const std::string userName) const {
	return _userName == userName;
}

bool User::isHashedPasswordEqual(const size_t hashedPassword) const {
	return _hashedPassword == hashedPassword;
}

std::string User::getUsername() const {
	return _userName;
}

std::size_t User::getHashedPassword() const {
	return _hashedPassword;
}

void User::startSession(long connectionId) {
	_connectionId = connectionId;
	// moveToRoom(..)
}

bool User::operator<(const User& other) {
	return (User::getUsername() < other.getUsername());
}

void User::moveToRoom(int roomNumber) {
    _roomNumber = roomNumber;
}
