//
// Created on 1/24/2019.
//

#ifndef ALTERSPACE_INVENTORY_H
#define ALTERSPACE_INVENTORY_H

#include <vector>
#include "Object.h"
class Inventory {
private:
    std::vector<Object> list;
public:
    void addItem(Object object);


    /*
     * TEST FUNCTIONS
     */
    void listInventory();
};


#endif //ALTERSPACE_INVENTORY_H
