//
// Created on 1/22/2019.
//

#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <stdio.h>
#include <string>
#include <utility>

class Object {
private:
    unsigned int ID;
    std::string name;

public:

    Object(unsigned int ID, const std::string &name);

    const std::string &getName() const;

    unsigned int getID() const;
};


#endif //ALTERSPACE_OBJECT_H
