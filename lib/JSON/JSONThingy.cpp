#include "JSONThingy.h"
#include <Door.h>
#include <ExtendedDescription.h>
#include <Room.h>
#include <iostream>

// map TaskState values to JSON as strings
NLOHMANN_JSON_SERIALIZE_ENUM( CommandType, {
    //USE
    {LOGIN, "LOGIN"},
    {LOGOUT, "LOGOUT"},
    {SIGNUP, "SIGNUP"},

    //COMMUNICATION
    {SAY, "SAY"},
    {YELL, "YELL"},
    {BROADCAST, "BROADCAST"},
    {TELL, "TELL"},
    {WHISPER, "WHISPER"},

    //MOVEMENT
    {MOVE, "MOVE"},
    {NORTH, "NORTH"},
    {SOUTH, "SOUTH"},
    {WEST, "WEST"},
    {EAST, "EAST"},
    {NORTHWEST, "NORTHWEST"},
    {NORTHEAST, "NORTHEAST"},
    {SOUTHWEST, "SOUTHWEST"},
    {SOUTHEAST, "SOUTHEAST"},

    //INFORMATION
    {HELP, "HELP"},
    {INFO, "INFO"},
    {LOOK, "LOOK"},
    {EXAMINE, "EXAMINE"},
    {INVENTORY, "INVENTORY"},

    //ITEMS
    {PICKUP, "PICKUP"},
    {DROP, "DROP"},
    {GIVE, "GIVE"},
    {WEAR, "WEAR"},
    {TAKEOFF, "TAKEOFF"},

    //SPELLS
    {SWAP, "SWAP"},
    {CONFUSE, "CONFUSE"},
    {DECOY, "DECOY"}
})

// Doors
void from_json(const json &j, Door &aDoor) {
    aDoor = Door(j.at("dir").get<std::string>(),
                 j.at("desc").get<std::vector<std::string>>(),
                 j.at("keywords").get<std::vector<std::string>>(),
                 j.at("to").get<int>());
}

// Extended Descriptions
void from_json(const json &j, ExtendedDescription &extendedDescription) {
    extendedDescription = ExtendedDescription(
            j.at("keywords").get<std::vector<std::string>>(),
            j.at("desc").get<std::vector<std::string>>());
}

// Rooms
void from_json(const json &j, Room &aRoom) {
    aRoom = Room(j.at("id").get<int>(),
                 j.at("name").get<std::string>(),
                 j.at("desc").get<std::vector<std::string>>(),
                 j.at("doors").get<std::vector<Door>>(),
                 j.at("extended_descriptions").get<std::vector<ExtendedDescription>>());
}

// RoomController
void from_json(const json &j, RoomController &roomController) {
    roomController = RoomController(j.at("ROOMS").get<std::vector<Room>>());
}

// Objects
void to_json(json &j, const Object &anObject) {
    j = json{
            {"objectID", anObject.getID() },
            {"objectName", anObject.getName() }
    };
}

void from_json(const json &j, Object &anObject) {
    anObject = Object( j.at("objectID").get<ID>(), j.at("objectName").get<Name>());
}

// Inventory
void to_json(json &j, const Inventory &anInventory) {
    j = json{
            {"objects", anInventory.getObjects() }
    };
}

void from_json(const json &j, Inventory &anInventory) {
    anInventory = Inventory( j.at("objects").get<std::vector<Object>>());
}

// Characters
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
        aCharacter = tmpChar;

    }

}

void JSONThingy::load(std::string areaToLoad, RoomController &roomController) {

    if(!boost::filesystem::exists("./DataFiles/" + areaToLoad + ".json")) {
        std::cout << "room file not found" << std::endl;
        return;
    }

    std::cout << "file found" << std::endl;
    std::fstream fs;
    fs.open("./DataFiles/" + areaToLoad + ".json", std::fstream::in);
    if(!fs.fail()) {
        json j;
        fs >> j;
        fs.close();
        roomController = j.get<RoomController>();
    }
}

void JSONThingy::load(std::string language, CommandTranslator &aTranslator) {

    if(!boost::filesystem::exists("./DataFiles/internalization.json")) {
        return;
    }

    std::fstream fs;
    fs.open("./DataFiles/internalization.json", std::fstream::in);
    if(!fs.fail()) {
        json j;
        fs >> j;
        fs.close();
        std::map<std::string, CommandType> tmp = j.at(language).get<std::map<std::string, CommandType>>();
        for(auto& t : tmp) {
            aTranslator.registerTranslation(t.first, t.second);
        }

    }

}
