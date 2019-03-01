//
// Created on 1/23/2019.
//

#include <Character.h>
#include "Object.h"
#include "Inventory.h"
#include <iostream>
#include <stdio.h>

int main(){

    std::string testCharacterName = "character01";
    Character character(testCharacterName, 0);
    std::string testObjectName = "object01";
    std::string testObjectName2 = "object02";
    Object object(testObjectName2);
    Object obj(testObjectName);
    Object obj2(testObjectName2);
    // character.addItemtoInventory(obj);
    // character.addItemtoInventory(obj2);
    character.listInventory();
    std::cout << character.getName() << std::endl;
    std::cout << character.getRoomID() << std::endl;
    return 0;
}