#include <GameCommands.h>
#include <iostream>
#include <Utility.h>
#include <sstream>

//Say
std::pair<std::vector<Response>, bool> Say::execute() {
    std::cout << "Say " << input << std::endl;
    Name charName = characterController->getCharacter(username).getName();

    Response userResponse = Response("Me: " + input, username);

    std::string genericMessage = charName + ": " + input;
    std::cout << genericMessage << std::endl;

    auto res = formulateResponse(userResponse,
                                 roomController->getUsernameList(characterController->getCharacterRoomID(username)),
                                 genericMessage);
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

//Swap
std::pair<std::vector<Response>, bool> Swap::execute() {

    if (target.empty()) {
        Response userResponse = Response(help(), username);

        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    if (!(characterController->findCharacter(target))) {

        Response userResponse = Response("Target doesn't exist, sorry!", username);

        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    Name userKey = username;
    Name targetKey = characterController->getCharacter(username).getName();

    if ((userKey != targetKey) && (targetKey == target) &&
        (userKey == characterController->getCharacter(targetKey).getName())) {

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

    if ((userKey != targetKey) && (targetKey == target) &&
        (userKey == characterController->getCharacter(targetKey).getName())) {

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

//todo this class could get big, maybe move these types of commands called SocialCommands
//Broadcast
std::pair<std::vector<Response>, bool> Broadcast::execute() {
    std::vector<std::string> broadcast = characterController->getAllCharacterNames();

    Response userResponse = Response("Me: " + input, username);
    std::string genericMessage = username + ": " + input;
    auto res = formulateResponse(userResponse, broadcast, genericMessage);

    return std::make_pair(res, true);
}

std::unique_ptr<Command> Broadcast::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<Broadcast>( this->characterController,
                                        username, input, connection);
}

std::unique_ptr<Command> Broadcast::clone() const {
    return std::make_unique<Broadcast>( this->characterController,
                                        this->username, this->input, this->connection);
}

std::string Broadcast::help() {
    return "/broadcast - sends messages to current and adjacent rooms";
}

//Drop
std::pair<std::vector<Response>, bool> Drop::execute() {
    Name itemName = input;
    if (!objectController->doesObjectOfThisNameExist(itemName)) {
        Response userResponse = Response("This item does not exist!", username);
       auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    // Verify if the character has item
    if (!characterController->characterHasItem(username, itemName)) {
        Response userResponse = Response("You don't have this item in your inventory!", username);
        auto res = formulateResponse(userResponse);
        return std::make_pair(res, true);
    }

    ID itemID = characterController->getItemIDFromCharacterInventory(username, itemName);

    // Remove item from character's inventory
    characterController->dropItemFromCharacterInventory(username, itemID);

    // Add item to room's item List
    roomController->addObjectToRoom(itemID, characterController->getCharacterRoomID(username));

    Response userResponse = Response("You dropped " + itemName + " in the room!", username);
    auto res = formulateResponse(userResponse);
    return std::make_pair(res, true);
}

std::unique_ptr<Command> Drop::clone(Name username, Input input, Connection connection = Connection{}) const {
    return std::make_unique<Drop>(this->userController, this->characterController, this->roomController, this->objectController, username, input, connection);
}

std::unique_ptr<Command> Drop::clone() const {
    return std::make_unique<Drop>(this->userController, this->characterController, this->roomController, this->objectController, this->username, this->input, this->connection);
}

std::string Drop::help() {
    return "/Drop - drop an item";
}