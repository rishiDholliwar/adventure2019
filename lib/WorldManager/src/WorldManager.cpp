#include <utility>
#include "../include/WorldManager.h"
#include <iostream>
#include <WorldManager.h>

WorldManager::FunctionMap WorldManager::_funcMap = []
{
    std::map<std::string, std::string (WorldManager::*)(std::string, std::string)> mapping;
    mapping["!say"]  = &WorldManager::say;
    mapping["!move"] = &WorldManager::move;
    mapping["!get"] = &WorldManager::pickUp;
    mapping["!drop"] = &WorldManager::drop;
    mapping["!use"] = &WorldManager::consume;
    return mapping;
}();


std::string WorldManager::say(std::string userName, std::string input)
{
    std::cout << "Say " << input << std::endl;
    return userName+" says: "+input;
}

std::string WorldManager::move(std::string userName, std::string input) {
    std::cout << "Move: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = userManager.getCharacter(userName);

    // Verify if direction is valid
    if(!roomController.isDirectionValid(character.getRoomID(), input)){
        return "That isnt a valid direction";
    }else {
        unsigned int destinationRoomID = roomController.getRoomID(character.getRoomID, input);
        charController.updateRoomID(character, destinationRoomID);

        // Update roomList to account for character moving
        roomController.updateCharacterList(userName, character.getRoomID(), destinationRoomID);
        return userName + " has moved " + input;
    }

}

std::string WorldManager::pickUp(std::string userName, std::string input) {
    std::cout << "Pick Up: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = userManager.getCharacter(userName);

    // Obtain item through input
    auto item = itemList.getItemByName(input);

    // Verify if item exists in the room
    if(!roomController.doesItemExist(character.getRoomID(), item.getItemID())) {
        return "Item: " + input + " doesnt exist in this room!";
    } else {
        if(!charController.addItemToInventory(character, item)){
            return "You have no room for this item";
        }else{
            // Update room to no longer have the item (until the next reset)
            roomController.removeItem(character.getRoomID, input);

            return "Item added to inventory!";
        }
    }
}

std::string WorldManager::drop(std::string userName, std::string input) {
    std::cout << "Drop: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = userManager.getCharacter(userName);

    //obtain item through input
    auto item = itemList.getItemByName(input);

    // Verify if the character has item
    if(!character.hasItem(item.getItemID())){
        return "You don't have this item in your inventory";
    }else{
        // Remove item from character's inventory
        character.dropItem(item.getItemID());

        // Add item to room's item List
        roomController.addItem(character.getRoomID(), item);

        return "You dropped " + input + " into the room!";
    }
}

std::string WorldManager::consume(std::string userName, std::string input) {
    std::cout << "Consume: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = userManager.getCharacter(userName);

    //obtain item through input
    auto item = itemList.getItemByName(input);

    // Verify if character has the item
    if(!character.hasItem(item.getItemID())){
        return "You don't have this item in your inventory";
    }else{
        // Check if item is consumable
        if(!character.isConsumable(item)){
            return "The item is not a consumable!";
        }else {
            // Consume Item and gain it's effects
            character.consume(item.getItemID());

            // Remove item from character's inventory
            character.dropItem(item.getItemID());

            return "you used " + input + " !";
        }
    }
}


void WorldManager::receiveText(std::string input, std::string userName, std::function<void (std::string userName, std::string message)> callBack) {
    auto command = input.substr(0, input.find(' '));
    auto actionText = input.substr(input.find(' ') + 1, std::string::npos);
    std::string ret;
    std::string error = "Unknown";
    if(_funcMap.find(command) != _funcMap.end())
    {
        ret = (this->*_funcMap[command])(userName, actionText);
    }
    else
    {
        error = "Invalid command";
    }
    callBack(userName, ret);
}




