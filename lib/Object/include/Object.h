//
// Created on 1/22/2019.
//

#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <stdio.h>
#include <string>


class Object {
private:
    std::string id;
    std::string name;
    std::string short_description;
    std::string long_description;

public:
    Object(){};
    Object(std::string name);
    Object(std::string id, std::string name, std::string short_description, std::string long_description);

    /*
     * Getter functions
     */
    std::string getObjectName();
    std::string getObjectID();
    std::string getObjectShortDescription();
    std::string getObjectLongDescription();

    void printTest() const;
};


#endif //ALTERSPACE_OBJECT_H
