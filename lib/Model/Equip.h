//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_EQUIP_H
#define ALTERSPACE_EQUIP_H


#include "Item.h"

class Equip {

private:

    Item equippedItem;


public:

    explicit Equip(const Item &equippedItem);

    const Item &getEquippedItem() const;

    void setEquippedItem(const Item &equippedItem);

    virtual ~Equip();


};


#endif //ALTERSPACE_EQUIP_H
