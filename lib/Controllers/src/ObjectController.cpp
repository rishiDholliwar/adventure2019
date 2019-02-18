#include <ObjectController.h>

ObjectController::ObjectController(){
    objects.insert( {"Basic Sword", Object(100,"Basic Sword")} );
    objects.insert( {"Basic Armor", Object(200,"Basic Armor")} );
};

bool ObjectController::doesObjectExist(const Name &objType) {
    return objects.find(objType) != objects.end();
}

const Object &ObjectController::getObjectFromListByName(const Name &objType) const {
    return objects.find(objType)->second;
}
