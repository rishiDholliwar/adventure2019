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

std::vector<Response> GameController::say(Name username, Input message) {
    std::cout << "Say " << message << std::endl;

    Character character = characterController.getCharacter(username);

    Response userResponse = Response("Me: " + message, username);
    std::string genericMessage = username + ": "+ message;

    return formulateResponse(userResponse, roomController.getUsernameList(character.getRoomID()),genericMessage);
}

std::vector<Response> GameController::broadcast(Name username, Input message) {
    std::cout << "Broadcast " << message << std::endl;

    Character character = characterController.getCharacter(username);
    std::vector<std::string> broadcast = characterController.getAllCharacterNames();


    Response userResponse = Response("Me: " + message, username);
    std::string genericMessage = username + ": " + message;

    return formulateResponse(userResponse, broadcast ,genericMessage);
}

std::vector<Response> GameController::move(Name username, std::string direction) {
    std::cout << "Move: " << direction << std::endl;

    // Obtain character object based on userName (dummy)
    Character* character = &characterController.getCharacter(username);

    // check if direction exists
    if(!directionExists(direction)){
        Response userResponse = Response("There is no such direction!", username);
        return formulateResponse(userResponse);
    }

    // Verify if direction is valid
    unsigned int destinationRoomID = roomController.getLinkedRoom(directionMap.at(direction), character->getRoomID());
    if( destinationRoomID == 0){
        Response userResponse = Response("That isn't a valid direction!", username);
        return formulateResponse(userResponse);
    }

    // Update roomList to account for character moving
    roomController.removeUserNameFromRoom(character->getName(),character->getRoomID());
    roomController.addUserNameToRoom(character->getName(), destinationRoomID);
    character->setRoomID(destinationRoomID);

    Response userResponse = Response("Headed " + direction, username);
    std::string genericMessage = username + "headed " + direction;
    return formulateResponse(userResponse, roomController.getUsernameList(character->getRoomID()),genericMessage);
}

std::vector<Response> GameController::pickUp(Name username, std::string itemName) {
    std::cout << "Pick Up: " << itemName << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(username);

    if(!objectController.doesObjectExist(itemName)){
        Response userResponse = Response("This item does not exist!", username);
        return formulateResponse(userResponse);
    }

    // Obtain item through input
    Object item = objectController.getObjectFromListByName(itemName);


    if(!roomController.removeObjectFromRoom(item.getID(), character.getRoomID())) {
        Response userResponse = Response("This item does not exist in the room!", username);
        return formulateResponse(userResponse);
    }

    // Update room to no longer have the item (until the next reset)
    character.addItemToInventory(item);

    Response userResponse = Response(itemName + " added to inventory!", username);
    return formulateResponse(userResponse);


}

std::vector<Response> GameController::drop(Name username, std::string itemName) {
    std::cout << "Drop: " << itemName << std::endl;

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(username);

    if(!objectController.doesObjectExist(itemName)){
        Response userResponse = Response("This item does not exist!", username);
        return formulateResponse(userResponse);
    }
    //obtain item through input
    Object item = objectController.getObjectFromListByName(itemName);

    // Verify if the character has item
    if(!character.hasItem(item.getID())){
        Response userResponse = Response("You don't have this item in your inventory!", username);
        return formulateResponse(userResponse);
    }
    // Remove item from character's inventory
    character.dropItem(item.getID());

    // Add item to room's item List
    roomController.addObjectToRoom(item.getID(), character.getRoomID());

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

	//check user if user is logged in
	if (!characterController.doesCharacterExist(username)) {
		characterController.addCharacter(username, roomController);
	}

	//obtain user character object based on userName (dummy)
	Character userCharacter = characterController.getCharacter(username);

	//obtain gift target user character object based on userName
	Character targetCharacter = characterController.getCharacter(inputStrings.at(0));

	//check if gift item exists in user inventory
	if (!userCharacter.hasItemByName(inputStrings.at(1))) {
		Response userResponse = Response("Item name " + inputStrings.at(1) + " does not exist for you to give.", username);
		return formulateResponse(userResponse);
	}

	Object gift = userCharacter.getItemFromInventoryByName(inputStrings.at(1));

	//drop item from user inventory
	if (userCharacter.dropItem(gift.getID()) == false) {
        Response userResponse = Response("dropping failed for userChar", username);
        return formulateResponse(userResponse);
    }

    //test only:
    if (targetCharacter.dropItem(gift.getID()) == false) {
        Response userResponse = Response("dropping failed for targetChar", username);
        return formulateResponse(userResponse);
    }

    //test only:
    if (userCharacter.hasItem(gift.getID())) {
        Response userResponse = Response("userChar still has item", username);
        return formulateResponse(userResponse);
    }

    //test only:
    if (targetCharacter.hasItem(gift.getID())) {
        Response userResponse = Response("targetChar still has item", username);
        return formulateResponse(userResponse);
    }

	//add item to target user inventory
	targetCharacter.addItemToInventory(gift);

    bool giftSuccess = targetCharacter.hasItem(gift.getID());

	if (giftSuccess == false) {
		Response userResponse = Response("Giving " + inputStrings.at(1) + " to character " + inputStrings.at(0) + " has failed.", username);
		return formulateResponse(userResponse);
	}

	//generate response
	Response userResponse = Response("You have given " + inputStrings.at(1) + " to character " + inputStrings.at(0) + "!", username);
	return formulateResponse(userResponse);

}

