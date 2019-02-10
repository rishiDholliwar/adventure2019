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
     * Pre-Condition: ID of the item in question
     * Post:returns true if found
     *
     * */
    bool doesItemExist(ID objectID);

    /* Remove Item:
     *
     * Function: removes item from inventory
     *
     * Pre-Condition: the ID of the item in question
     * Post: will have removed the item from the inventory, returns true if removed
     *
     * */
    bool removeItem(ID objectID);

    /* List Inventory:
     *
     * Function: Lists Inventory to user
     *
     * Pre-Condition:
     * Post:
     *
     * */
    std::string listInventory();
};


#endif //ALTERSPACE_INVENTORY_H
