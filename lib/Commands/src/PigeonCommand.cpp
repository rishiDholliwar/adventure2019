#include <GameCommands.h>
#include <CharacterController.h>

#include <iostream>
#include <Utility.h>
#include <sstream>

//PigeonMail
std::pair<std::vector<Response>, bool> PigeonMail::execute() {
    std::vector<std::string> inputStrings = utility::popFront(input);
    auto roomID = characterController->getCharacterRoomID(username);
    std::string subcommand = inputStrings.at(0);
    if( subcommand == "deliver" ) {
        std::vector<std::string> inputs = utility::tokenizeString(inputStrings.at(1));
        auto itr = inputs.begin();
        for( ; itr != inputs.end(); itr++ ) {
            // auto possibleUserVector(inputs.begin(), itr);
            // auto possibleItemVector(itr, inputs.end());
            auto possibleName = boost::algorithm::join(std::vector(inputs.begin(), itr), " ");
            auto possibleItem = boost::algorithm::join(std::vector(itr, inputs.end()), " ");
            auto usernames = characterController->getUsernamesOfCharacter(possibleName);
            if( objectController->doesObjectOfThisNameExist(possibleItem) && !usernames.empty()){

            }
            else {
                continue;
            }
        }



        Character pigeon("Pigeon", roomID);
        auto pigeonUniqueID = pigeon.getID();
        std::string pigeonName = "Pigeon#" + std::to_string(pigeonUniqueID);
        pigeon.setName(pigeonName);
        pigeonUsername = characterController->addNPC(pigeon);
    }
    else if( subcommand == "status" ) {

    }
    else {

    }

    std::cout << "Say " << input << std::endl;
    Name charName = characterController->getCharName(username);

    Response userResponse = Response("Me: " + input, username);

    std::string genericMessage = charName + ": "+ input;
    std::cout << genericMessage << std::endl;

    auto res = formulateResponse(userResponse,
                                 roomController->getCharacterList(characterController->getCharacterRoomID(username)), genericMessage);
    return std::make_pair(res, true);
}

std::pair<std::vector<Response>, bool> PigeonMail::callback() {
    registerCallback = true;
    callbackAfterHeartbeats = 150;
}

std::unique_ptr<Command> PigeonMail::clone(Name username, Input input, Connection connection = Connection{}) const {
    auto pm = std::make_unique<PigeonMail>(this->characterController, this->roomController, username, input);
    return std::move(pm);
}

std::unique_ptr<Command> PigeonMail::clone() const {
    auto pm = std::make_unique<PigeonMail>(this->characterController, this->roomController, this->username, this->input);
    return std::move(pm);
}

std::string PigeonMail::help() {
    return "/PigeonMail";
}
