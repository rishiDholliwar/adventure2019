#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <string>
#include <vector>

#include <AlterSpace.h>

using AlterSpace::ID;
using AlterSpace::Name;

class Object {
private:
    ID objID;
    Name objType;
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
	Object();

    Object(ID objID, const Name &objType) : objID(objID), objType(objType) {}

    //Struct not working with this constructor
//    Object(ID objID,std::vector<std::string> keywords , std::string shortdesc,std::vector<std::string> longdesc,std::vector<std::string> extraKeywords, std::vector<std::string> extraDesc)
//    : objID(objID),keywords(keywords),shortdesc(shortdesc),longdesc(longdesc), extra(extraKeywords),extraDescription(extraDesc){}

    Object(ID objID, Name objType, std::unordered_map<Property, Value> abilities, std::vector<std::string> keywords, std::string shortdesc, std::vector<std::string> longdesc,
           std::vector<std::string> extraKeywords, std::vector<std::string> extraDesc) {
        this->objID = objID;
        this->objType = objType;
        this->abilities = abilities;
        this->keywords = keywords;
        this->shortdesc = shortdesc;
        this->longdesc = longdesc;
        this->extra.keywords = extraKeywords;
        this->extra.desc = extraDesc;
    }

    ID getID() const;

    Name &getType() const;

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
