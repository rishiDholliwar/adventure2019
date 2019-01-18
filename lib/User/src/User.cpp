//
// Created by ximinz on 16/01/19.
//

#include "../include/User.h"

void User::setConnection(const long connectionId) const {
	this -> _connectionId = connectionId;
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

void User::startSession(const long connectionId) const {
	setConnection(connectionId);
}

void User::moveToRoom(int roomNumber) {
    this->_roomNumber = roomNumber;
}

int User::getRoomNumber() const {
	return _roomNumber;
}

bool operator<(const User& t, const User& o) {
	return (t.getUsername() < o.getUsername());
}

/*
./bin/chatserver
./bin/chatserver 4002 ../adventure2019/webchat.html
*/