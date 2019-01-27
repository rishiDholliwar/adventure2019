//
// Created by evan on 19/01/19.
//

#include <memory>
#include "Room.h"
#include "Area.h"
#include <iostream>

int main(){
    std::string dir = "north";
    std::string room_name = "r1";
    std::string area_name = "a1";
    Room* r = new Room(1,"r1");
    Area* a = new Area(2,"a1");
    a->addRoom(r);
    std::cout<< "Area name: " << a->getName() << "\n";
    Room* roomInArea = a->getRooms().at(0);
    std::cout<< "Room name: " << roomInArea->getName() <<"\n";
    Room* r2 = new Room(3,"r2");
    // link r2 to north of r1
    roomInArea->linkRoom('n', r2);
    // link r1 to south of r2
    r2->linkRoom('s',roomInArea);
    std::cout<< "North of r1: " << roomInArea->getNorth()->getName() <<"\n";
    std::cout<< "South of r2: " << roomInArea->getNorth()->getSouth()->getName() <<"\n";





}