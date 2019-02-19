//
// Created on 2/18/2019.
//

#ifndef ALTERSPACE_SPELLCONTROLLER_H
#define ALTERSPACE_SPELLCONTROLLER_H

#include <Spells.h>
#include <vector>

class SpellController {
private:
    std::vector<Spells> SpellList;
public:
    /* Constructor */
    SpellController();

    /*
     *
     *
     */

    bool doesSpellExist(std::string &spellName);




};



#endif //ALTERSPACE_SPELLCONTROLLER_H
