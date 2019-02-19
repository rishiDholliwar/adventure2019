//
// Created on 2/18/2019.
//

#include <SpellController.h>
#include <Spells.h>


SpellController::SpellController() {
    /*
     * Create table of available spells
     *
     * Format:
     * (SpellName , SpellType , ManaCost , SpellDamage)
     */
    SpellList.push_back(Spells("swap",Spells::SpellType::CHARACTER,0,0));
    SpellList.push_back(Spells("confuse",Spells::SpellType::CHARACTER,0,0));
    SpellList.push_back(Spells("decoy",Spells::SpellType::COMBAT,0,0));
}

bool SpellController::doesSpellExist(std::string &spellName) {
    for(auto &spells : SpellList){
        if(spells.getName() == spellName){
            return true;
        }
    }
    return false;
}
