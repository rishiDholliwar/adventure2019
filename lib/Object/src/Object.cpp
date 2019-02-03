//
// Created on 1/22/2019.
//


#include <iostream>
#include <Object.h>


Object::Object(unsigned int id, const std::string &name) : id(id), name(name) {}

const std::string &Object::getName() const {
    return name;
}

unsigned int Object::getId() const {
    return id;
}

void Object::printTest() {
    std::cout << "Object name: " << name << std::endl;
}


