#include <Object.h>

Object::Object() = default;

Name& Object::getName() const {
    return objectName;
}

ID Object::getID() const {
    return id;
}
