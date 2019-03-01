#include <Object.h>

const Name& Object::getName() const {
    return this->objectName;
}

ID Object::getID() const {
    return id;
}
