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
    	std::vector<std::string> result{};
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
        std::vector<std::string> result{};
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

    /*
     *  Extract string in string vector into certain format and return the new string
     *  Example:
     *      string element 1
     *      string element 2
     *
     */
    static std::string extractStringVector(const std::vector<std::string>& stringVector){
        std::stringstream ss;
        for (const auto &str : stringVector ){
            ss << "\t" << str << "\n";
        }
        return ss.str();
    }

    static std::string toLower(std::string data) {
        std::for_each(data.begin(), data.end(), [](char & c) {
            c = ::tolower(c);
        });
        return data;
    }

}


#endif //WEBSOCKETNETWORKING_UTILITY_H
