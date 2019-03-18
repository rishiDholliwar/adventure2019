#include <algorithm>
#include <sstream>
#include <Inventory.h>
#include <JSONObjects.h>

void Inventory::addItem(Object object) {
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

bool Inventory::removeItem(ID objectID)
{
    auto it = getItemIterator(objectID);

    if (it == objects.end())
    {
        return false;
    }

    it = objects.erase(it);
    return true; //TODO: fix this for multiple items later!!!
}

template <typename Container> inline unsigned int Inventory::getLengthStrArr(const Container& strArr) {

    unsigned int length = 0;

    for (const auto& str : strArr) {
        length += str.length();
    }
    return length;
}

std::string Inventory::listInventory(Name& username) {

    if (objects.empty()) {
        return std::string();
    }

    // get unique object names
    std::unordered_set<std::string> objectNames;
    for (Object obj : objects) {
        objectNames.insert(obj.getName());
    }

    // Preallocate expected string length, to avoid reallocation & get cache locality
    unsigned int length = 0;
    length = getLengthStrArr<std::unordered_set<std::string>>(objectNames) + (4 * objectNames.size());
    std::string inventoryList = std::string();
    inventoryList.reserve(length);

    // list inventory, grouped by name
    for (auto& name : objectNames) {
        int nameCount = count_if(objects.begin(), objects.end(),
                    [name] (const Object& obj) {
                        return obj.getName() == name;
                    });
        std::string nameStr = name + "  x" + std::to_string(nameCount) + "\n";
        inventoryList += nameStr;
    }
    return inventoryList;

    //  ** Return type vector<Response> ?
    //  Response userResponse = Response(inventoryList, username);
    //  return formulateResponse(userResponse);
}
