
#include <Spells.h>
#include <string>

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

Spells::Spells(const std::string &name, Spells::SpellType spellType, unsigned int manaCost, unsigned int spellDamage) : name(name),
                                                                                                                        type(spellType),
                                                                                                                        manaCost(manaCost),
                                                                                                                        spellDamage(spellDamage){}

Spells::Spells() = default;

