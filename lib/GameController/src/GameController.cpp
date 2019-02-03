#include <utility>
#include "GameController.h"
#include "../../Character/include/Character.h"
#include <iostream>

GameController::FunctionMap GameController::_funcMap = []
{
    std::map<std::string, std::string (GameController::*)(std::string, std::string)> mapping;
    mapping["!say"]  = &GameController::say;
    mapping["!move"] = &GameController::move;
    mapping["!get"] = &GameController::pickUp;
    mapping["!drop"] = &GameController::drop;

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
    Character character = characterController.getCharacter(userName);

    // Verify if direction is valid
    if(!roomController.isDirectionValid(character.getRoomID(), input)){
        return "That isnt a valid direction";
    }
    unsigned int destinationRoomID = roomController.getRoomID(character.getRoomID(), input);
    character.setRoomID(destinationRoomID);

    // Update roomList to account for character moving
    roomController.updateCharacterList(userName, character.getRoomID(), destinationRoomID);
    return userName + " has moved " + input;
    

}

std::string GameController::pickUp(std::string userName, std::string input) {
    std::cout << "Pick Up: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    if(!objectController.findObject(input)){
        return "No such Item";
    }

    // Obtain item through input
    Object item = objectController.getObject(input);

    // Verify if item exists in the room
    if(!roomController.doesItemExist(character.getRoomID(), item.getId())) {
        return "Item: " + input + " doesnt exist in this room!";
    } 

    // Update room to no longer have the item (until the next reset)
    roomController.removeItem(character.getRoomID, input);

    character.addItemToInventory(item);

    return "Item added to inventory!";


}

std::string GameController::drop(std::string userName, std::string input) {
    std::cout << "Drop: " << input << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    if(!objectController.findObject(input)){
        return "No such Item";
    }
    //obtain item through input
    Object item = objectController.getObject(input);

    // Verify if the character has item
    if(!character.hasItem(item.getId())){
        return "You don't have this item in your inventory";
    }
    // Remove item from character's inventory
    character.dropItem(item.getId());

    // Add item to room's item List
    roomController.addItem(character.getRoomID(), item);

    return "You dropped " + input + " into the room!";
    
}



std::string GameController::receiveText(std::string input, std::string userName) {

    auto command = input.substr(0, input.find(' '));
    auto actionText = input.substr(input.find(' ') + 1, std::string::npos);
    std::string ret;
    std::string error = "Unknown";
    if(_funcMap.find(command) != _funcMap.end())
    {
        ret = (this->*_funcMap[command])(std::move(userName), actionText);
    }
    else
    {
        error = "Invalid command";
    }

    return (!ret.empty()) ? ret : error;
}

