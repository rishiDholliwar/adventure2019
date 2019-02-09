//
// Created by bshetty on 2/2/19.
//

#ifndef ALTERSPACE_OBJECTCONTROLLER_H
#define ALTERSPACE_OBJECTCONTROLLER_H

#include <string>
#include <map>
#include <Object.h>



class ObjectController{
private:

    std::map<std::string, Object> objects;

public:

    ObjectController();

    /* Does Object Exist:
     *
     * Function: Checks to see if the object in question is valid
     *
     * Pre-Condition: requires the name of the object
     * Post: returns true if object exists
     *
     * */
    bool doesObjectExist(const std::string &objectName);

    /* Get Object By Name:
     *
     * Function: Retrieve the object from the object list
     *
     * Pre-Condition: requires the name of the object
     * Post: returns the object
     *
     * */
    const Object &getObjectFromListByName(const std::string &objectName) const;
};

#endif //ALTERSPACE_OBJECTCONTROLLER_H
