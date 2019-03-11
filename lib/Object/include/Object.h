#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <string>
#include <vector>
#include <AlterSpace.h>
#include <UniqueID.h>

using AlterSpace::ID;
using AlterSpace::Name;

class Object : public UniqueID {
private:
    Name objectName;

    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;

public:
    Object(const Name &objectName) : objectName(objectName) {}

    std::vector<std::string> const& getDescriptions() const{return descriptions;};
    std::vector<std::string> const& getExtendedDescriptions() const{return extendedDescriptions;};

    const Name& getName() const;
    ID getID() const;

};


#endif //ALTERSPACE_OBJECT_H
