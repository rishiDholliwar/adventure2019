#include <iostream>
#include <algorithm>
#include <NPC.h>
#include <sstream>
#include <ios>

NPC::NPC(const Name &name, ID roomID)
{
  this->name = name;
  this->roomID = roomID;
}

Name NPC::getName() const {
    return this->name;
}

ID NPC::getRoomID() const {
    return this->roomID;
}

ID NPC::getID() const {
    return id;
}

std::string NPC::getInfo() const {

  std::stringstream retString;
  retString << "ID: " << id << "\n" << "Name: " << name << "\n" << "Room ID: " << roomID << "\n";


	return retString.str();
}

void NPC::setRoomID(ID roomID) {
    roomID = roomID;
}