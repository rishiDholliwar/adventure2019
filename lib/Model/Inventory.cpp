//
// Created by bshetty on 1/18/19.
//

#include "Inventory.h"

Inventory::Inventory(unsigned int inventorySize, const std::vector<Item> &items) : inventorySize(inventorySize),
                                                                                   items(items) {}

unsigned int Inventory::getInventorySize() const {
    return inventorySize;
}

void Inventory::setInventorySize(unsigned int inventorySize) {
    Inventory::inventorySize = inventorySize;
}

const std::vector<Item> &Inventory::getItems() const {
    return items;
}

void Inventory::setItems(const std::vector<Item> &items) {
    Inventory::items = items;
}

Inventory::~Inventory() {

}

bool Inventory::hasSpace() {
    return items.size() < inventorySize;
}

void Inventory::store(const Equip &equip) {
    items.push_back(equip.getEquippedItem());
}
