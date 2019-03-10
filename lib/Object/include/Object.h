#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <string>

#include <AlterSpace.h>
#include <UniqueID.h>

using AlterSpace::ID;
using AlterSpace::Name;

class Object : public UniqueID {
private:
    Name objectName;

public:
    Object(const Name &objectName) : objectName(objectName) {}

    const Name& getName() const;
    ID getID() const;

};


#endif //ALTERSPACE_OBJECT_H
