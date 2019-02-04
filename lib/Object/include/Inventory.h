//
// Created on 1/24/2019.
//

#ifndef ALTERSPACE_INVENTORY_H
#define ALTERSPACE_INVENTORY_H

#include <vector>
#include "Object.h"
class Inventory {
private:
    std::vector<Object> objects;

public:
    Inventory();

    void addItem(Object object);

    void listInventory();

    bool doesItemExist(unsigned int objectId);

    void removeItem(unsigned int objectId);
};


#endif //ALTERSPACE_INVENTORY_H