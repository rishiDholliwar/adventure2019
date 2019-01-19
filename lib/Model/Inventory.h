//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_INVENTORY_H
#define ALTERSPACE_INVENTORY_H


#include <vector>
#include "Item.h"
#include "Equip.h"

class Inventory {
private:
    unsigned int inventorySize;
    std::vector<Item> items;

public:
    Inventory(unsigned int inventorySize, const std::vector<Item> &items);

    unsigned int getInventorySize() const;

    void setInventorySize(unsigned int inventorySize);

    const std::vector<Item> &getItems() const;

    void setItems(const std::vector<Item> &items);

    virtual ~Inventory();

    bool hasSpace();

    void store(const Equip &equip);
};


#endif //ALTERSPACE_INVENTORY_H
