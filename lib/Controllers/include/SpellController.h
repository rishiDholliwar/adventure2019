//
// Created on 2/18/2019.
//

#ifndef ALTERSPACE_SPELLCONTROLLER_H
#define ALTERSPACE_SPELLCONTROLLER_H

#include <Spells.h>
#include <vector>

class SpellController {
public:

private:
    std::vector<Spells> SpellList;
public:
    /* Constructor */
    SpellController();

    /*
     *
     *
     */
    /*
     * Return a string of default spells
     *
     * Pre-Condition: determine a list of default spells (right now its all spells)
     *
     * Post-Condition: return a vector of default spell names
     */
    std::vector<std::string> getDefaultSpells();

    /*
     * Checks if a spell exists in the world
     *
     * Pre-Condition: a given spell name
     *
     * Post-Condition: true if the spell exists in the world
     */
    bool doesSpellExist(std::string &spellName);




};



#endif //ALTERSPACE_SPELLCONTROLLER_H
