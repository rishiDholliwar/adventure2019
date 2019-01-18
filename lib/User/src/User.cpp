//
// Created by ximinz on 16/01/19.
//

#include "../include/User.h"

void User::setConnection(const long connectionId) {
	this -> _connectionId = connectionId;
}

long User::getConnectionId() {
	return _connectionId;
}

void User::clearConnection() {
	setConnection(0);
}

bool User::isUsernameEqual(std::string userName) {
	return _userName == userName;
}

bool User::isHashedPasswordEqual(size_t hashedPassword) {
	return _hashedPassword == hashedPassword;
}

std::string User::getUsername() const {
	return _userName;
}

std::size_t User::getHashedPassword() const {
	return _hashedPassword;
}

void User::startSession(long connectionId) {

}

bool User::operator<(const User& other) {
	return (User::getUsername() < other.getUsername());
}

void User::moveToRoom(int roomNumber) {
    this->_roomNumber = roomNumber;
}
