#ifndef ALTERSPACE_OBJECTCONTROLLER_H
#define ALTERSPACE_OBJECTCONTROLLER_H

#include <string>
#include <unordered_map>

#include <AlterSpace.h>
#include <Object.h>

// For future use
using AlterSpace::ID;
using AlterSpace::Name;

class ObjectController
{
private:
    std::unordered_map<ID, Object> objects;

public:
    ObjectController();

    bool addObjectToList(const Object &object);

    /* Does Object Exist:
     *
     * Function: Checks to see if the object in question is valid
     *
     * Pre-Condition: Name of the object to validate
     * Post: returns true if object exists
     *
     * */
    bool doesObjectExist(const ID objectID);

    bool doesObjectOfThisNameExist(const Name objectName);

    const Object &getObject(const ID objectID) const;

    /* Get Object By Name:
     *
     * Function: Retrieve the object from the object list
     *
     * Pre-Condition: Name of the object to retrieve
     * Post: returns the object
     *
     * */
    const Object &getObjectFromList(const Name objectName) const;

    const Object &getObjectFromList(const ID objectID) const;

    Name getObjectName(const ID objectID){ return getObjectFromList(objectID).getName();};

    // look and examine
    std::string lookItem(Name objectName);
    std::string examineItem(Name objectName);
    std::string lookItem(ID objec);
    std::string examineItem(ID objectID);
};

#endif //ALTERSPACE_OBJECTCONTROLLER_H
