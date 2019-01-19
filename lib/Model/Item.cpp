//
// Created by bshetty on 1/18/19.
//

#include "Item.h"

Item::Item(const ItemInfo &itemInfo, const ItemStats &itemStats) : itemInfo(itemInfo), itemStats(itemStats) {}

Item::~Item() {

}

const ItemInfo &Item::getItemInfo() const {
    return itemInfo;
}

const ItemStats &Item::getItemStats() const {
    return itemStats;
}

bool Item::isWeapon(Item &item) {
    return item.getItemInfo().getItemType() == "WEAPON";
}

bool Item::isArmor(Item &item) {
    return item.getItemInfo().getItemType() == "ARMOR";
}




