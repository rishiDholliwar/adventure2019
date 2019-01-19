//
// Created by evan on 19/01/19.
//

#include <memory>
#include "../include/World.h"
#include <iostream>

int main(){
    std::unique_ptr<Area>a = std::make_unique<Area>(1,"a1");
    std::unique_ptr<Room>r = std::make_unique<Room>(1,"r1");
    a->addRoom(r);
    std::cout << a->getId();
}