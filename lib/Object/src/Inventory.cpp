#include <algorithm>
#include <Inventory.h>

Inventory::Inventory() = default;

void Inventory::addItem(Object object)
{
    objects.push_back(object);
}

auto Inventory::getItemIteratorByID(ID objectID)
{
    auto it = find_if(objects.begin(), objects.end(),
                      [ objectID ] ( Object const& obj )->bool {
                          return obj.getID() == objectID;
                        });

    return it;    
}

bool Inventory::doesItemExist(ID objectID)
{
    
    return getItemIteratorByID(objectID) != objects.end();
}

auto Inventory::getItemIteratorByName(Name objectName)
{
    auto it = find_if(objects.begin(), objects.end(),
                      [ objectName ] ( Object const& obj )->bool {
                          return obj.getName() == objectName;
                        });

    return it;
}

bool Inventory::doesItemExistByName(Name objectName)
{
    
    return getItemIteratorByName(objectName) != objects.end();
}

Object Inventory::getItemByName(Name objectName)
{
    if (doesItemExistByName(objectName) == false)
    {
        return nullptr;
    }

    auto it = getItemIteratorByName(objectName);

    return *it;
}

bool Inventory::removeItem(ID objectID)
{
    auto it = find_if(objects.begin(), objects.end(),
                        [objectID] (Object const& obj)->bool {
                            return obj.getID() == objectID;
                        });
    if (it != objects.end())
        it = objects.erase(it);
        return true;
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
