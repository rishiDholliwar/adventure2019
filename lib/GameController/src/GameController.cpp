#include "GameController.h"
#include <Character.h>
#include <iostream>

std::vector<Response> GameController::say(std::string userName, std::string message) {
    std::cout << "Say " << message << std::endl;

    // check user if user is logged in
    if(!characterController.doesExist(userName)){
        characterController.addToLoggedInUsers(userName);
        roomController.addUserNameToRoom(characterController.getCharacter(userName).getName(),characterController.getCharacter(userName).getRoomID());
    }

    Character character = characterController.getCharacter(userName);



    Response userResponse = Response("Me: " + message, userName);
    std::string genericMessage = userName + ": "+ message;

    return formulateResponse(userResponse, roomController.getUsernameList(character.getRoomID()),genericMessage);
}

std::vector<Response> GameController::broadcast(std::string userName, std::string message) {
    std::cout << "Yell " << message << std::endl;

    //
    if(!characterController.doesExist(userName)){
        characterController.addToLoggedInUsers(userName);
        roomController.addUserNameToRoom(characterController.getCharacter(userName).getName(),characterController.getCharacter(userName).getRoomID());
    }

    Character character = characterController.getCharacter(userName);

    std::vector<std::string> broadcast;
    for(auto &person : characterController.getLoggedInUsers()) {
        broadcast.push_back(person.first);
    }


    Response userResponse = Response("Me: " + message, userName);
    std::string genericMessage = userName + ": " + message;

    return formulateResponse(userResponse, broadcast ,genericMessage);
}

std::vector<Response> GameController::move(std::string userName, std::string direction) {
    std::cout << "Move: " << direction << std::endl;

    // check user if user is logged in
    if(!characterController.doesExist(userName)){
        characterController.addToLoggedInUsers(userName);
        roomController.addUserNameToRoom(characterController.getCharacter(userName).getName(),characterController.getCharacter(userName).getRoomID());
    }

    // Obtain character object based on userName (dummy)
    Character* character = &characterController.getCharacter(userName);

    // Verify if direction is valid
    unsigned int destinationRoomID = roomController.getLinkedRoom(directionMap.at(direction), character->getRoomID());
    if( destinationRoomID == 0){
        Response userResponse = Response("That isn't a valid direction!", userName);
        return formulateResponse(userResponse);
    }

    // Update roomList to account for character moving
    roomController.removeUserNameFromRoom(character->getName(),character->getRoomID());
    roomController.addUserNameToRoom(character->getName(), destinationRoomID);
    character->setRoomID(destinationRoomID);

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


std::vector<Response> GameController::inventory(std::string userName, std::string message) {
    // check user if user is logged in
    if(!characterController.doesExist(userName)){
        characterController.addToLoggedInUsers(userName);
    }

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(userName);

    //get the string containing inventory listed numerically
    std::string inventoryList = character.listInventory();

    //check if inventory is empty or not
    if(inventoryList.empty()) {
        Response userResponse = Response("Your inventory is empty!", userName);
        return formulateResponse(userResponse);
    }

    Response userResponse = Response("Your inventory has: \n" + inventoryList, userName);
    return formulateResponse(userResponse);

}


std::vector<Response> GameController::logout(std::string userName, std::string input) {
    Response userResponse = Response("You have logged out successfully!", userName);

    characterController.logoutUser(userName); // characterController can remove username from active users

    return formulateResponse(userResponse);
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
