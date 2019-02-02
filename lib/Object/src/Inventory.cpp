//
// Created on 1/24/2019.
//

#include <vector>
#include <iostream>
#include "../include/Inventory.h"
#include "../include/Object.h"

void Inventory::addItem(Object object) {
    list.push_back(object);
}

void Inventory::listInventory() {
    for(Object obj : list){
        obj.printTest();
    }
}