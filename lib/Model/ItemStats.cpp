//
// Created by bshetty on 1/18/19.
//

#include "ItemStats.h"

ItemStats::ItemStats(unsigned int health, unsigned int maxHealth, unsigned int mana, unsigned int maxMana,
                     unsigned int strength, unsigned int defence, unsigned int intelligence, unsigned int dexterity)
        : health(health), maxHealth(maxHealth), mana(mana), maxMana(maxMana), strength(strength), defence(defence),
          intelligence(intelligence), dexterity(dexterity) {}

unsigned int ItemStats::getHealth() const {
    return health;
}

void ItemStats::setHealth(unsigned int health) {
    ItemStats::health = health;
}

unsigned int ItemStats::getMaxHealth() const {
    return maxHealth;
}

void ItemStats::setMaxHealth(unsigned int maxHealth) {
    ItemStats::maxHealth = maxHealth;
}

unsigned int ItemStats::getMana() const {
    return mana;
}

void ItemStats::setMana(unsigned int mana) {
    ItemStats::mana = mana;
}

unsigned int ItemStats::getMaxMana() const {
    return maxMana;
}

void ItemStats::setMaxMana(unsigned int maxMana) {
    ItemStats::maxMana = maxMana;
}

unsigned int ItemStats::getStrength() const {
    return strength;
}

void ItemStats::setStrength(unsigned int strength) {
    ItemStats::strength = strength;
}

unsigned int ItemStats::getDefence() const {
    return defence;
}

void ItemStats::setDefence(unsigned int defence) {
    ItemStats::defence = defence;
}

unsigned int ItemStats::getIntelligence() const {
    return intelligence;
}

void ItemStats::setIntelligence(unsigned int intelligence) {
    ItemStats::intelligence = intelligence;
}

unsigned int ItemStats::getDexterity() const {
    return dexterity;
}

void ItemStats::setDexterity(unsigned int dexterity) {
    ItemStats::dexterity = dexterity;
}

ItemStats::~ItemStats() {

}


