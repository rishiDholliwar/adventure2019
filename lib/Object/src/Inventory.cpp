//
// Created on 1/24/2019.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <Inventory.h>
#include <Object.h>


Inventory::Inventory() = default;

void Inventory::addItem(Object object) {
    objects.push_back(object);
}

bool Inventory::doesItemExist(unsigned int objectID) {
    return find_if(objects.begin(), objects.end(),
                   [objectID](Object const& obj)->bool{return obj.getID() == objectID;}) != objects.end();
}

void Inventory::removeItem(unsigned int objectID) {
    auto it = find_if(objects.begin(), objects.end(), [objectID](Object const& obj)->bool{return obj.getID() == objectID;});
    objects.erase(it);
}

std::string Inventory::listInventory() {

    if (objects.empty()) {
        return std::string();
    }

    int objectCount = 1;
    std::string inventoryList;

    for(auto &obj : objects){

        std::string objectString = std::to_string(objectCount) + ". " + obj.getName() + "\n";
        inventoryList += objectString;

        objectCount++;
    }
    return inventoryList;
}
