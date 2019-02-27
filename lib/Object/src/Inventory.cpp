#include <algorithm>
#include <sstream>
#include <Inventory.h>

Inventory::Inventory() = default;

void Inventory::addItem(Object object)
{
    objects.push_back(object);
}

std::vector<Object>::iterator Inventory::getItemIterator(ID objectID)
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

Object Inventory::getItem(Name objectName)
{

    auto it = getItemIterator(objectName);

    return *it;
}

bool Inventory::removeItem(ID objectID)
{
    auto it = getItemIterator(objectID);

    if (it == objects.end())
    {
        return false;
    }

    it = objects.erase(it);
    return (!doesItemExist(objectID)); // fix this for multiple items later!!!
}

std::string Inventory::listInventory()
{
    if (objects.empty()) {
        return std::string();
    }

    int objectCount = 1;
    std::stringstream inventoryList;

    for(auto &obj : objects){

        inventoryList << objectCount << ". " << obj.getName() << "\n";
        objectCount++;
    }
    return inventoryList.str();
}
