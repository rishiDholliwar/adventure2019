//
// Created by ximinz on 16/01/19.
//

#include "../include/User.h"

void setConnection(const long connectionId) {
	this -> _connectionId = connectionId;
}

long getConnectionId() {
	return _connectionId;
}

void clearConnection() {
	setConnection(0);
}

bool isUsernameEqual(std::string userName) {
	return _userName == userName;
}

bool isHashedPasswordEqual(std::string hashedPassword) {
	return _hashedPassword == hashedPassword;
}

void User::moveToRoom(int roomNumber) {
    this->_roomNumber = roomNumber;
}
