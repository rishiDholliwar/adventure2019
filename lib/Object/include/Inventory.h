//
// Created on 1/24/2019.
//

#ifndef ALTERSPACE_INVENTORY_H
#define ALTERSPACE_INVENTORY_H

#include <vector>
#include <map>
#include "Object.h"
/*
 * Inventory
 * An inventory holds a list of objects
 */
class Inventory {
private:
    std::map<std::string,Object> list;
public:
    void addItem(Object object);
    void removeItem(std::string);

    /*
     * TEST FUNCTIONS
     */
    void listInventory();
    void printNumberOfItems();
};


#endif //ALTERSPACE_INVENTORY_H
