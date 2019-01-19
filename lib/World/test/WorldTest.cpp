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
    std::string dir = "north";
    std::string room_name = "r1";
    std::string area_name = "a1";
    std::unique_ptr<Door> d = std::make_unique<Door>(1,2,dir);
    std::unique_ptr<Room> r = std::make_unique<Room>(1,room_name);
    std::unique_ptr<Area> a = std::make_unique<Area>(2,area_name);
    r->addDoor(d);
    a->addRoom(r);
    std::cout<< "Area name: " << a->getName() << " original variable: "<< area_name << "\n";
    std::cout<< "Room name: " << a->getRooms().begin().operator*()->getName()
        << " original variable: "<< room_name <<"\n";
    std::cout<< "Door direction: "<< a->getRooms().begin().operator*()->getDoors()
            .begin().operator*()->getDirection() << " original variable: "<< dir << "\n";


}