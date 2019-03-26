
#include <ExtendedDescription.h>


ExtendedDescription::ExtendedDescription() {

}

ExtendedDescription::ExtendedDescription(const std::vector<std::string> &keywords,
                                         const std::vector<std::string> &desc) {

}

const std::vector<std::string> &ExtendedDescription::getKeywords() const {
    return keywords;
}

const std::vector<std::string> &ExtendedDescription::getDesc() const {
    return desc;
}
