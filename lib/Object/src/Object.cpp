#include <Object.h>

Object::Object() = default;

ID Object::getID() const {
    return this->objType;
}

const Name& Object::getType() const {
    return this->objType;
}
