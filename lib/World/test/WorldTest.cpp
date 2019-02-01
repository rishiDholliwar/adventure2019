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



    std::cout<< "generate room1: " <<rc.generateRoom(1, "room1")<<"\n";
    std::cout<< "generate room1: " <<rc.generateRoom(1, "room1")<<"\n";
    std::cout<< "generate room2: " <<rc.generateRoom(2, "room2")<<"\n";
    std::cout<< "generate room3: " <<rc.generateRoom(3, "room3")<<"\n";

    std::cout<< "add character 2 to room1: " << rc.addCharacterToRoom(2,1) << "\n";
    std::cout<< "add character 3 to room1: " << rc.addCharacterToRoom(3,1) << "\n";
    std::cout<< "add character 4 to room1: " << rc.addCharacterToRoom(4,1) << "\n";
    std::cout<< "add character 4 to room1: " << rc.addCharacterToRoom(4,1) << "\n";
    std::cout<< "add character 5 to room1: " << rc.addCharacterToRoom(5,1) << "\n";

    std::cout<< "add character 10 to room2: " << rc.addCharacterToRoom(10,2) << "\n";

    std::cout<< "character ID in room1" <<"\n";
    for (auto i : rc.getCharacterList(1)){
        std::cout<<i<<"\n";
    }
    std::cout<< "character ID in room2" <<"\n";
    for (auto i : rc.getCharacterList(2)){
        std::cout<<i<<"\n";
    }

    // moving character
    std::cout<< "remove character 2 from room1: " << rc.removeCharacterFromRoom(2,1) << "\n";
    std::cout<< "remove character 9 from room1: " << rc.removeCharacterFromRoom(9,1) << "\n";
    std::cout<< "remove character 10 from room2: " << rc.removeCharacterFromRoom(10,2) << "\n";
    std::cout<< "add character 2 to room2: " << rc.addCharacterToRoom(2,2) << "\n";

    std::cout<< "character ID in room1" <<"\n";
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

    rc.linkRoom('n',1,2);
    std::cout<< "link room 2 to the north of room1" << "\n";
    rc.linkRoom('s',2,1);
    std::cout<< "link room 1 to the south of room2" << "\n";
    std::cout<< "north of room1 is " << rc.getLinkedRoom('n', 1)<<"\n";
    std::cout<< "south of room2 is " << rc.getLinkedRoom('s', 2)<<"\n";
    std::cout << "end" << std::endl;

}