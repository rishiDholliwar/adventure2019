//
// Created by bshetty on 2/2/19.
//

#include <ObjectController.h>
#include <algorithm>


ObjectController::ObjectController(){
    objects.insert({"Basic Sword", Object(100,"Basic Sword")});
    objects.insert({"Basic Armor", Object(200,"Basic Armor")});
};

bool ObjectController::doesObjectExist(const std::string &objectName) {
    return objects.find(objectName) != objects.end();
}

const Object &ObjectController::getObjectFromListByName(const std::string &objectName) const {
    return objects.find(objectName)->second;
}