std::vector<Response> GameController::wear(Name username, std::string itemName) {
	// check user if user is logged in
    if(!characterController.doesCharacterExist(username)){
        characterController.addCharacter(username, roomController);
    }

    //obtain user character object based on userName (dummy)
	Character character = characterController.getCharacter(username);

	//check if item exists in user inventory
	if (!character.hasItemByName(itemName)) {
		Response userResponse = Response("Item name " + itemName + " does not exist for you to wear.", username);
		return formulateResponse(userResponse);
	}

	//obtain item through input
    Object item = objectController.getObjectFromListByName(itemName);

    // Verify if the character has item
    if(!character.hasItem(item.getID())){
        Response userResponse = Response("You don't have this item in your inventory!", username);
        return formulateResponse(userResponse);
    }

    //check if character is already wearing this item
    if (character.isWearing(item.getID())) {
    	Response userResponse = Response("You are already wearing this item!", username);
        return formulateResponse(userResponse);
    }

    //wear item
    if (character.wear(item) == true) {
    	Response userResponse = Response("Wearing " + item.getName() + " succesfully!", username);
        return formulateResponse(userResponse);
    }

    Response userResponse = Response("Wearing " + item.getName() + " has failed!", username);
        return formulateResponse(userResponse);
}

std::vector<Response> GameController::takeOff(Name username, std::string itemName) {
	// check user if user is logged in
    if(!characterController.doesCharacterExist(username)){
        characterController.addCharacter(username, roomController);
    }

    //obtain user character object based on userName (dummy)
	Character character = characterController.getCharacter(username);

	//check if item exists in user inventory
	if (!character.hasItemByName(itemName)) {
		Response userResponse = Response("Item name " + itemName + " does not exist for you to wear.", username);
		return formulateResponse(userResponse);
	}

	//obtain item through input
    Object item = objectController.getObjectFromListByName(itemName);

    // Verify if the character has item
    if(!character.hasItem(item.getID())){
        Response userResponse = Response("You don't have this item in your inventory!", username);
        return formulateResponse(userResponse);
    }

    //check if character is already wearing this item
    if (character.isWearing(item.getID())) {
    	Response userResponse = Response("You are already wearing this item!", username);
        return formulateResponse(userResponse);
    }

    if (character.takeOff(item) == true) {
    	Response userResponse = Response("Took off " + item.getName() + " succesfully!", username);
        return formulateResponse(userResponse);
    }

    Response userResponse = Response("Taking off " + item.getName() + " has failed!", username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::inventory(Name username, Input message) {

    // Obtain character object based on userName (dummy)
    Character character = characterController.getCharacter(username);

    //get the string containing inventory listed numerically
    std::string inventoryList = character.listInventory();

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

    Character userCharacter = characterController.getCharacter(username);
    Character targetCharacter = characterController.getCharacter(target);

    // swap spell
    characterController.swapCharacters(userCharacter, targetCharacter);

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
