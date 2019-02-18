#ifndef ALTERSPACE_INVENTORY_H
#define ALTERSPACE_INVENTORY_H

#include <vector>
#include <string>

#include <AlterSpace.h>
#include "Object.h"

using AlterSpace::ID;

class Inventory {
private:
    std::vector<Object> objects;

    auto getItemIteratorByID(ID objectID);

    auto getItemIteratorByName(Name objectName);

public:
    Inventory();

    /* Add Item:
     *
     * Function: adds item to inventory
     *
     * Pre-Condition: the object to add
     * Post: will have added the item to inventory
     *
     * */
    void addItem(Object object);

    /* Does Item Exist:
     *
     * Function: Checks to see if user has such the item
     *
     * Pre-Condition: ID of the item to validate
     * Post: returns true if found
     *
     * */
    bool doesItemExist(ID objectID);

    /* Does Item Exist By Name:
     *
     * Function: Checks to see if user has such the item
     *
     * Pre-Condition: Name of the item to validate
     * Post: returns true if found
     *
     * */
    bool doesItemExistByName(Name objectName);

    /* Get Item By Name:
     *
     * Function: Checks to see if user has such the item and returns the item if true
     *
     * Pre-Condition: Name of the item to retrieve
     * Post: returns item if found
     *
     * */
    Object getItemByName(Name objectName);

    /* Remove Item:
     *
     * Function: removes item from inventory
     *
     * Pre-Condition: ID of the item to remove
     * Post: Removes the item from the inventory, returns true if removed successfully
     *
     * */
    bool removeItem(ID objectID);

    /* List Inventory:
     *
     * Function: Lists Inventory to user
     *
     * Pre-Condition: inventory has an iterable list of items
     * Post: Returns a list of objects in inventory
     *
     * */
    std::string listInventory();
};


#endif //ALTERSPACE_INVENTORY_H
