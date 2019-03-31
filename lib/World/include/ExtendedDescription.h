#ifndef ALTERSPACE_EXTENDEDDESCRIPTION_H
#define ALTERSPACE_EXTENDEDDESCRIPTION_H


#include <string>
#include <vector>

class ExtendedDescription {
private:
    std::vector<std::string> keywords;
    std::vector<std::string> desc;

public:
    ExtendedDescription();

    ExtendedDescription(const std::vector<std::string> &keywords, const std::vector<std::string> &desc);

    const std::vector<std::string> &getKeywords() const;

    const std::vector<std::string> &getDesc() const;

};


#endif //ALTERSPACE_EXTENDEDDESCRIPTION_H
