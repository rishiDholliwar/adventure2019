#include "GameController.h"
#include <Character.h>
#include <iostream>
#include <GameController.h>
#include <Utility.h>

using ASDirection::directionMap;

GameController::GameController()
{
    this->characterController = CharacterController();
    this->objectController = ObjectController();
}

bool GameController::loadCharacter(Name username)
{
    return characterController.addCharacter(username, roomController);
}

std::vector<Response> GameController::info(Name username, Input message) {
    Response userResponse = Response(characterController.getCharacterInfo(username), username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::say(Name username, Input message) {
    std::cout << "Say " << message << std::endl;

    Response userResponse = Response("Me: " + message, username);
    std::string genericMessage = username + ": "+ message;

    return formulateResponse(userResponse, roomController.getUsernameList(characterController.getCharacterRoomID(username)), genericMessage);
}

std::vector<Response> GameController::whisper(Name username, Input inputs) {
    std::vector<std::string> inputStrings = utility::popFront(inputs);

    //check if user input format is incorrect
    if (inputStrings.size() != 2) {
        Response userResponse = Response("You must type in the {username of the character you wish to message}, {message}", username);
        return formulateResponse(userResponse);
    }

    //if whisper target character is not currently logged in
    if (!characterController.doesCharacterExist(inputStrings.at(0))) {
        Response userResponse = Response(inputStrings.at(0) + ": is not currently logged in", username);
        return formulateResponse(userResponse);
    }

    Response userResponse = Response("To [" + inputStrings.at(0) + "]: " + inputStrings.at(1), username);
    Response targetResponse = Response("From [" + username + "]: " + inputStrings.at(1), inputStrings.at(0));

    return formulateResponse(userResponse, targetResponse);
}

std::vector<Response> GameController::broadcast(Name username, Input message) {
    std::cout << "Broadcast " << message << std::endl;

    std::vector<std::string> broadcast = characterController.getAllCharacterNames();


    Response userResponse = Response("Me: " + message, username);
    std::string genericMessage = username + ": " + message;

    return formulateResponse(userResponse, broadcast, genericMessage);
}

std::vector<Response> GameController::move(Name username, Input direction) {
    std::cout << "Move: " << direction << std::endl;

    // check if direction exists
    if(!directionExists(direction)){
        Response userResponse = Response("There is no such direction!", username);
        return formulateResponse(userResponse);
    }

    // Verify if direction is valid
    unsigned int destinationRoomID = roomController.getLinkedRoom(directionMap.at(direction), characterController.getCharacterRoomID(username));
    if( destinationRoomID == 0){
        Response userResponse = Response("That isn't a valid direction!", username);
        return formulateResponse(userResponse);
    }

    // list of users to notify that character moved north
    std::vector<std::string> userList = roomController.getUsernameList(characterController.getCharacterRoomID(username));

    // Update roomList to account for character moving
    roomController.removeUserNameFromRoom(username, characterController.getCharacterRoomID(username));
    roomController.addUserNameToRoom(username, destinationRoomID);
    characterController.setCharacterRoomID(username, destinationRoomID);

    Response userResponse = Response("Headed " + direction, username);
    std::string genericMessage = username + " headed " + direction;
    return formulateResponse(userResponse, userList, genericMessage);
}

std::vector<Response> GameController::pickUp(Name username, Input itemName) {
    std::cout << "Pick Up: " << itemName << std::endl;

    if(!objectController.doesObjectExist(itemName)){
        Response userResponse = Response("This item does not exist!", username);
        return formulateResponse(userResponse);
    }

    // Obtain item through input
    Object item = objectController.getObjectFromListByName(itemName);


    if(!roomController.removeObjectFromRoom(item.getID(), characterController.getCharacterRoomID(username))) {
        Response userResponse = Response("This item does not exist in the room!", username);
        return formulateResponse(userResponse);
    }

    // Update room to no longer have the item (until the next reset)
    characterController.addItemToCharacterInventory(username, item);

    Response userResponse = Response(itemName + " added to inventory!", username);
    return formulateResponse(userResponse);

}

std::vector<Response> GameController::drop(Name username, Input itemName) {

    if(!objectController.doesObjectExist(itemName)){
        Response userResponse = Response("This item does not exist!", username);
        return formulateResponse(userResponse);
    }
    //obtain item through input
    Object item = objectController.getObjectFromListByName(itemName);

    // Verify if the character has item
    if(!characterController.characterHasItem(username, item.getID())){
        Response userResponse = Response("You don't have this item in your inventory!", username);
        return formulateResponse(userResponse);
    }
    // Remove item from character's inventory
    characterController.dropItemFromCharacterInventory(username, item.getID());

    // Add item to room's item List
    roomController.addObjectToRoom(item.getID(), characterController.getCharacterRoomID(username));

    Response userResponse = Response("You dropped " + itemName + " in the room!", username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::give(Name username, Input message) {
	std::vector<std::string> inputStrings = utility::tokenizeString(message);

	//check if user input format is incorrect
	if (inputStrings.size() != 2) {
		Response userResponse = Response("You must type in the {username of the character you wish to gift to}, {item name}", username);
		return formulateResponse(userResponse);
	}

	//if gift target character doesn't exist
	if (!characterController.doesCharacterExist(inputStrings.at(0))) {
		Response userResponse = Response("Character name " + inputStrings.at(0) + " does not exist for you to gift to.", username);
		return formulateResponse(userResponse);
	}

    Name targetCharacterName = inputStrings.at(0);
    Name giftName = inputStrings.at(1);

	//check if gift item exists in user inventory
	if (!characterController.characterHasItem(username, giftName)) {
		Response userResponse = Response("Item name " + giftName + " does not exist for you to give.", username);
		return formulateResponse(userResponse);
	}

	Object gift = characterController.getItemFromCharacterInventory(username, giftName);

	//drop item from user inventory
	if (!characterController.dropItemFromCharacterInventory(username, gift.getID())) {
        Response userResponse = Response("dropping failed for userChar", username);
        return formulateResponse(userResponse);
    }

	//add item to target user inventory
	characterController.addItemToCharacterInventory(targetCharacterName, gift);

	if (!characterController.characterHasItem(targetCharacterName, gift.getID())) {
		Response userResponse = Response("Giving " + giftName + " to character " + targetCharacterName + " has failed.", username);
		return formulateResponse(userResponse);
	}

	//generate response
	Response userResponse = Response("You have given " + giftName + " to character " + targetCharacterName + "!", username);
	return formulateResponse(userResponse);

}

std::vector<Response> GameController::wear(Name username, Input itemName) {
	//check if item exists in user inventory
	if (!characterController.characterHasItem(username, itemName)) {
		Response userResponse = Response("Item name " + itemName + " does not exist for you to wear.", username);
		return formulateResponse(userResponse);
	}

    //check if character is already wearing this item
    if (characterController.characterIsWearingItem(username, itemName)) {
    	Response userResponse = Response("You are already wearing this item!", username);
        return formulateResponse(userResponse);
    }

    //obtain item through input
    Object item = objectController.getObjectFromListByName(itemName);

    //wear item
    if (!characterController.characterWearItem(username, item)) {
        Response userResponse = Response("Wearing " + item.getName() + " has failed!", username);
        return formulateResponse(userResponse);
    }

    Response userResponse = Response("Wearing " + item.getName() + " succesfully!", username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::takeOff(Name username, Input itemName) {
	//obtain item through input
    Object item = objectController.getObjectFromListByName(itemName);

    //check if character is already wearing this item
    if (!characterController.characterIsWearingItem(username, item.getID())) {
    	Response userResponse = Response("You don't have this item equipped!", username);
        return formulateResponse(userResponse);
    }

    if (!characterController.characterRemoveItem(username, item)) {
        Response userResponse = Response("Taking off " + item.getName() + " has failed!", username);
        return formulateResponse(userResponse);
    	
    }

    Response userResponse = Response("Took off " + item.getName() + " succesfully!", username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::inventory(Name username, Input message) {
    //get the string containing inventory listed numerically
    std::string inventoryList = characterController.characterListInventory(username);

    //check if inventory is empty or not
    if(inventoryList.empty()) {
        Response userResponse = Response("Your inventory is empty!", username);
        return formulateResponse(userResponse);
    }

    Response userResponse = Response("Your inventory has: \n" + inventoryList, username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::swap(Name username, Name target) {
    //check if target is valid
    if(!characterController.doesCharacterExist(target)){
        Response userResponse = Response("The target does not exist!", username);
    }

    // swap spell
    characterController.swapCharacters(username, target);

    Response userResponse = Response("Successfully swapped!", username);
    Response targetResponse = Response("A swap spell was cast on you!", target);

    return formulateResponse(userResponse, targetResponse);
}

std::vector<Response>
GameController::formulateResponse(Response &userResponse, std::vector<Name> characterList, Input message)
{
    std::vector<Response> response;

    for(auto &character : characterList){
        if(character == userResponse.username){
            continue;
        }
        response.emplace_back(message, character);
    }

    response.push_back(userResponse);
    return response;
}

std::vector<Response> GameController::formulateResponse(Response &userResponse, Response &targetResponse) {

    std::vector<Response> response;

    response.push_back(userResponse);
    response.push_back(targetResponse);

    return response;
}

std::vector<Response> GameController::formulateResponse(Response &userResponse) {
    return formulateResponse(userResponse, std::vector<std::string>{}, std::string{});
}

bool GameController::directionExists(std::string direction) {
    return directionMap.find(direction) != directionMap.end();
}
