//
// Created by evan on 19/01/19.
//

#include <memory>
#include "../include/Door.h"
#include "../src/Door.cpp"
#include "../include/Room.h"
#include "../src/Room.cpp"
#include "../include/Area.h"
#include "../src/Area.cpp"
#include <iostream>

int main(){
    std::unique_ptr<Door> d = std::make_unique<Door>(1,2,"north");
    std::unique_ptr<Room> r = std::make_unique<Room>(1,"r1");
    std::unique_ptr<Area> a = std::make_unique<Area>(2,"a1");
    r->addDoor(d);
    a->addRoom(r);
    std::cout<< "Area name: " << a->getName() << "\n";
    std::cout<< "Room name: " << a->getRooms().begin().operator*().get()->getName() << "\n";
    std::cout<< "Door direction: " << a->getRooms().begin().operator*().get()->getDoors().begin().operator*().get()->getDirection() << "\n";


}