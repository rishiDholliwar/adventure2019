//
// Created on 1/23/2019.
//

#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H


#include <string>
#include "../../Object/include/Inventory.h"
#include "../../Object/include/Object.h"

class Character {
private:
    unsigned int roomID;
    std::string name;


    Inventory inventory;

    public:
    Character(unsigned int roomID, const std::string &name);

    std::string getName();
    unsigned int getRoomID();

    void setRoomID(unsigned int roomID);

    bool hasItem(unsigned int objectId);

    bool addItemToInventory(Object obj);
    void listInventory();


    void dropItem(unsigned int objectId);
};


#endif //ALTERSPACE_CHARACTER_H
