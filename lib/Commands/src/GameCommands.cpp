#include <GameCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>

//Say
std::pair<std::vector<Response>, bool> Say::execute() {
    std::cout << "Say " << input << std::endl;
    Name charName = characterController->getCharacter(username).getName();

    Response userResponse = Response("Me: " + input, username);

    std::string genericMessage = charName + ": "+ input;
    std::cout << genericMessage << std::endl;

    auto res = formulateResponse(userResponse, roomController->getUsernameList(characterController->getCharacterRoomID(username)), genericMessage);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Say::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto say = std::make_unique<Say>(this->characterController, this->roomController, username, input);
    return std::move(say);
}

std::unique_ptr<Command> Say::clone() const {
    auto say = std::make_unique<Say>(this->characterController, this->roomController, this->username, this->input);
    return std::move(say);
}

std::string Say::help() {
    return "/say [message] - sends message to other players in the room";
}


// tell
std::pair<std::vector<Response>, bool> Tell::execute() {
    std::vector<std::string> inputStrings = utility::popFront(target);

    //check if user input format is incorrect
    if (inputStrings.size() != 2 || target.empty()) {
        Response userResponse = Response(help(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    Name charName = characterController->getCharacter(username).getName();
    Name targetCharName = inputStrings.at(TARGET_CHARACTER_NAME);
    Name targetUserName = characterController->getUsernameOfCharacter(targetCharName);

    //if tell target character is not currently logged in
    if (!characterController->doesCharacterExist(targetUserName)) {
        Response userResponse = Response(targetCharName + ": is not currently logged in", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    std::string message = inputStrings.at(MESSAGE);

    Response userResponse = Response("To [" + targetCharName + "]: " + message, username);
    Response targetResponse = Response("From [" + charName + "]: " + message, targetUserName);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Tell::clone(Name username, Input target, Connection connection = Connection{}) const {
    auto tell = std::make_unique<Tell>(this->characterController, username, target);
    return std::move(tell);
}

std::unique_ptr<Command> Tell::clone() const {
    auto tell = std::make_unique<Tell>(this->characterController, this->username, this->target);
    return std::move(tell);
}

std::string Tell::help() {
    return "/tell [target] [message] - Send a message to a specific player in the world";
};



// whisper
std::pair<std::vector<Response>, bool> Whisper::execute() {
    std::vector<std::string> inputStrings = utility::popFront(input);

    if (input.empty() || inputStrings.size() != 2) {
        Response userResponse = Response(help(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    Name charName = characterController->getCharacter(username).getName();
    Name targetCharName = inputStrings.at(TARGET_CHARACTER_NAME);
    Name targetUserName = characterController->getUsernameOfCharacter(targetCharName);

    //if tell target character is not currently logged in
    if (!characterController->doesCharacterExist(targetUserName)) {
        Response userResponse = Response(targetCharName + ": is not currently logged in", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }



    std::string message = inputStrings.at(MESSAGE);

    Response userResponse = Response("To [" + targetCharName + "]: " + message, username);
    Response targetResponse = Response("From [" + charName + "]: " + message, targetUserName);
    std::string modifiedMessage = "From [" + charName + "] to [ " + targetCharName + " ]: " + whisperModifier(message);

    Response empty = Response();
    std::vector<std::string> characterList = roomController->getUsernameList(characterController->getCharacterRoomID(charName));
    removeTargets(characterList, username, targetUserName);

    auto res = formulateResponse(userResponse, targetResponse);
    auto resModified = formulateResponse(empty, characterList, modifiedMessage);

    res.insert(res.end(), resModified.begin(), resModified.end());

    return std::make_pair(res, true);
}

std::unique_ptr<Command> Whisper::clone() const {
    auto whisper = std::make_unique<Whisper>(this->characterController, this->roomController, this->username, this->input);
    return std::move(whisper);
}

std::unique_ptr<Command> Whisper::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto whisper = std::make_unique<Whisper>(this->characterController, this->roomController, username, input);
    return std::move(whisper);
}

std::string Whisper::help() {
    return "/whisper [target] [message] - Send a message to a specific player in the world ... but beware of prying ears";
}

void Whisper::removeTargets(std::vector<std::string> &characterList, Name username, Name targetName) {
    characterList.erase(
            std::remove_if(characterList.begin(), characterList.end(),
                           [username, targetName](const std::string &character) { return (character == username) || (character == targetName); }),
            characterList.end());
}

//DisplayInventory
std::pair<std::vector<Response>, bool> DisplayInventory::execute() {
	std::cout << "Inventory " << std::endl;

	//get the string containing inventory listed numerically
    std::string inventoryList = characterController->characterListInventory(username);

    //check if inventory is empty or not
    if(inventoryList.empty()) {
        Response userResponse = Response("Your inventory is empty!", username);
        auto res = formulateResponse(userResponse);

    	return std::make_pair(res, true);
    }

    Response userResponse = Response("Your inventory has: \n" + inventoryList, username);
    auto res = formulateResponse(userResponse);

    return std::make_pair(res, true);
}

std::unique_ptr<Command> DisplayInventory::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto inventory = std::make_unique<DisplayInventory>(this->characterController, username, input);
    return std::move(inventory);
}

std::unique_ptr<Command> DisplayInventory::clone() const {
    auto inventory = std::make_unique<DisplayInventory>(this->characterController, this->username, this->input);
    return std::move(inventory);
}

std::string DisplayInventory::help() {
    return "/inventory - displays your inventory";
}

//Give
std::pair<std::vector<Response>, bool> Give::execute() {
	std::vector<std::string> inputStrings = utility::popFront(input);

    Name targetCharName = inputStrings.at(TARGET_CHARACTER_NAME);
    Name giftName = inputStrings.at(GIFT_NAME);

	//check if user input format is incorrect
	if (targetCharName.empty() || giftName.empty()) {
		Response userResponse = Response("You must type in the {username of the character you wish to gift to}, {item name}", username);
		auto res = formulateResponse(userResponse);
		return std::make_pair(res, false);
	}

	if ((inputStrings.at(CHECK_INTERACT) == "interact") && !(interactions.empty())) {
		return this->interact();
	}

    Name targetUserName = characterController->getCharacter(targetCharName).getName();
    Name charName = characterController->getCharacter(username).getName();

	//if gift target character doesn't exist
	if (!characterController->doesCharacterExist(targetUserName)) {
		Response userResponse = Response("Character name " + targetCharName + " does not exist for you to gift to.", username);
		auto res = formulateResponse(userResponse);
		return std::make_pair(res, false);
	}

	//check if gift item exists in user inventory
	if (!characterController->characterHasItem(username, giftName)) {
		Response userResponse = Response("Item name " + giftName + " does not exist for you to give.", username);
		auto res = formulateResponse(userResponse);
		return std::make_pair(res, false);
	}

	std::vector<Object> giftItems = characterController->getItemsFromCharacterInventory(username, giftName);

	if (giftItems.size() > MULTIPLE_ITEMS) {
		interactions = giftItems;
		interactTarget = targetCharName;

		std::stringstream ss;

		ss << "You have more than 1 item named " << giftName << ". Which item would you like to give?\n";

		int counter = 0;
		for (auto &obj : interactions) {
			ss << "\t" << ++counter << ". " << obj.getName() << ", ID: " << obj.getID() << "\n";
		}

		Response userResponse = Response(ss.str(), username);
		auto res = formulateResponse(userResponse);
		return std::make_pair(res, false);
	}

	ID giftID = characterController->getItemIDFromCharacterInventory(username, giftName);

	//drop item from user inventory
	if (!characterController->dropItemFromCharacterInventory(username, giftID)) {
        Response userResponse = Response("Gifting item has failed.", username);
        auto res = formulateResponse(userResponse);
		return std::make_pair(res, false);
    }

	//add item to target user inventory
	characterController->addItemToCharacterInventory(targetUserName, objectController->getObjectFromList(giftID));

	if (!characterController->characterHasItem(targetUserName, giftID)) {
        characterController->addItemToCharacterInventory(username, objectController->getObjectFromList(giftID));
		Response userResponse = Response("Giving " + giftName + " to character " + targetCharName + " has failed.", username);
		auto res = formulateResponse(userResponse);
		return std::make_pair(res, false);
	}

	//generate response
	Response userResponse = Response("You have given " + giftName + " to character " + targetCharName + "!", username);
    Response targetResponse = Response(username + " has given " + giftName + " to you!", targetUserName);
	auto res = formulateResponse(userResponse, targetResponse);

	return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Give::interact() {
    std::cout << "give interacting" << std::endl;

    std::vector<std::string> v = utility::tokenizeString(input);

    if ( v.size() != 2 ) {
    	std::cout << "Too many arguments..." << std::endl;
    	Response userResponse = Response("Please enter /give interact {index number of the item you wish to give}.", username);
    	auto res = formulateResponse(userResponse);

    	return std::make_pair(res, false);
    }

    std::stringstream ss{v.at(INTERACT_CHOICE)};
    int index = -1;
    ss >> index;
    index--;
    if ( index >= interactions.size() || index < 0 ) {
        Response userResponse = Response("Please enter /give interact {index number of the item you wish to give}.", username);
    	auto res = formulateResponse(userResponse);

    	return std::make_pair(res, false);
    }

    ID giftID = interactions.at(index).getID();
    Name giftName = interactions.at(index).getName();

    Name interactTargetUsername = characterController->getUsernameOfCharacter(interactTarget);
    Name charName = characterController->getCharacter(username).getName();

	//drop item from user inventory
	if (!characterController->dropItemFromCharacterInventory(username, giftID)) {
        Response userResponse = Response("Gifting item has failed.", username);
        auto res = formulateResponse(userResponse);
		return std::make_pair(res, false);
    }

	//add item to target user inventory
	characterController->addItemToCharacterInventory(interactTargetUsername, objectController->getObjectFromList(giftID));

	if (!characterController->characterHasItem(interactTargetUsername, giftID)) {
        characterController->addItemToCharacterInventory(username, objectController->getObjectFromList(giftID));
		Response userResponse = Response("Giving " + giftName + " to character " + interactTarget + " has failed.", username);
		auto res = formulateResponse(userResponse);
		return std::make_pair(res, false);
	}

	//generate response
	Response userResponse = Response("You have given " + giftName + " to character " + interactTarget + "!", username);
    Response targetResponse = Response(charName + " has given " + giftName + " to you!", interactTargetUsername);
	auto res = formulateResponse(userResponse, targetResponse);

	return std::make_pair(res, true);
}


std::unique_ptr<Command> Give::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto give = std::make_unique<Give>(this->characterController, this->objectController, username, input);
    give->setInteractions(this->interactions, this->interactTarget);
    return std::move(give);
}

std::unique_ptr<Command> Give::clone() const {
    auto give = std::make_unique<Give>(this->characterController, this->objectController, this->username, this->input);
    give->setInteractions(this->interactions, this->interactTarget);
    return std::move(give);
}

std::string Give::help() {
    return "/give [target's character name] [item name] - give item to a player";
}

void Give::setInteractions(std::vector<Object> i, Name interactT) {
    interactions = i;
    interactTarget = interactT;
}

// Confuse
std::pair<std::vector<Response>, bool> Confuse::execute(){

    if(target.empty()) {
        Response userResponse(help(), username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    //if tell target character is not currently logged in
    if (!characterController->doesCharacterExist(target)) {
        Response userResponse = Response(target + ": is not currently logged in", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    Name targetUserName = characterController->getUsernameOfCharacter(target);
    
    characterController->confuseCharacter(targetUserName);

    Response userResponse = Response("Successfully confused!", username);
    Response targetResponse = Response("A confuse spell was cast on you!", targetUserName);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Confuse::callback(){

    Name targetUserName = characterController->getUsernameOfCharacter(target);

    characterController->confuseCharacter(targetUserName);

    Response userResponse = Response("Your target is no longer confused", username);
    Response targetResponse = Response("You are no longer confused", targetUserName);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);

}

std::unique_ptr<Command> Confuse::clone() const {
    auto confuse = std::make_unique<Confuse>(this->characterController, this->roomController, this->username, this->target);
    return std::move(confuse);
}

std::unique_ptr<Command> Confuse::clone(Name username, Input target, Connection connection) const {
    auto confuse = std::make_unique<Confuse>(this->characterController, this->roomController, username, target);
    return std::move(confuse);
}

std::string Confuse::help(){
    return "/confuse [target] - confuses a target and they see weird things";
}

//Swap
std::pair<std::vector<Response>, bool> Swap::execute() {

    if (target.empty()) {
        Response userResponse = Response(help(), username);

        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    if (!(characterController->findCharacter(target))) {

        Response userResponse = Response("Target doesn't exist, sorry!", username);

        auto res = formulateResponse(userResponse);
        return std::make_pair(res, false);
    }

    Name userKey = username;
    Name targetKey = characterController->getCharacter(username).getName();

    if ((userKey != targetKey) && (targetKey == target) && (userKey == characterController->getCharacter(targetKey).getName())) {

        Response userResponse = Response("You are already under a swap spell!", userKey);
        Response targetResponse = Response("You are already under a swap spell!", targetKey);

        auto res = formulateResponse(userResponse, targetResponse);
        return std::make_pair(res, true);
    }

    characterController->swapCharacter(username, target);

    Response userResponse = Response("Successfully swapped!", username);
    Response targetResponse = Response("A swap spell was cast on you!", target);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> Swap::callback() {
    Name userKey = username;
    Name targetKey = characterController->getCharacter(username).getName();

    if ((userKey != targetKey) && (targetKey == target) && (userKey == characterController->getCharacter(targetKey).getName())) {

        Name targetCharName = characterController->getCharacter(username).getName();

        characterController->swapCharacter(userKey, targetKey);

        Response userResponse = Response("Successfully unswapped!", userKey);
        Response targetResponse = Response("You have been successfully unswapped!", targetKey);

        auto res = formulateResponse(userResponse, targetResponse);
        return std::make_pair(res, true);

    }

    Response userResponse = Response("You are not under a swap spell", userKey);
    Response targetResponse = Response("You are not under a swap spell", target);

    auto res = formulateResponse(userResponse, targetResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Swap::clone(Name username, Input target, Connection connection = Connection{}) const {
    auto swap = std::make_unique<Swap>(this->characterController, username, target);
    return std::move(swap);
}

std::unique_ptr<Command> Swap::clone() const {
    auto swap = std::make_unique<Swap>(this->characterController, this->username, this->target);
    return std::move(swap);
}

std::string Swap::help() {
    return "/swap [target username] - swap with the target character with this username";
}

