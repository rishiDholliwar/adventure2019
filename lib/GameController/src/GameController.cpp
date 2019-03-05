#include "GameController.h"
#include <Character.h>
#include <iostream>
#include <GameController.h>
#include <Utility.h>
#include <pigLatin.h>

using ASDirection::directionMap;

GameController::GameController()
{
    this->characterController = CharacterController();
    this->objectController = ObjectController();
}

bool GameController::loadCharacter(Name username) {
    return characterController.addCharacter(username, roomController, objectController);
}

bool GameController::removeCharacter(Name username) {
	Name charName = characterController.getCharacter(username).getName();
    return characterController.removeCharacter(charName);
}

std::vector<Response> GameController::info(Name username, Input message) {
    Name charName = characterController.getCharacter(username).getName();
    Response userResponse = Response(characterController.getCharacterInfo(username), username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::say(Name username, Input message) {
    std::cout << "Say " << message << std::endl;
    Name charName = characterController.getCharacter(username).getName();

    Response userResponse = Response("Me: " + message, username);
    std::cout << "within gc say, username: " + username << std::endl;
    // std::string genericMessage = username + ": "+ message;
    std::string genericMessage = charName + ": "+ message;
    std::cout << genericMessage << std::endl;

    return formulateResponse(userResponse, roomController.getUsernameList(characterController.getCharacterRoomID(username)), genericMessage);
}

std::vector<Response> GameController::whisper(Name username, Input inputs) {
    std::vector<std::string> inputStrings = utility::popFront(inputs);

    //check if user input format is incorrect
    if (inputStrings.size() != 2) {
        Response userResponse = Response("You must type in the {username of the character you wish to message}, {message}", username);
        return formulateResponse(userResponse);
    }

    Name charName = characterController.getCharacter(username).getName();
    Name targetCharName = characterController.getCharacter(inputStrings.at(0)).getName();

    //if whisper target character is not currently logged in
    if (!characterController.doesCharacterExist(inputStrings.at(0))) {
        Response userResponse = Response(inputStrings.at(0) + ": is not currently logged in", username);
        return formulateResponse(userResponse);
    }

    Response userResponse = Response("To [" + targetCharName + "]: " + inputStrings.at(1), username);
    Response targetResponse = Response("From [" + charName + "]: " + inputStrings.at(1), inputStrings.at(0));

    return formulateResponse(userResponse, targetResponse);
}

std::vector<Response> GameController::broadcast(Name username, Input message) {
    std::cout << "Broadcast " << message << std::endl;

    std::vector<std::string> broadcast = characterController.getAllCharacterNames();

    Name charName = characterController.getCharacter(username).getName();

    Response userResponse = Response("Me: " + message, username);
    std::string genericMessage = charName + ": " + message;

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

    Name charName = characterController.getCharacter(username).getName();

    // Update roomList to account for character moving
    roomController.removeUserNameFromRoom(charName, characterController.getCharacterRoomID(username));
    roomController.addUserNameToRoom(charName, destinationRoomID);
    characterController.setCharacterRoomID(username, destinationRoomID);

    Response userResponse = Response("Headed " + direction, username);
    std::string genericMessage = charName + " headed " + direction;
    return formulateResponse(userResponse, userList, genericMessage);
}

std::vector<Response> GameController::pickUp(Name username, Input itemName) {
    std::cout << "Pick Up: " << itemName << std::endl;

    if(!objectController.doesObjectOfThisNameExist(itemName)){
        Response userResponse = Response("This item does not exist!", username);
        return formulateResponse(userResponse);
    }

    // // Obtain item through input
    // Object item = objectController.getObjectFromListByName(itemName);

    Object item = Object("Basic Sword");


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

    if(!objectController.doesObjectOfThisNameExist(itemName)){
        Response userResponse = Response("This item does not exist!", username);
        return formulateResponse(userResponse);
    }

    // Verify if the character has item
    if(!characterController.characterHasItem(username, itemName)) {
        Response userResponse = Response("You don't have this item in your inventory!", username);
        return formulateResponse(userResponse);
    }

    ID itemID = characterController.getItemIDFromCharacterInventory(username, itemName);

    // Remove item from character's inventory
    characterController.dropItemFromCharacterInventory(username, itemID);

    Name charName = characterController.getCharacter(username).getName();

    // Add item to room's item List
    roomController.addObjectToRoom(itemID, characterController.getCharacterRoomID(charName));

    Response userResponse = Response("You dropped " + itemName + " in the room!", username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::give(Name username, Input message) {
	std::vector<std::string> inputStrings = utility::popFront(message);

	//check if user input format is incorrect
	if (inputStrings.size() != 2) {
		Response userResponse = Response("You must type in the {username of the character you wish to gift to}, {item name}", username);
		return formulateResponse(userResponse);
	}

    Name targetUserName = inputStrings.at(0);
    Name targetCharName = characterController.getCharacter(targetUserName).getName();
    Name charName = characterController.getCharacter(username).getName();
    Name giftName = inputStrings.at(1);

	//if gift target character doesn't exist
	if (!characterController.doesCharacterExist(targetUserName)) {
		Response userResponse = Response("Character name " + targetUserName + " does not exist for you to gift to.", username);
		return formulateResponse(userResponse);
	}

	//check if gift item exists in user inventory
	if (!characterController.characterHasItem(username, giftName)) {
		Response userResponse = Response("Item name " + giftName + " does not exist for you to give.", username);
		return formulateResponse(userResponse);
	}

	ID giftID = characterController.getItemIDFromCharacterInventory(username, giftName);

	//drop item from user inventory
	if (!characterController.dropItemFromCharacterInventory(username, giftID)) {
        Response userResponse = Response("Gifting item has failed.", username);
        return formulateResponse(userResponse);
    }

    Name targetCharacterName;

    if (targetUserName != targetCharName) {
    	targetCharacterName = targetCharName;
    } else {
    	targetCharacterName = targetUserName;
    }

	//add item to target user inventory
	characterController.addItemToCharacterInventory(targetCharacterName, objectController.getObjectFromList(giftID));

	if (!characterController.characterHasItem(targetCharacterName, giftID)) {
        characterController.addItemToCharacterInventory(username, objectController.getObjectFromList(giftID));
		Response userResponse = Response("Giving " + giftName + " to character " + targetUserName + " has failed.", username);
		return formulateResponse(userResponse);
	}

	//generate response
	Response userResponse = Response("You have given " + giftName + " to character " + targetUserName + "!", username);
    Response targetResponse = Response(username + " has given " + giftName + " to you!", targetUserName);
	return formulateResponse(userResponse, targetResponse);

}

std::vector<Response> GameController::wear(Name username, Input itemName) {
	//check if item exists in user inventory
	if (!characterController.characterHasItem(username, itemName)) {
		Response userResponse = Response("Item name " + itemName + " does not exist for you to wear.", username);
		return formulateResponse(userResponse);
	}

    //obtain item through input
    ID itemID = characterController.getItemIDFromCharacterInventory(username, itemName);

    //wear item
    if (!characterController.characterWearItem(username, itemName)) {
        Response userResponse = Response("Wearing " + itemName + " has failed!", username);
        return formulateResponse(userResponse);
    }

    Response userResponse = Response("Wearing " + itemName + " succesfully!", username);
    return formulateResponse(userResponse);
}

std::vector<Response> GameController::takeOff(Name username, Input itemName) {

    //check if character is already wearing this item
    if (!characterController.characterIsWearingItem(username, itemName)) {
    	Response userResponse = Response("You don't have this item equipped!", username);
        return formulateResponse(userResponse);
    }

    ID itemID = characterController.getItemIDFromCharacterWearing(username, itemName);

    if (!characterController.characterRemoveItem(username, objectController.getObjectFromList(itemID))) {
        Response userResponse = Response("Taking off " + itemName + " has failed!", username);
        return formulateResponse(userResponse);
    	
    }

    Response userResponse = Response("Took off " + itemName + " succesfully!", username);
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
    
    // // swap spell
    // characterController.swapCharacters(username, target);
    if (!characterController.doesCharacterExist(username)) {
        Response userResponse = Response("Apparently you don't exist???!", username);

        return formulateResponse(userResponse);
    }

    if (!(characterController.findCharacter(target))) {
    	//  || npcController.findNPC(target)
        Response userResponse = Response("Target doesn't exist, sorry!", username);

        return formulateResponse(userResponse);
    }

    if (characterController.findCharacter(target)) {

        characterController.swapCharacter(username, target);

        Response userResponse = Response("Successfully swapped!", username);
        Response targetResponse = Response("A swap spell was cast on you!", target);

        return formulateResponse(userResponse, targetResponse);
    
    // } else if (npcController.findNPC(target)) {
        
    //     ID NPCID = npcController.findNPCID(target);
    //     npcController.swapNPC(characterController.getCharacter(username).getID(), NPCID);
    //     characterController.swapCharacter(target, username);

    //     Response userResponse = Response("Successfully swapped!", username);
    //     Response targetResponse = Response("A swap spell was cast on you!", target);

    //     return formulateResponse(userResponse, targetResponse);

    } else {
        Response userResponse = Response("Swap failed!", username);

        return formulateResponse(userResponse);
    }

    Response userResponse = Response("Swap failed!", username);
    Response targetResponse = Response("Swap failed!", target);

    return formulateResponse(userResponse, targetResponse);
}

std::vector<Response> GameController::confuse(Name username, Input target) {
    // confuse spell
    characterController.confuseCharacter(target);

    Response userResponse = Response("Successfully confused!", username);
    Response targetResponse = Response("A confuse spell was cast on you!", target);

    return formulateResponse(userResponse, targetResponse);
}

std::vector<Response> GameController::formulateResponse(Response &userResponse, std::vector<Name> characterList, Input message) {
    std::vector<Response> response;

    for(auto &character : characterList){
        if(character == userResponse.username){
            continue;
        }
        if(characterController.isCharacterConfused(character)) {
            response.emplace_back(translate(message), character);
        } else {
            response.emplace_back(message, character);
        }
    }

    if(characterController.isCharacterConfused(userResponse.username)){
        userResponse.message = translate(userResponse.message);
        response.push_back(userResponse);
    } else {
        response.push_back(userResponse);
    }
    
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
