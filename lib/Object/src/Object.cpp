//
// Created on 1/22/2019.
//

#include <iostream>
#include <Object.h>




Object::Object(std::string name) {
    this->name = name;
}

void Object::printTest() {
    std::cout << "Object name: " << name << std::endl;
}

