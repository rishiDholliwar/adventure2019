//
// Created on 2/9/2019.
//

#ifndef ALTERSPACE_SPELLS_H
#define ALTERSPACE_SPELLS_H

#include <string>

class Spells{
public:
    enum class SpellType{
        COMBAT,
        CHARACTER,
        DEFAULT
    };
    Spells();
    Spells(const std::string &name, SpellType spellType, unsigned int manaCost, unsigned int spellDamage);
    std::string getName();
    SpellType getType();
    unsigned int getManaCost();
    unsigned int getSpellDamage();
private:
    std::string name;
    SpellType type;
    unsigned int manaCost;
    unsigned int spellDamage;

};







#endif //ALTERSPACE_SPELLS_H
