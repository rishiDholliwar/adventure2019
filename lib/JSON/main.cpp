//
// Created by bryan on 21/03/19.
//

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

    jt.load("Elvin", readElvin);
    jt.load("Lora", readLora);

    std::cout << readElvin.getName() << std::endl;
    std::cout << readElvin.listInventory() << std::endl;
    std::cout << readElvin.listWearing() << std::endl;


    std::cout << readLora.getName() << std::endl;
    std::cout << readLora.listInventory() << std::endl;
    std::cout << readLora.listWearing() << std::endl;

}