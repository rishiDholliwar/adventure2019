#include <algorithm>
#include <Inventory.h>
#include <JSONObjects.h>

void Inventory::addItem(Object object) {
    objects.push_back(object);
}

auto Inventory::getItemIteratorByID(ID objID) {
    auto it = find_if(objects.begin(), objects.end(),
                      [ objID ] ( Object const& obj )->bool {
                          return obj.getID() == objID;
                        });

    return it;
}

bool Inventory::doesItemExist(ID objID) {

    return getItemIteratorByID(objID) != objects.end();
}

auto Inventory::getItemIteratorByName(Name objType) {
    auto it = find_if(objects.begin(), objects.end(),
                      [ objType ] ( Object const& obj )->bool {
                          return obj.getName() == objType;
                        });

    return it;
}

bool Inventory::doesItemExistByName(Name objType) {

    return getItemIteratorByName(objType) != objects.end();
}

Object Inventory::getItemByType(Name objType)
{

    if (doesItemExistByName(objType) == false)
    {
        return Object();
    }

    auto it = getItemIteratorByName(objType);

    return *it;
}

bool Inventory::removeItem(ID objID)
{
    auto it = getItemIteratorByID(objID);

    if (it != objects.end())
    {
        it = objects.erase(it);
        return (doesItemExist(objID) == false);
    }
    return false;
}

std::string Inventory::listInventory()
{
    if (objects.empty()) {
        return std::string();
    }


    /////

    int objectCount = 1;
    std::string inventoryList;

    for(auto &obj : objects){

        std::string objectString = std::to_string(objectCount) + ". " + obj.getName() + "\n";
        inventoryList += objectString;

        objectCount++;
    }
    return inventoryList;
}
