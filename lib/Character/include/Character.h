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
    std::string roomID;
    std::string name;
    std::string const STARTING_ROOM = "0000";
    Inventory inventory;

    public:
    Character();
    Character(std::string name);
    std::string getName();
    std::string getRoomID();
    void addItemtoInventory(Object obj);
    //FOR NOW ONLY RETURNING A LONG STRING OF ITEMS
    void listInventory();

};


#endif //ALTERSPACE_CHARACTER_H
