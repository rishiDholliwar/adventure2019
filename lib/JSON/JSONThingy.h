//
// Created by bryan on 21/03/19.
//

#ifndef ALTERSPACE_JSONTHINGY_H
#define ALTERSPACE_JSONTHINGY_H

#include <Character.h>
#include <Object.h>
#include <json.hpp>
#include <boost/filesystem.hpp>


using AlterSpace::Name;
using AlterSpace::ID;

using json = nlohmann::json;


class JSONThingy {
private:

    void to_json(json &j, const Character &aCharacter);

    void from_json(const json &j, Character &aCharacter);

    void to_json(json &j, const Object &anObject);

    void from_json(const json &j, Object &anObject);

public:

    void save(Character &aCharacter);

    void load(Name characterToLoad, Character &aCharacter);
};


#endif //ALTERSPACE_JSONTHINGY_H
