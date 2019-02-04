#include <utility>
#include "GameController.h"
#include <Character.h>
#include <iostream>
#include <GameController.h>


GameController::FunctionMap GameController::_funcMap = []
{
    std::map<std::string, std::string (GameController::*)(std::string, std::string)> mapping;
    mapping["!say"]  = &GameController::say;
    mapping["!move"] = &GameController::move;
    mapping["!get"] = &GameController::pickUp;
    mapping["!drop"] = &GameController::drop;

    return mapping;
}();


Response GameController::say(std::string userName, std::string input)
{
    std::cout << "Say " << input << std::endl;
    return userName+" says: "+input;
}

Response GameController::move(std::string userName, std::string input) {
    std::cout << "Move: " << input << std::endl;

    Response response;
    response.usernames.push_back(userName);

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    // Verify if direction is valid
    unsigned int destinationRoomID = roomController.getLinkedRoom(directionMap.at(input), character.getRoomID());
    if( destinationRoomID == 0){
      response.message = "That isn't a valid direction";
      return response;
    }

    // Update roomList to account for character moving
    roomController.removeCharacterFromRoom(character.getCharacterId(),character.getRoomID());
    roomController.addCharacterToRoom(character.getCharacterId(), destinationRoomID);
    character.setRoomID(destinationRoomID);

    response.message = userName + " has moved " + input;
    return response;
}

Response GameController::pickUp(std::string userName, std::string input) {
    std::cout << "Pick Up: " << input << std::endl;

    Response response;
    response.usernames.push_back(userName);

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    if(!objectController.findObject(input)){
      response.message = "No such Item";
      return response;
    }

    // Obtain item through input
    Object item = objectController.getObject(input);

    // Verify if item exists in the room
    if(!roomController.hasItem(character.getRoomID(), item.getId())) {
      response.message = "Item: " + input + " doesnt exist in this room!";
    }

    // Update room to no longer have the item (until the next reset)
    roomController.removeObjectFromRoom(item.getId(), character.getRoomID());

    character.addItemToInventory(item);

    response.message = "Item added to inventory!";
    return response;


}

Response GameController::drop(std::string userName, std::string input) {
    std::cout << "Drop: " << input << std::endl;

    Response response;
    response.usernames.push_back(userName);

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    if(!objectController.findObject(input)){
      response.message = "No such item";
    }
    //obtain item through input
    Object item = objectController.getObject(input);

    // Verify if the character has item
    if(!character.hasItem(item.getId())){
      response.message = "You don't have this item in your inventory";
      return response;
    }
    // Remove item from character's inventory
    character.dropItem(item.getId());

    // Add item to room's item List
    roomController.addObjectToRoom(item.getId(), character.getRoomID());

    response.message = "You dropped " + input + " into the room!";
    return response;
}


Response GameController::logout(std::string userName, std::string input) {
  Response response;
  response.usernames.push_back(userName);
  response.message = userName + "has logged out";

  characterController.logoutUser(userName); // characterController can remove username from active users

  return response;
}

Response GameController::receiveText(std::string input, std::string userName) {

    Response response;

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
      response.usernames.push_back(userName);
      response.message = "Invalid command";
    }

    return (!ret.empty()) ? ret : error;
}
