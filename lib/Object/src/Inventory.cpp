//
// Created on 1/24/2019.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/Inventory.h"
#include "../include/Object.h"


Inventory::Inventory() {}

void Inventory::addItem(Object object) {
    objects.push_back(object);
}

void Inventory::listInventory() {
    for(Object obj : objects){
        //obj.printTest();
    }
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


