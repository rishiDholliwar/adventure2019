#include <utility>
#include "GameController.h"
#include <iostream>

GameController::FunctionMap GameController::_funcMap = []
{
    std::map<std::string, std::string (GameController::*)(std::string, std::string)> mapping;
    mapping["!say"]  = &GameController::say;
    mapping["!move"] = &GameController::move;
    mapping["!get"] = &GameController::pickUp;
    mapping["!drop"] = &GameController::drop;
    mapping["!use"] = &GameController::consume;

    return mapping;
}();


std::string GameController::say(std::string userName, std::string input)
{
    std::cout << "Say " << input << std::endl;
    return userName+" says: "+input;
}

std::string GameController::move(std::string userName, std::string input) {
    std::cout << "Move: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = userManager.getCharacter(userName);

    // Verify if direction is valid
    if(!roomController.isDirectionValid(character.getRoomID(), input)){
        return "That isnt a valid direction";
    }
    unsigned int destinationRoomID = roomController.getRoomID(character.getRoomID, input);
    charController.updateRoomID(character, destinationRoomID);

    // Update roomList to account for character moving
    roomController.updateCharacterList(userName, character.getRoomID(), destinationRoomID);
    return userName + " has moved " + input;
    

}

std::string GameController::pickUp(std::string userName, std::string input) {
    std::cout << "Pick Up: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = userManager.getCharacter(userName);

    // Obtain item through input
    auto item = itemList.getItemByName(input);

    // Verify if item exists in the room
    if(!roomController.doesItemExist(character.getRoomID(), item.getItemID())) {
        return "Item: " + input + " doesnt exist in this room!";
    } 

    if(!charController.addItemToInventory(character, item)){
        return "You have no room for this item";
    }
    // Update room to no longer have the item (until the next reset)
    roomController.removeItem(character.getRoomID, input);

    return "Item added to inventory!";


}

std::string GameController::drop(std::string userName, std::string input) {
    std::cout << "Drop: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = userManager.getCharacter(userName);

    //obtain item through input
    auto item = itemList.getItemByName(input);

    // Verify if the character has item
    if(!character.hasItem(item.getItemID())){
        return "You don't have this item in your inventory";
    }
    // Remove item from character's inventory
    character.dropItem(item.getItemID());

    // Add item to room's item List
    roomController.addItem(character.getRoomID(), item);

    return "You dropped " + input + " into the room!";
    
}

std::string GameController::consume(std::string userName, std::string input) {
    std::cout << "Consume: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = userManager.getCharacter(userName);

    //obtain item through input
    auto item = itemList.getItemByName(input);

    // Verify if character has the item
    if(!character.hasItem(item.getItemID())){
        return "You don't have this item in your inventory";
    }
    // Check if item is consumable
    if(!character.isConsumable(item)){
        return "The item is not a consumable!";
    }
    // Consume Item and gain it's effects
    character.consume(item.getItemID());

    // Remove item from character's inventory
    character.dropItem(item.getItemID());

    return "you used " + input + " !";
    
    
}



std::string GameController::receiveText(std::string input, std::string userName) {

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

    return (ret != "") ? ret : error;
}

