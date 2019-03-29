#ifndef ALTERSPACE_EXTRA_H
#define ALTERSPACE_EXTRA_H

#include <string>
#include <vector>

class Extra {
private:
    std::vector<std::string> keywords;
    std::vector<std::string> desc;
public:
    Extra() = default;
    
    explicit Extra(std::vector<std::string> keywords, std::vector<std::string> desc)
    : keywords(keywords), desc(desc) { }

    const std::vector<std::string> getKeywords() const;
    const std::vector<std::string> getDesc() const;
};

#endif 