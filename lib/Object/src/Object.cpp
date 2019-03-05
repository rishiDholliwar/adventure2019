#include <Object.h>

Object::Object() = default;

ID Object::getID() const {
    return this->objectID;
}

Name Object::getName() const {
    return this->objectName;
}
