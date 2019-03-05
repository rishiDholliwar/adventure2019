#include <algorithm>
#include <Inventory.h>
#include <JSONObjects.h>

void Inventory::addItem(Object object) {
    objects.push_back(object);
}

auto Inventory::getItemIteratorByID(ID objectID) {
    auto it = find_if(objects.begin(), objects.end(),
                      [ objectID ] ( Object const& obj )->bool {
                          return obj.getID() == objectID;
                        });

    return it;
}

bool Inventory::doesItemExist(ID objectID) {

    return getItemIteratorByID(objectID) != objects.end();
}

auto Inventory::getItemIteratorByName(Name objectName) {
    auto it = find_if(objects.begin(), objects.end(),
                      [ objectName ] ( Object const& obj )->bool {
                          return obj.getName() == objectName;
                        });

    return it;
}

bool Inventory::doesItemExistByName(Name objectName) {

    return getItemIteratorByName(objectName) != objects.end();
}

Object Inventory::getItemByName(Name objectName)
{

    if (doesItemExistByName(objectName) == false)
    {
        return Object();
    }

    auto it = getItemIteratorByName(objectName);

    return *it;
}

bool Inventory::removeItem(ID objectID)
{
    auto it = getItemIteratorByID(objectID);

    if (it != objects.end())
    {
        it = objects.erase(it);
        return (doesItemExist(objectID) == false);
    }
    return false;
}

std::string Inventory::listInventory() {

    if (objects.empty()) {
        return std::string();
    }

    // get unique object names
    std::unordered_set<std::string> objectNames;
    for (Object obj : objects) {
        objectNames.insert(obj.getName());
    }

    // get inventory, grouped by name
    std::string inventoryList = std::string();
    for (std::string name : objectNames) {
        int nameCount = count_if(objects.begin(), objects.end(),
                    [] (const Object& obj) {
                        return obj.getName() == name
                    });
        std::string nameStr = name + "  x" + nameCount + "\n";
        inventoryList += nameStr;
    }
    return inventoryList;
}
