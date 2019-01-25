//
// Created by bshetty on 1/18/19.
//

#include <iostream>
#include "../include/CharacterController.h"

CharacterController::CharacterController() = default;

bool CharacterController::levelUpCharacter(Character &character) {
    if(character.canLevelUp()){
        character.levelUp();
        std::cout << "Player: " << character.getUserName() << " has successfully levelled up!" << std::endl;

        // JSON is updated here for character->username (currently dummy JSON integration)
        std::cout << "...JSON is updated for: " << character.getUserName() <<  "..." << std::endl;

        return true;
    } else {
        return false;
    }
}

bool CharacterController::equipWeapon(Character &character, Item &item) {
    if(item.isWeapon(item)){
        if(character.equipNewWeapon(item)){
            std::cout << "Player: " << character.getUserName() << " has successfully equipped "<<
                      item.getItemInfo().getItemType() <<"!" << std::endl;

            // JSON is updated here for character->username (currently dummy JSON integration)
            std::cout << "...JSON is updated for: " << character.getUserName() <<  "..." << std::endl;

            return true;
        } else {
            std::cout << "There is no space left in your inventory! .... Equip FAILED" << std::endl;
            return false;
        }

    } else {
        std::cout << "The item you are trying to equip is not a weapon! .... Equip FAILED" << std::endl;
        return false;
    }

}

bool CharacterController::equipArmor(Character &character, Item &item) {
    if(item.isArmor(item)){
        if(character.equipNewArmor(item)){
            std::cout << "Player: " << character.getUserName() << " has successfully equipped "<<
                      item.getItemInfo().getItemType() <<"!" << std::endl;

            // JSON is updated here for character->username (currently dummy JSON integration)
            std::cout << "...JSON is updated for: " << character.getUserName() <<  "..." << std::endl;

            return true;
        } else {
            std::cout << "There is no space left in your inventory! .... Equip FAILED" << std::endl;
            return false;
        }

    } else {
        std::cout << "The item you are trying to equip is not an armor! .... Equip FAILED" << std::endl;
        return false;
    }
}




