//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_ITEM_H
#define ALTERSPACE_ITEM_H


#include "ItemInfo.h"
#include "ItemStats.h"

class Item {

private:
    ItemInfo itemInfo;
    ItemStats itemStats;

public:

    Item(const ItemInfo &itemInfo, const ItemStats &itemStats);

    const ItemInfo &getItemInfo() const;

    const ItemStats &getItemStats() const;

    bool isWeapon(Item &item);

    bool isArmor(Item &item);

    virtual ~Item();


};


#endif //ALTERSPACE_ITEM_H
