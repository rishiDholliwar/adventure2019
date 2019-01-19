//
// Created by bshetty on 1/17/19.
//

#ifndef ALTERSPACE_CHARACTER_H
#define ALTERSPACE_CHARACTER_H


#include <string>
#include "Equip.h"
#include "Inventory.h"

class Character {

private:

    std::string userName;

    unsigned int level;
    unsigned int currentExp;
    unsigned int expToNextLevel;

    unsigned int health;
    unsigned int maxHealth;

    unsigned int mana;
    unsigned int maxMana;

    unsigned int strength;
    unsigned int defence;
    unsigned int intelligence;
    unsigned int dexterity;

    Inventory inventory;

    Equip equipWeapon;
    Equip equipArmor;

public:
    Character(const std::string &userName, unsigned int level, unsigned int currentExp, unsigned int expToNextLevel,
              unsigned int health, unsigned int maxHealth, unsigned int mana, unsigned int maxMana,
              unsigned int strength, unsigned int defence, unsigned int intelligence, unsigned int dexterity,
              const Inventory &inventory, const Equip &equipWeapon, const Equip &equipArmor);

    unsigned int getLevel() const;

    void setLevel(unsigned int level);

    unsigned int getCurrentExp() const;

    void setCurrentExp(unsigned int currentExp);

    unsigned int getExpToNextLevel() const;

    void setExpToNextLevel(unsigned int expToNextLevel);

    unsigned int getHealth() const;

    void setHealth(unsigned int health);

    unsigned int getMaxHealth() const;

    void setMaxHealth(unsigned int maxHealth);

    unsigned int getMana() const;

    void setMana(unsigned int mana);

    unsigned int getMaxMana() const;

    void setMaxMana(unsigned int maxMana);

    unsigned int getStrength() const;

    void setStrength(unsigned int strength);

    unsigned int getDefence() const;

    void setDefence(unsigned int defence);

    unsigned int getIntelligence() const;

    void setIntelligence(unsigned int intelligence);

    unsigned int getDexterity() const;

    void setDexterity(unsigned int dexterity);

    const Inventory &getInventory() const;

    void setInventory(const Inventory &inventory);

    const Equip &getEquipWeapon() const;

    void setEquipWeapon(const Equip &equipWeapon);

    const Equip &getEquipArmor() const;

    void setEquipArmor(const Equip &equipArmor);

    const std::string &getUserName() const;

    virtual ~Character();

    bool canLevelUp();

    void levelUp();

    unsigned int experienceToNextLevel();

    bool equipNewWeapon(Item &item);

    bool equipNewArmor(Item &item);
};


#endif //ALTERSPACE_CHARACTER_H
