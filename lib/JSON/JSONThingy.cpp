//
// Created by bryan on 21/03/19.
//

#include "JSONThingy.h"

void to_json(json &j, const Object &anObject) {
    j = json{
            {"objectID", anObject.getID() },
            {"objectName", anObject.getName() }
    };
}

void from_json(const json &j, Object &anObject) {
    anObject = Object( j.at("objectID").get<ID>(), j.at("objectName").get<Name>());
}

void to_json(json &j, const Inventory &anInventory) {
    j = json{
            {"objects", anInventory.getObjects() }
    };
}

void from_json(const json &j, Inventory &anInventory) {
    anInventory = Inventory( j.at("objects").get<std::vector<Object>>());
}

void to_json(json &j, const Character &aCharacter) {

    j = json{
            { "name", aCharacter.getName() },
            { "roomID", aCharacter.getRoomID() },
            { "wearing", aCharacter.getWearing() },
            { "inventory", aCharacter.getInventory() },
    };
}

void from_json(const json &j, Character &aCharacter) {
    aCharacter = Character(
            j.at("name").get<std::string>(),
            j.at("roomID").get<ID>(),
            j.at("inventory").get<Inventory>(),
            j.at("wearing").get<std::vector<Object>>());

}

void JSONThingy::save(Character &aCharacter) {
    json j;

    to_json(j, aCharacter);

    if(!boost::filesystem::exists("./DataFiles/Characters/")) {
        boost::filesystem::create_directory("./DataFiles/Characters/");
    }
    std::ofstream write("./DataFiles/Characters/" + aCharacter.getName() + ".json");
    write << std::setw(4) << j << std::endl;
    write.close();
}

void JSONThingy::load(Name characterToLoad, Character &aCharacter) {

    if(!boost::filesystem::exists("./DataFiles/Characters/" + characterToLoad + ".json")) {
        return;
    }

    std::fstream fs;
    fs.open("./DataFiles/Characters/" + characterToLoad + ".json", std::fstream::in);
    if(!fs.fail()) {
        json j;
        fs >> j;
        fs.close();
        Character tmpChar = j.get<Character>();
        tmpChar.giveFullHP(); //todo change later
        aCharacter = tmpChar;

    }

}