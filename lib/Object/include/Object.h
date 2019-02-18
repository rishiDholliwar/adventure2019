#ifndef ALTERSPACE_OBJECT_H
#define ALTERSPACE_OBJECT_H

#include <string>
#include <vector>

#include <AlterSpace.h>

using AlterSpace::ID;
using AlterSpace::Name;

class Object {
private:
    ID objectID;
    Name objectName;
    std::vector<std::string> keywords;
    std::string shortdesc;
    std::vector<std::string> longdesc;

    struct extraDescription {
        std::vector<std::string> keywords;
        std::vector<std::string> desc;
    };
    extraDescription extra;


public:
    Object(ID objectID, const Name &objectName) : objectID(objectID), objectName(objectName) {}

    //Struct not working with this constructor
//    Object(ID objectID,std::vector<std::string> keywords , std::string shortdesc,std::vector<std::string> longdesc,std::vector<std::string> extraKeywords, std::vector<std::string> extraDesc)
//    : objectID(objectID),keywords(keywords),shortdesc(shortdesc),longdesc(longdesc), extra(extraKeywords),extraDescription(extraDesc){}

    Object(ID objectID, std::vector<std::string> keywords, std::string shortdesc, std::vector<std::string> longdesc,
           std::vector<std::string> extraKeywords, std::vector<std::string> extraDesc) {
        this->objectID = objectID;
        this->keywords = keywords;
        this->shortdesc = shortdesc;
        this->longdesc = longdesc;
        this->extra.keywords = extraKeywords;
        this->extra.desc = extraDesc;

    }

    const Name &getName() const;

    ID getID() const;

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