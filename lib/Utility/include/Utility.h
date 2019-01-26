#ifndef WEBSOCKETNETWORKING_UTILITY_H
#define WEBSOCKETNETWORKING_UTILITY_H

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
namespace utility {

    template <typename T, typename Pred>
    static std::vector<T> filter(std::vector<T> collection, Pred predicate){
        std::vector<T> result;
        std::copy_if(collection.begin(), collection.end(), result, predicate);
        return result;
    }

    static std::vector<std::string> stringToVector(std::string input)
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

}


#endif //WEBSOCKETNETWORKING_UTILITY_H
