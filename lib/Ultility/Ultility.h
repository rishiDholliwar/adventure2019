//
// Created by ximinz on 16/01/19.
//

#ifndef WEBSOCKETNETWORKING_ULTILITY_H
#define WEBSOCKETNETWORKING_ULTILITY_H

#include <vector>
#include <algorithm>
namespace ultility {

    template <typename T, typename Pred>
    static std::vector<T> filter(std::vector<T> collection, Pred predicate){
        std::vector<T> result;
        std::copy_if(collection.begin(), collection.end(), result, predicate);
        return result;
    }

}


#endif //WEBSOCKETNETWORKING_ULTILITY_H
