//
// Created by bryan on 21/03/19.
//

#include "JSONThingy.h"



void JSONThingy::to_json(json &j, const Object &anObject) {
    j = json::array({
            {"objectID", anObject.getID() },
            {"objectName", anObject.getName() }
    });
}

void JSONThingy::from_json(const json &j, Object &anObject) {
    anObject = Object( j.at("objectID").get<ID>(), j.at("objectName").get<Name>());
}

void JSONThingy::to_json(json &j, const Character &aCharacter) {

    j = json::array({
            { "name", aCharacter.getName() },
            { "roomID", aCharacter.getRoomID() },
            { "confused", aCharacter.isConfused() },
            { "wearing", aCharacter.getWearing() },
            { "inventory", aCharacter.getInventory() },
    });

//    j["name"] = aCharacter.getName();
//    j["roomID"] = aCharacter.getRoomID();
//    j["confused"] = aCharacter.isConfused();
//    j[""]
}



void JSONThingy::from_json(const json &j, Character &aCharacter) {
    aCharacter = Character(
            j.at("name").get<std::string>(),
            j.at("roomID").get<ID>(),
            j.at("inventory").get<std::vector<Object>>(),
            j.at("wearing").get<std::vector<Object>>(),
            j.at("confused").get<bool>());
}






void JSONThingy::save(Character &aCharacter) {
    json j;

    to_json(j, aCharacter);

    if(!boost::filesystem::exists("DataFiles/Character/")) {
        boost::filesystem::create_directory("DataFiles/Character/");
    }

    std::ofstream write("DataFiles/Characters/" + aCharacter.getName() + ".json");
    write << std::setw(4) << j << std::endl;
}

void JSONThingy::load(Name characterToLoad, Character &aCharacter) {

    if(!boost::filesystem::exists("DataFiles/Character/" + characterToLoad + ".json")) {
        return;
    }

    fstream fs;
    fs.open("DataFiles/Character/" + characterToLoad + ".json", fstream::in);
    if(!fs.fail) {
        json j;
        fs >> j;

        Character tmpChar = j.get<Character>();
        aCharacter = tmpChar;

    }

}