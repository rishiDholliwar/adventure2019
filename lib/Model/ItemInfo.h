//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_ITEMINFO_H
#define ALTERSPACE_ITEMINFO_H


#include <string>

class ItemInfo {
private:
    std::string itemID;
    std::string itemType;
    std::string description;
    unsigned int pickupLocation;
    std::string currentOwner;
    unsigned int salePrice;


public:
    ItemInfo(const std::string &itemID, const std::string &itemType, const std::string &description,
             unsigned int pickupLocation, const std::string &currentOwner, unsigned int salePrice);

    const std::string &getDescription() const;

    unsigned int getPickupLocation() const;

    const std::string &getCurrentOwner() const;

    unsigned int getSalePrice() const;

    const std::string &getItemID() const;

    void setCurrentOwner(const std::string &currentOwner);

    const std::string &getItemType() const;

    virtual ~ItemInfo();

};


#endif //ALTERSPACE_ITEMINFO_H
