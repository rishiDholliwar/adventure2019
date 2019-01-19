//
// Created by bshetty on 1/18/19.
//

#include "Equip.h"

Equip::Equip(const Item &equippedItem) : equippedItem(equippedItem) {}

const Item &Equip::getEquippedItem() const {
    return equippedItem;
}

void Equip::setEquippedItem(const Item &equippedItem) {
    Equip::equippedItem = equippedItem;
}

Equip::~Equip() {

}




