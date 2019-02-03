#include <User.h>

bool User::isusernameEqual(const Name username) const {
	return _username == username;
}

bool User::isHashedPasswordEqual(const size_t hashedPassword) const {
	return _hashedPassword == hashedPassword;
}

std::string User::getusername() const {
	return _username;
}

std::size_t User::getHashedPassword() const {
	return _hashedPassword;
}

void User::moveToRoom(int roomNumber) {
    this->_roomNumber = roomNumber;
}

int User::getRoomNumber() const {
	return _roomNumber;
}

bool operator<(const User& t, const User& o) {
	return (t.getusername() < o.getusername());
}

/*
./bin/chatserver
./bin/chatserver 4002 ../adventure2019/webchat.html
*/
