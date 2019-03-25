#include <Object.h>

Name Object::getName() const {
    return objectName;
}

ID Object::getID() const {
    return id;
}

std::unordered_map<Property, Value> Object::getAbilities() {
  return abilities;
}

std::vector<std::string> Object::getKeywords() {
    return keywords;
}

std::string Object::getShortDesc() {
    return shortdesc;
}

std::vector<std::string> Object::getLongDesc() {
    return longdesc;
}

std::vector<std::string> Object::getExtraKeywords() {
    return extra.keywords;
}

std::vector<std::string> Object::getExtraDesc() {
    return extra.desc;
}