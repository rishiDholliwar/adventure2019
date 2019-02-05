#include "GameController.h"
#include <Character.h>
#include <iostream>

std::vector<Response> GameController::say(std::string userName, std::string message) {
    std::cout << "Say " << message << std::endl;

    // check user if user is logged in
    if(!characterController.doesExist(userName)){
        characterController.addToLoggedInUsers(userName);
    }

    Character character = characterController.getCharacter(userName);

    Response userResponse = Response("Me: " + message, userName);
    std::string genericMessage = userName + ": "+ message;

    return formulateResponse(userResponse, roomController.getUsernameList(character.getRoomID()),genericMessage);
}

std::vector<Response> GameController::move(std::string userName, std::string direction) {
    std::cout << "Move: " << direction << std::endl;

    // check user if user is logged in
    if(!characterController.doesExist(userName)){
        characterController.addToLoggedInUsers(userName);
    }
    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    // Verify if direction is valid
    unsigned int destinationRoomID = roomController.getLinkedRoom(directionMap.at(direction), character.getRoomID());
    if( destinationRoomID == 0){
        Response userResponse = Response("That isn't a valid direction!", userName);
        return formulateResponse(userResponse);
    }

    // Update roomList to account for character moving
    roomController.removeCharacterFromRoom(character.getCharacterId(),character.getRoomID());
    roomController.addCharacterToRoom(character.getCharacterId(), destinationRoomID);
    character.setRoomID(destinationRoomID);

    Response userResponse = Response("Headed " + direction, userName);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::pickUp(std::string userName, std::string itemName) {
    std::cout << "Pick Up: " << itemName << std::endl;

    // check user if user is logged in
    if(!characterController.doesExist(userName)){
        characterController.addToLoggedInUsers(userName);
    }

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    if(!objectController.findObject(itemName)){
        Response userResponse = Response("This item does not exist!", userName);
        return formulateResponse(userResponse);
    }

    // Obtain item through input
    Object item = objectController.getObject(itemName);


    if(! roomController.removeObjectFromRoom(item.getId(), character.getRoomID())) {
        Response userResponse = Response("This item does not exist in the room!", userName);
        return formulateResponse(userResponse);
    }

    // Update room to no longer have the item (until the next reset)
    roomController.removeObjectFromRoom(item.getId(), character.getRoomID());
    character.addItemToInventory(item);

    Response userResponse = Response(itemName + " added to inventory!", userName);
    return formulateResponse(userResponse);


}

std::vector<Response> GameController::drop(std::string userName, std::string itemName) {
    std::cout << "Drop: " << itemName << std::endl;

    // check user if user is logged in
    if(!characterController.doesExist(userName)){
        characterController.addToLoggedInUsers(userName);
    }

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    if(!objectController.findObject(itemName)){
        Response userResponse = Response("This item does not exist!", userName);
        return formulateResponse(userResponse);
    }
    //obtain item through input
    Object item = objectController.getObject(itemName);

    // Verify if the character has item
    if(!character.hasItem(item.getId())){
        Response userResponse = Response("You don't have this item in your inventory!", userName);
        return formulateResponse(userResponse);
    }
    // Remove item from character's inventory
    character.dropItem(item.getId());

    // Add item to room's item List
    roomController.addObjectToRoom(item.getId(), character.getRoomID());

    Response userResponse = Response("You dropped " + itemName + " in the room!", userName);
    return formulateResponse(userResponse);
}


std::vector<Response> GameController::logout(std::string userName, std::string input) {
    Response userResponse = Response("You have logged out successfully!", userName);

    characterController.logoutUser(userName); // characterController can remove username from active users

    return formulateResponse(userResponse);
}



std::vector<Response> GameController::receiveText(std::string input, std::string userName) {

    auto command = input.substr(0, input.find(' '));
    auto actionText = input.substr(input.find(' ') + 1, std::string::npos);
    std::vector<Response> ret;
    std::string error = "Unknown";
    if(_funcMap.find(command) != _funcMap.end())
    {
        ret = (this->*_funcMap[command])(std::move(userName), actionText);

    }
    else
    {
        Response userResponse = Response("Invalid command!", userName);
        ret = formulateResponse(userResponse);
    }

    return ret;
}

std::vector<Response>
GameController::formulateResponse(Response &userResponse, std::vector<std::string> characterList,
                                  std::string message){

    std::vector<Response> response;

    for(auto &character : characterList){
        if(character == userResponse.username)
            continue;

        response.emplace_back(message, character);
    }

    response.push_back(userResponse);
    return response;
}

std::vector<Response> GameController::formulateResponse(Response &userResponse) {
    return formulateResponse(userResponse, std::vector<std::string>{}, std::string{});
}
