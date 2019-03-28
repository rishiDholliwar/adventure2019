//
// Created by bryan on 21/03/19.
//

#include <iostream>
#include "JSONThingy.h"




int main() {

    JSONThingy jt;

    Character elvin("elvin", 1);
    Character lora("lora", 2);

    elvin.addItemToInventory(Object("Basic Sword"));

    lora.addItemToInventory(Object("Basic Armor"));

    jt.save(elvin);
    jt.save(lora);

    Character readElvin;
    Character readLora;

    jt.load("elvin", readElvin);
    jt.load("lora", readLora);

    std::cout << "name: " << readElvin.getName() << std::endl;
    std::cout << "inv: " << readElvin.listInventory() << std::endl;
    std::cout << "wear: " << readElvin.listWearing() << std::endl;


    std::cout << readLora.getName() << std::endl;
    std::cout << readLora.listInventory() << std::endl;
    std::cout << readLora.listWearing() << std::endl;

}