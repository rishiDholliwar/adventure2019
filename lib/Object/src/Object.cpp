//
// Created on 1/22/2019.
//

#include <iostream>
#include <Object.h>




Object::Object(std::string name) {
    this->name = name;
}

Object::Object(std::string id, std::string name, std::string short_description, std::string long_description) {
    this->id = id;
    this->name = name;
    this->short_description = short_description;
    this->long_description = long_description;
}

std::string Object::getObjectName() {
    return this->name;
}

std::string Object::getObjectID() {
    return this->id;
}


void Object::printTest() const {
    std::cout << "Object name: " << name <<  " Object ID: " << id << std::endl;
}
