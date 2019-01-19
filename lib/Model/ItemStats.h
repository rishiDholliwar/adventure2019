//
// Created by bshetty on 1/18/19.
//

#ifndef ALTERSPACE_ITEMSTATS_H
#define ALTERSPACE_ITEMSTATS_H


class ItemStats {

private:
    unsigned int health;
    unsigned int maxHealth;

    unsigned int mana;
    unsigned int maxMana;

    unsigned int strength;
    unsigned int defence;
    unsigned int intelligence;
    unsigned int dexterity;

public:

    ItemStats(unsigned int health, unsigned int maxHealth, unsigned int mana, unsigned int maxMana,
              unsigned int strength, unsigned int defence, unsigned int intelligence, unsigned int dexterity);

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

    virtual ~ItemStats();

};


#endif //ALTERSPACE_ITEMSTATS_H
