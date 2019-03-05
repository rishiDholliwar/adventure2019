#include <Object.h>

Object::Object() = default;

ID Object::getID() const {
    return this->objectID;
}

Name Object::getType() const {
    return this->objectName;
}
