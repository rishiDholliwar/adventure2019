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
  
    Object(const Name &objectName) : objectName(objectName) {}

    Object();

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

    ID getID() const;

    Name getType() const;

    std::unordered_map<Property, Value> getAbilities() {
      return abilities;
    }

    std::vector<std::string> getKeywords() {
        return keywords;
    }

    std::string getShortDesc() {
        return shortdesc;
    }

    std::vector<std::string> getLongDesc() {
        return longdesc;
    }

    std::vector<std::string> getExtraKeywords() {
        return extra.keywords;
    }

    std::vector<std::string> getExtraDesc() {
        return extra.desc;
    }

};


#endif //ALTERSPACE_OBJECT_H
