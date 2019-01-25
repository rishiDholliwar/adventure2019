//
// Created by bshetty on 1/18/19.
//

#include <iostream>
#include <CharacterController.h>

#include "../include/CharacterController.h"

CharacterController::CharacterController() = default;

bool CharacterController::levelUpCharacter(Character &character) {
    if(character.canLevelUp()){
        character.levelUp();
        std::cout << "Player: " << character.getUserName() << " has successfully levelled up!" << std::endl;

        return true;
    } else {
        return false;
    }
}


bool CharacterController::updateRoomID(Character &character, unsigned int &destinationRoomID) {

    if(character.getRoomID() == destinationRoomID){
        return false;
    }else {
        character.setRoomID(destinationRoomID);
        return true;
    }
}

template<typename T>
bool CharacterController::addItemToInventory(Character &character, T &item) {
    if(!character.hasSpaceInInventory()){
        return false;
    }else{
        character.addItem(item);
        return true;
    }
}






