#include "GameController.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <Utility.h>
#include <memory>

GameController::GameController()
{

}

std::string GameController::say(std::string userName, std::string input)
{
    return userName+" says: "+input;
}
