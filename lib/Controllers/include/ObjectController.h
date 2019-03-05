//
// Created by bshetty on 2/2/19.
//

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
    std::unordered_map<Name, Object> objects;

public:
    ObjectController();

    /* Does Object Exist:
     *
     * Function: Checks to see if the object in question is valid
     *
     * Pre-Condition: Name of the object to validate
     * Post: returns true if object exists
     *
     * */
    bool doesObjectExist(const Name &objectName);

    /* Get Object By Name:
     *
     * Function: Retrieve the object from the object list
     *
     * Pre-Condition: Name of the object to retrieve
     * Post: returns the object
     *
     * */
    const Object &getObjectFromListByName(const Name &objectName) const;
};

#endif //ALTERSPACE_OBJECTCONTROLLER_H
