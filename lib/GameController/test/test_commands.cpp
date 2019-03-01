#include <GameController.h>
#include <ObjectController.h>
#include <Character.h>
#include <Object.h>
#include <Inventory.h>
#include <stdio.h>
#include <iostream>

int main() {

	std::string testCharacterName = "lora";
    Character character(testCharacterName, 0);
    std::string testObjectName = "Basic Sword";
    std::string testObjectName2 = "Basic Armor";
    Object object(testObjectName2);
    Object obj(testObjectName);
    Object obj2(testObjectName2);
    character.addItemToInventory(obj);
    character.addItemToInventory(obj2);
    std::cout << character.getName() + ": " << std::endl;
    std::cout << character.listInventory() << std::endl;
    std::cout << std::endl;
    // std::cout << character.getName() << std::endl;
    // std::cout << character.getRoomID() << std::endl;

    std::string test2CharacterName = "bryan";
    Character character2(test2CharacterName, 0);
    character2.addItemToInventory(obj);

    std::cout << character2.getName() + ": " << std::endl;
    std::cout << character2.listInventory() << std::endl;
    std::cout << std::endl;

    character.dropItem(obj.getID());
    std::cout << character.getName() + ": " << std::endl;
    std::cout << character.listInventory() << std::endl;
    std::cout << std::endl;

    std::cout << std::boolalpha << character.hasItem(obj.getID()) << std::endl;
    std::cout << character.hasItem(obj2.getID()) << std::endl;
    std::cout << std::endl;
    std::string objName = obj.getName();
    std::string obj2Name = obj2.getName();
    std::cout << objName << std::endl;
    std::cout << character.hasItem(objName) << std::endl;
    std::cout << std::endl;
    std::cout << obj2Name << std::endl;
    std::cout << character.hasItem(obj2Name) << std::endl;
    std::cout << std::endl;

    character.wear(obj2.getID());
    std::cout << character.getName() + ": " << std::endl;
    std::cout << character.listInventory() << std::endl;
    std::cout << character.isWearing(obj2.getID()) << std::endl;
    std::cout << std::endl;
    std::cout << character.getInfo() << std::endl;
    std::cout << std::endl;
    character.remove(obj2);
    std::cout << character.getName() + ": " << std::endl;
    std::cout << character.listInventory() << std::endl;
    std::cout << character.isWearing(obj2.getID()) << std::endl;
    std::cout << std::endl;
    std::cout << character2.getInfo() << std::endl;
    std::cout << std::endl;
    return 0;
}