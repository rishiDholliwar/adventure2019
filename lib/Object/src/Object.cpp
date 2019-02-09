//
// Created on 1/22/2019.
//


#include <iostream>
#include <Object.h>


Object::Object(unsigned int ID, const std::string &name) : ID(ID), name(name) {}

const std::string &Object::getName() const {
    return name;
}

unsigned int Object::getID() const {
    return ID;
}


