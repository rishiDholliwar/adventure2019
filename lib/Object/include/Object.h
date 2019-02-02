//
// Created on 1/22/2019.
//

#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <stdio.h>
#include <string>

class Object {
private:
    std::string name;
    public:
    Object(){};
    Object(std::string name);

    void printTest();
};


#endif //ALTERSPACE_OBJECT_H
