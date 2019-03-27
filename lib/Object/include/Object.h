#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <string>
#include <vector>

#include <AlterSpace.h>
#include <UniqueID.h>
#include <unordered_map>

using AlterSpace::ID;
using AlterSpace::Name;
using AlterSpace::Property;
using AlterSpace::Value;

class Object : public UniqueID {
private:
    ID objectID;
    Name objectName;
    std::unordered_map<Property, Value> abilities;
    std::vector<std::string> keywords;
    std::string shortdesc;
    std::vector<std::string> longdesc;

    struct extraDescription {
        std::vector<std::string> keywords;
        std::vector<std::string> desc;
    };
    extraDescription extra;

public:

    Object() = default;

    Object(const Name &objectName) : objectName(objectName) {}

    Object(ID objectID, const Name &objectName) : objectID(objectID), objectName(objectName) {}

    Object(ID objectID, Name objectName, std::unordered_map<Property, Value> abilities, std::vector<std::string> keywords, std::string shortdesc, std::vector<std::string> longdesc,
           std::vector<std::string> extraKeywords, std::vector<std::string> extraDesc) {
        this->objectID = objectID;
        this->objectName = objectName;
        this->abilities = abilities;
        this->keywords = keywords;
        this->shortdesc = shortdesc;
        this->longdesc = longdesc;
        this->extra.keywords = extraKeywords;
        this->extra.desc = extraDesc;
    }

    Name getName() const;

    ID getID() const;

    std::unordered_map<Property, Value> getAbilities();

    std::vector<std::string> getKeywords();

    std::string getShortDesc();

    std::vector<std::string> getLongDesc();

    std::vector<std::string> getExtraKeywords();

    std::vector<std::string> getExtraDesc();
};


#endif //ALTERSPACE_OBJECT_H
