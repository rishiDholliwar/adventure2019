#include <Object.h>

Object::Object() = default;

ID Object::getID() const {
    return this->objID;
}

Name Object::getType() const {
    return this->objType;
}
