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

    bool findObject(const std::string &objectName);

    const Object &getObject(const std::string &objectName) const;
};

#endif //ALTERSPACE_OBJECTCONTROLLER_H
