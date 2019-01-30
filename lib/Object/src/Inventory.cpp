//
// Created on 1/24/2019.
//

#include <vector>
#include <iostream>
#include "../include/Inventory.h"
#include "../include/Object.h"

void Inventory::addItem(Object object) {
    this->list.insert(std::pair<std::string,Object>(object.getObjectName(),object));
}



void Inventory::listInventory() {
    if(list.empty()){
        printNumberOfItems();
        std::cout << "inventory is empty" << std::endl;
        return;
    }
    printNumberOfItems();
    for(auto const &obj : list){
        auto const &object = obj.second;
        object.printTest();
    }
}

void Inventory::printNumberOfItems(){
    std::cout << "Inventory size: " << list.size() << std::endl;
}

void Inventory::removeItem(std::string itemName) {
    if(list.find(itemName) == list.end()){
        //If item is in the inventory

    } else{
        //If item is not in the inventory
        list.erase(itemName);
    }
}
