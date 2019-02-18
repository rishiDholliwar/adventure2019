#include <ObjectController.h>

ObjectController::ObjectController(){
    objects.insert( {"Basic Sword", Object(100,"Basic Sword")} );
    objects.insert( {"Basic Armor", Object(200,"Basic Armor")} );
};

bool ObjectController::doesObjectExist(const Name &objectName) {
    return objects.find(objectName) != objects.end();
}

const Object &ObjectController::getObjectFromListByName(const Name &objectName) const {
    return objects.find(objectName)->second;
}
