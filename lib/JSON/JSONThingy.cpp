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
    {PIGEONMAIL, "PIGEONMAIL"},

    //SPELLS
    {SWAP, "SWAP"},
    {CONFUSE, "CONFUSE"},
    {DECOY, "DECOY"},

    //COMBAT
    {COMBAT, "COMBAT"},
    {ATTACK, "ATTACK"},
    {BATTLES, "BATTLES"},
    {FLEE, "FLEE"},

    //MINI GAME
    {TTT, "TTT"},
    {TTTT, "TTTT"}



})

//Resets
void from_json(const json &j, Reset &reset) {
    auto action = j.at("action").get<std::string>();

    if (action == "npc") {
        reset = Reset(action,
                        j.at("id").get<int>(),
                        j.at("limit").get<int>(),
                        j.at("room").get<int>());
    } else if (action == "equip" || action == "give") {
        reset = Reset(action,
                        j.at("id").get<int>());
    } else if (action == "object") {
        reset = Reset(action,
                        j.at("id").get<int>(),
                        j.at("room").get<int>());
    } else if (action == "door") {
        reset = Reset(action,
                        j.at("id").get<int>(),
                        j.at("room").get<int>(),
                        j.at("state").get<std::string>());
    }
}

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

void to_json(json &j, const Extra &anExtra) {
    j = json{
            {"keywords", anExtra.getKeywords() },
            {"desc", anExtra.getDesc() }
    };
}

// RoomController
void from_json(const json &j, RoomController &roomController) {
    roomController = RoomController(j.at("ROOMS").get<std::vector<Room>>());
}

// Objects
void to_json(json &j, const Object &anObject) {
    j = json{
            {"id", anObject.getObjectID() },
            {"keywords", anObject.getKeywords() },
            {"shortdesc", anObject.getShortDesc() },
            {"longdesc", anObject.getLongDesc() },
            {"extra", anObject.getExtra() }
    };
}

void from_json(const json &j, Extra &extraDesc) {
    extraDesc = Extra(
        j.at("keywords").get<std::vector<std::string>>(),
        j.at("desc").get<std::vector<std::string>>());
}

void from_json(const json &j, Object &anObject) {
    anObject = Object(
        j.at("id").get<ID>(),
        j.at("keywords").get<std::vector<std::string>>(),
        j.at("shortdesc").get<std::string>(),
        j.at("longdesc").get<std::vector<std::string>>(),
        j.at("extra").get<std::vector<Extra>>());
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

    if ( !(aCharacter.isNPC()) ) {
        std::cout << "xD" << std::endl;
        j = json{
            { "name", aCharacter.getName() },
            { "roomID", aCharacter.getRoomID() },
            { "wearing", aCharacter.getWearing() },
            { "inventory", aCharacter.getInventory() },
        };
        std::cout << j.dump() << std::endl;
    }
}

void from_json(const json &j, Character &aCharacter) {

    auto isNPC = j.find("shortdesc");

    if (isNPC == j.end()) {
        aCharacter = Character(
            j.at("name").get<std::string>(),
            j.at("roomID").get<ID>(),
            j.at("inventory").get<Inventory>(),
            j.at("wearing").get<std::vector<Object>>());
    } else {
        aCharacter = Character(
            j.at("id").get<ID>(),
            j.at("keywords").get<std::vector<std::string>>(),
            j.at("shortdesc").get<std::string>(),
            j.at("longdesc").get<std::vector<std::string>>(),
            j.at("description").get<std::vector<std::string>>());
        aCharacter.setNPC();
    }

}

void from_json(const json &j, ObjectController &objects) {
    objects = ObjectController( j.at("OBJECTS").get<std::vector<Object>>());
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

void JSONThingy::load(std::string areaToLoad, ObjectController &objects) {
    if(!boost::filesystem::exists("./DataFiles/" + areaToLoad + ".json")) {
        return;
    }

    std::fstream fs;
    fs.open("./DataFiles/" + areaToLoad + ".json", std::fstream::in);
    if(!fs.fail()) {
        json j;
        fs >> j;
        fs.close();

        objects = j.get<ObjectController>();
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

    if(!boost::filesystem::exists("./DataFiles/internationalization.json")) {
        return;
    }

    std::fstream fs;
    fs.open("./DataFiles/internationalization.json", std::fstream::in);
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

void JSONThingy::load(std::string areaToLoad, ResetController &resetController) {
    if(!boost::filesystem::exists("./DataFiles/" + areaToLoad + ".json")) {
        std::cout << "room file not found" << std::endl;
        return;
    }

    std::fstream fs;
    fs.open("./DataFiles/" + areaToLoad + ".json", std::fstream::in);
    if(!fs.fail()) {
        json j;
        fs >> j;
        fs.close();

        resetController.addResets(j.at("RESETS").get<std::vector<Reset>>());
        resetController.addNPCs(j.at("NPCS").get<std::vector<Character>>());
    }
}