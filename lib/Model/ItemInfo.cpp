//
// Created by bshetty on 1/18/19.
//

#include "ItemInfo.h"

ItemInfo::ItemInfo(const std::string &itemID, const std::string &itemType, const std::string &description,
                   unsigned int pickupLocation, const std::string &currentOwner, unsigned int salePrice) : itemID(
        itemID), itemType(itemType), description(description), pickupLocation(pickupLocation), currentOwner(
        currentOwner), salePrice(salePrice) {}

const std::string &ItemInfo::getDescription() const {
    return description;
}

unsigned int ItemInfo::getPickupLocation() const {
    return pickupLocation;
}

const std::string &ItemInfo::getCurrentOwner() const {
    return currentOwner;
}

unsigned int ItemInfo::getSalePrice() const {
    return salePrice;
}

const std::string &ItemInfo::getItemID() const {
    return itemID;
}

void ItemInfo::setCurrentOwner(const std::string &currentOwner) {
    ItemInfo::currentOwner = currentOwner;
}

const std::string &ItemInfo::getItemType() const {
    return itemType;
}


ItemInfo::~ItemInfo() {

}






