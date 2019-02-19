//
// Created on 2/18/2019.
//

#include <SpellController.h>
#include <Spells.h>
#include <StringLibrary.h>


SpellController::SpellController() {
    /*
     * Create table of available spells
     *
     * Format:
     * (SpellName , SpellType , ManaCost , SpellDamage)
     */
    SpellList.push_back(Spells(StringLibrary::spellSwap ,Spells::SpellType::CHARACTER,0,0));
    SpellList.push_back(Spells(StringLibrary::spellConfuse,Spells::SpellType::CHARACTER,0,0));
    SpellList.push_back(Spells(StringLibrary::spellDecoy,Spells::SpellType::COMBAT,0,0));
}

bool SpellController::doesSpellExist(std::string &spellName) {
    for(auto &spells : SpellList){
        if(spells.getName() == spellName){
            return true;
        }
    }
    return false;
}

Spells SpellController::getSpell(std::string &spellName) {
    Spells spell;
    for(auto &spell : SpellList){
        if(spell.getName() == spellName){
            return spell;
        }
    }
    return spell;
}


