//
// Created on 1/24/2019.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <Inventory.h>
#include <Object.h>


Inventory::Inventory() { }

void Inventory::addItem(Object object) {
    objects.push_back(object);
}

std::string Inventory::listInventory() {

    if (objects.empty()) {
        return std::string();
    }

    int objectCount = 1;
    std::string inventoryList = "";

    for(Object obj : objects){
        std::string objectString = std::to_string(objectCount) + ". " + obj.getName() + "\n";
        inventoryList += objectString;

        objectCount++;
    }

    return inventoryList;
}

bool Inventory::doesItemExist(unsigned int objectId) {
    for(auto& object : objects){
        return object.getId() == objectId;
    }
    return false;
}

void Inventory::removeItem(unsigned int objectId) {
    auto it = find_if(objects.begin(), objects.end(), [objectId](Object const& obj)->bool{return obj.getId() == objectId;});

    if(it != objects.end()){
        objects.erase(it);
    }
}


