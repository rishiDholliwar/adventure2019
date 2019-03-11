#ifndef WEBSOCKETNETWORKING_UTILITY_H
#define WEBSOCKETNETWORKING_UTILITY_H

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace utility {

    template <typename T, typename Pred>
    static std::vector<T> filter(std::vector<T> collection, Pred predicate){
        std::vector<T> result;
        std::copy_if(collection.begin(), collection.end(), result, predicate);
        return result;
    }

    static std::string trimStringToLength(std::string input, int length)
    {
        if ( input.length() > length )
        {
            input.erase(length, std::string::npos);
        }
        return input;
    }

    static std::vector<std::string> tokenizeString(const std::string& input)
    {
    	std::vector<std::string> result;
    	std::stringstream ss(input);
    	std::string word;
    	while (ss >> word)
    	{
    		result.push_back(word);
    	}
    	return result;
    }

    static std::vector<std::string> popFront(const std::string& input)
    {
        std::vector<std::string> result;
        std::stringstream ss(input);
        std::string str;
        ss >> str;
        result.push_back(str);
        str = "";
        auto pos = input.find(" ", str.length()) + 1;
        if ( input.find(" ", str.length()) != std::string::npos ) {
            str = input;
            str.erase(0, pos);
        }
        result.push_back(str);
        return result;
    }

    template <typename EntityType>
    static std::string lookEntity(const EntityType& entity){
        std::stringstream ss;
        const auto &descriptions = entity.getDescriptions();
        std::string indentation = "    ";
        for (const auto &description : descriptions ){
            ss << indentation << description << "\n";
        }
        return ss.str();
    }

    template <typename EntityType>
    static std::string examineEntity(const EntityType& entity){
        std::stringstream ss;
        const auto &descriptions = entity.getExtendedDescriptions();
        if (descriptions.size() == 0){
            return lookEntity(entity);
        }
        std::string indentation = "    ";
        for (const auto &description : descriptions ){
            ss << indentation << description << "\n";
        }
        return ss.str();
    }

}


#endif //WEBSOCKETNETWORKING_UTILITY_H
