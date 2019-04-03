#include <Object.h>

Name Object::getName() const {
    return objectName;
}

ID Object::getObjectID() const {
	return objectID;
}

ID Object::getID() const {
    return id;
}

// std::unordered_map<Property, Value> Object::getAbilities() {
//   return abilities;
// }

const std::vector<std::string> Object::getKeywords() const {
    return keywords;
}

const std::string Object::getShortDesc() const {
    return shortdesc;
}

const std::vector<std::string> Object::getLongDesc() const {
    return longdesc;
}

std::vector<Extra> Object::getExtra() const {
    return extra;
}