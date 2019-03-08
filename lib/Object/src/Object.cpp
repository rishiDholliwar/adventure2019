#include <Object.h>

Object::Object() = default;

Name& Object::getName() const {
    return this->objectName;
}

ID Object::getID() const {
    return id;
}

Name Object::getType() const {
    return this->objectName;
}
