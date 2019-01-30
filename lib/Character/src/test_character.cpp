//
// Created on 1/23/2019.
//

#include <Character.h>
#include "Object.h"
#include "Inventory.h"
#include <iostream>
#include <stdio.h>

/*
 * Throw away tester class to test the functions of Character
 */
int main(){
    std::string testCharacterName = "character01";
    Character character(testCharacterName);

    std::cout << "This character's name is : " << character.getCharacterName() << std::endl;
    std::cout << "This character's in the room id : " << character.getCharacterRoomID() << std::endl;

    std::string testObjectName = "object01";
    std::string testObjectID = "objectID01";
    std::string testObjectShortDesc = "Short description";
    std::string testObjectLongDesc = "Long description";

    std::string testObjectName2 = "object02";
    std::string testObjectID2 = "objectID02";

    Object obj(testObjectID,testObjectName,testObjectShortDesc,testObjectLongDesc);
    Object obj2(testObjectID2,testObjectName2,testObjectShortDesc,testObjectLongDesc);
    character.addItemtoInventory(obj);
    character.addItemtoInventory(obj2);
    character.listInventory();
    character.removeItemFromInventory(testObjectName);
    character.listInventory();
    character.removeItemFromInventory(testObjectName2);
    character.listInventory();

    std::cout << "Setting character room to 0005" << std::endl;
    character.setCharacterRoomId("0005");
    std::cout << "This character's name is : " << character.getCharacterName() << std::endl;
    std::cout << "This character's in the room id : " << character.getCharacterRoomID() << std::endl;
    return 0;
}