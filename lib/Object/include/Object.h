#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <string>

#include <AlterSpace.h>

using AlterSpace::ID;
using AlterSpace::Name;

class Object {
private:
    ID objectID;
    Name objectName;

public:
	Object();
	
    Object(ID objectID, const Name &objectName) : objectID(objectID), objectName(objectName) {}

    const Name& getName() const;
    ID getID() const;
};


#endif //ALTERSPACE_OBJECT_H
