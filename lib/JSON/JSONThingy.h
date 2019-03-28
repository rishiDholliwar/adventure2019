//
// Created by bryan on 21/03/19.
//

#ifndef ALTERSPACE_JSONTHINGY_H
#define ALTERSPACE_JSONTHINGY_H

#include <Character.h>
#include <Object.h>
#include <ObjectController.h>
#include <Extra.h>
#include <CharacterController.h>
#include <json.hpp>
#include <boost/filesystem.hpp>
#include <iomanip>
#include <fstream>
#include <RoomController.h>
#include <CommandTranslator.h>
#include <ResetController.h>

using AlterSpace::Name;
using AlterSpace::ID;

using json = nlohmann::json;


class JSONThingy {
public:

    void save(Character &aCharacter);

    void load(Name characterToLoad, Character &aCharacter);

    void load(std::string areaToLoad, ObjectController &objects);

    void load(std::string areaToLoad, RoomController &roomController);

    void load(std::string language, CommandTranslator &aTranslator);

    void load(std::string areaToLoad, ResetController &resetController);
};


#endif //ALTERSPACE_JSONTHINGY_H
