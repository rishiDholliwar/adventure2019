//
// Created by evan on 19/01/19.
//

#include <memory>
#include <Area.h>

int main(){
    std::unique_ptr<Area>a = std::make_unique<Area>(1,"a1");

}