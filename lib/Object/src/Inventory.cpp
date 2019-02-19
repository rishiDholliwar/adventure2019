#include <algorithm>
#include <Inventory.h>

Inventory::Inventory() = default;

void Inventory::addItem(Object object)
{
    objects.push_back(object);
}

auto Inventory::getItemIterator(ID objectID)
{
    auto it = find_if(objects.begin(), objects.end(),
                      [ objectID ] ( Object const& obj )->bool {
                          return obj.getID() == objectID;
                        });

    return it;    
}

bool Inventory::doesItemExist(ID objectID)
{
    
    return getItemIterator(objectID) != objects.end();
}

auto Inventory::getItemIterator(Name objectName)
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

Object Inventory::getItem(Name objectName)
{

    if (doesItemExist(objectName) == false)
    {
        return Object();
    }

    auto it = getItemIterator(objectName);

    return *it;
}

bool Inventory::removeItem(ID objectID)
{
    auto it = getItemIterator(objectID);

    if (it != objects.end())
    {
        it = objects.erase(it);
        return (doesItemExist(objectID) == false);
    }
    return false;
}

std::string Inventory::listInventory()
{
    if (objects.empty()) {
        return std::string();
    }

    int objectCount = 1;
    std::string inventoryList;

    for(auto &obj : objects){

        std::string objectString = std::to_string(objectCount) + ". " + obj.getName() + "\n";
        inventoryList += objectString;

        objectCount++;
    }
    return inventoryList;
}
