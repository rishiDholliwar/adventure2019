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
    rc.generateRoom(2, "room2");
    rc.generateRoom(3, "room3");

    rc.addCharacterToRoom(2,1);
    rc.addCharacterToRoom(4,1);
    rc.addCharacterToRoom(5,1);
    rc.addCharacterToRoom(5,1);
    rc.addCharacterToRoom(6,1);

    rc.addCharacterToRoom(10,2);
    std::cout<< "character ID in room1" <<"\n";
    for (auto i : rc.getCharacterList(1)){
        std::cout<<i<<"\n";
    }
    std::cout<< "character ID in room2" <<"\n";
    for (auto i : rc.getCharacterList(2)){
        std::cout<<i<<"\n";
    }

    // moving character
    rc.removeCharacterFromRoom(2,1);
    rc.addCharacterToRoom(2,2);


    std::cout<< "move character 2 to room2 \n character ID in room1" <<"\n";
    for (auto i : rc.getCharacterList(1)){
        std::cout<<i<<"\n";
    }
    std::cout<< "character ID in room2" <<"\n";
    for (auto i : rc.getCharacterList(2)){
        std::cout<<i<<"\n";
    }
    std::cout<< "all room ID" <<"\n";
    for (auto i : rc.getRoomList()){
        std::cout<<i<<"\n";
    }

    std::cout << "end" << std::endl;

}