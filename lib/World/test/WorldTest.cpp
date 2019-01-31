//
// Created by evan on 19/01/19.
//

#include <memory>
#include "Room.h"
#include "Area.h"
#include <iostream>
#include <RoomControllor.h>
#include <algorithm>

int main(){
    RoomControllor rc;



    std::cout<<rc.generateRoom(1, "room1")<<"\n";
    std::cout<<rc.generateRoom(1, "room1")<<"\n";

    Room* room = rc.searchRoom(1);

    std::cout<<(room== nullptr)<<"\n";
    std::cout<<room->getName()<<"\n";
    rc.addCharacterToRoom(2,1);
    rc.addCharacterToRoom(4, 1);
    rc.generateRoom(2, "room2");
    rc.generateRoom(3, "room3");

    for (auto i : rc.getCharacterList(1)){
        std::cout<<i<<"\n";
    }

    std::cout << "end" << std::endl;

//    std::vector<Room> rlist;
//    rlist.emplace_back(1, "room1");
//
//    auto tempRoom = std::find_if(rlist.begin(), rlist.end(),
//                                 [](const Room& room)
//                                 {return room.getId() == 1;}
//    );
//
//    auto room = tempRoom.base();
//    room->addCharacter(2);

}