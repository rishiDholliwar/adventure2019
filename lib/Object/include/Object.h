#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <string>
#include <vector>
#include <numeric>

#include <Extra.h>
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
    // std::unordered_map<Property, Value> abilities;
    std::vector<std::string> keywords;
    std::string shortdesc;
    std::vector<std::string> longdesc;
    std::vector<Extra> extra;

public:

    Object() = default;

    Object(const Name &objectName) : objectName(objectName) {
        this->objectID = id;
    }

    // Object(ID objectID, const Name &objectName) : objectID(objectID), objectName(objectName) {}

    explicit Object(ID objectID, std::vector<std::string> keywords, std::string shortdesc, std::vector<std::string> longdesc,
           std::vector<Extra> extra) : objectID(objectID), keywords(keywords), shortdesc(shortdesc), longdesc(longdesc), extra(extra) {
        this->objectName = std::accumulate(keywords.begin(), keywords.end(), std::string(""));
    }

    Object(const Object &tempObject) {
        this->id = tempObject.id;
        this->objectName = tempObject.getName();
        this->objectID = tempObject.getObjectID();
        this->keywords = tempObject.getKeywords();
        this->shortdesc = tempObject.getShortDesc();
        this->longdesc = tempObject.getLongDesc();
        this->extra = tempObject.getExtra();
    }

    // Object(ID objectID, Name objectName, std::unordered_map<Property, Value> abilities, std::vector<std::string> keywords, std::string shortdesc, std::vector<std::string> longdesc) {
    //     this->objectID = objectID;
    //     this->objectName = objectName;
    //     this->abilities = abilities;
    //     this->keywords = keywords;
    //     this->shortdesc = shortdesc;
    //     this->longdesc = longdesc;
    // }

    Name getName() const;

    ID getID() const;

    ID getObjectID() const;

    // std::unordered_map<Property, Value> getAbilities();

    const std::vector<std::string> getKeywords() const;

    const std::string getShortDesc() const;

    const std::vector<std::string> getLongDesc() const;

    std::vector<Extra> getExtra() const;
};


#endif //ALTERSPACE_OBJECT_H
