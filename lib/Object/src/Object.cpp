#include <Object.h>

Object::Object() = default;

const Name& Object::getName() const {
    return this->objectName;
}

ID Object::getID() const {
    return this->objectID;
}
