
#include <Spells.h>

std::string Spells::getName() {
    return this->name;
}

unsigned int Spells::getManaCost() {
    return this->manaCost;
}

Spells::SpellType Spells::getType() {
    return this->type;
}

unsigned int Spells::getSpellDamage() {
    return this->spellDamage;
}
