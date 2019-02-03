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
    std::string name;
    unsigned int characterId;
    unsigned int roomID;


    Inventory inventory;

    public:
    Character(const std::string &name, unsigned int characterId, unsigned int roomID);

    std::string getName();
    unsigned int getRoomID();

    unsigned int getCharacterId() const;

    void setRoomID(unsigned int roomID);

    bool hasItem(unsigned int objectId);



    bool addItemToInventory(Object obj);
    void listInventory();


    void dropItem(unsigned int objectId);
};


#endif //ALTERSPACE_CHARACTER_H
