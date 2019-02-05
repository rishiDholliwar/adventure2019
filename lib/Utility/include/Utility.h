#ifndef WEBSOCKETNETWORKING_UTILITY_H
#define WEBSOCKETNETWORKING_UTILITY_H

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <regex>

namespace utility {

    template <typename T, typename Pred>
    static std::vector<T> filter(std::vector<T> collection, Pred predicate){
        std::vector<T> result;
        std::copy_if(collection.begin(), collection.end(), result, predicate);
        return result;
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
        std::string tmp;
        ss >> tmp;
        while ( ss >> str )
        {
            tmp += " " + str;
        }
        auto value = std::regex_replace(tmp, std::regex("^ +| +$|( ) +"), "$1");
        result.push_back(value);
        return result;
    }

}


#endif //WEBSOCKETNETWORKING_UTILITY_H
