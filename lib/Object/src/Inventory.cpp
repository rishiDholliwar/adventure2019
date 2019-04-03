#include <algorithm>
#include <sstream>
#include <Inventory.h>

#include <iostream>
// #include <JSONObjects.h>

void Inventory::addItem(Object object) {
    objects.push_back(object);
}

std::vector<Object>::iterator Inventory::getItemIterator(ID objectID)
{
    auto it = find_if(objects.begin(), objects.end(),
                      [ objectID ] ( Object const& obj ) {
                          return objectID == obj.getID();
                        });

    return it;
}

bool Inventory::doesItemExist(ID objectID)
{
    return getItemIterator(objectID) != objects.end();
}

std::vector<Object>::iterator Inventory::getItemIterator(Name objectName)
{
    auto it = find_if(objects.begin(), objects.end(),
                      [ objectName ] ( Object const& obj )->bool {
                          return obj.getName() == objectName;
                        });

    return it;
}

bool Inventory::doesItemExist(Name objectName)
{

    return getItemIterator(objectName) != objects.end();
}

std::vector<Object> Inventory::getItems(Name& objectName)
{
    std::vector<Object> items;

    for (auto &obj : objects) {
        if (obj.getName() == objectName) {
            items.push_back(obj);
        }
    }

    return items;
}

Object Inventory::getItem(Name& objectName)
{

    auto it = getItemIterator(objectName);

    return *it;
}

Object Inventory::getItem(ID objectID)
{
    auto it = getItemIterator(objectID);

    return *it;
}

void Inventory::removeItem(ID objectID)
{
    auto it = getItemIterator(objectID);

    if (it != objects.end())
    {
        it = objects.erase(it);
    }
}

std::string Inventory::listInventory()
{
    int objectCount = 1;

    std::stringstream inventoryList;

    for (auto &obj : objects) {

        inventoryList << objectCount++ << ". " << obj.getName() << "\n";
    }

    return inventoryList.str();

}

const std::vector<Object>& Inventory::getObjects() const {
    return objects;
}
