//
// Created by bshetty on 1/17/19.
//

#include <iostream>
#include <cmath>
#include "Character.h"

Character::Character(const std::string &userName, unsigned int level, unsigned int currentExp,
                     unsigned int expToNextLevel, unsigned int health, unsigned int maxHealth, unsigned int mana,
                     unsigned int maxMana, unsigned int strength, unsigned int defence, unsigned int intelligence,
                     unsigned int dexterity, const Inventory &inventory, const Equip &equipWeapon,
                     const Equip &equipArmor) : userName(userName), level(level), currentExp(currentExp),
                                                expToNextLevel(expToNextLevel), health(health), maxHealth(maxHealth),
                                                mana(mana), maxMana(maxMana), strength(strength), defence(defence),
                                                intelligence(intelligence), dexterity(dexterity), inventory(inventory),
                                                equipWeapon(equipWeapon), equipArmor(equipArmor) {}

unsigned int Character::getLevel() const {
    return level;
}

void Character::setLevel(unsigned int level) {
    Character::level = level;
}

unsigned int Character::getCurrentExp() const {
    return currentExp;
}

void Character::setCurrentExp(unsigned int currentExp) {
    Character::currentExp = currentExp;
}

unsigned int Character::getExpToNextLevel() const {
    return expToNextLevel;
}

void Character::setExpToNextLevel(unsigned int expToNextLevel) {
    Character::expToNextLevel = expToNextLevel;
}

unsigned int Character::getHealth() const {
    return health;
}

void Character::setHealth(unsigned int health) {
    Character::health = health;
}

unsigned int Character::getMaxHealth() const {
    return maxHealth;
}

void Character::setMaxHealth(unsigned int maxHealth) {
    Character::maxHealth = maxHealth;
}

unsigned int Character::getMana() const {
    return mana;
}

void Character::setMana(unsigned int mana) {
    Character::mana = mana;
}

unsigned int Character::getMaxMana() const {
    return maxMana;
}

void Character::setMaxMana(unsigned int maxMana) {
    Character::maxMana = maxMana;
}

unsigned int Character::getStrength() const {
    return strength;
}

void Character::setStrength(unsigned int strength) {
    Character::strength = strength;
}

unsigned int Character::getDefence() const {
    return defence;
}

void Character::setDefence(unsigned int defence) {
    Character::defence = defence;
}

unsigned int Character::getIntelligence() const {
    return intelligence;
}

void Character::setIntelligence(unsigned int intelligence) {
    Character::intelligence = intelligence;
}

unsigned int Character::getDexterity() const {
    return dexterity;
}

void Character::setDexterity(unsigned int dexterity) {
    Character::dexterity = dexterity;
}

const Inventory &Character::getInventory() const {
    return inventory;
}

void Character::setInventory(const Inventory &inventory) {
    Character::inventory = inventory;
}

const Equip &Character::getEquipWeapon() const {
    return equipWeapon;
}

void Character::setEquipWeapon(const Equip &equipWeapon) {
    Character::equipWeapon = equipWeapon;
}

const Equip &Character::getEquipArmor() const {
    return equipArmor;
}

void Character::setEquipArmor(const Equip &equipArmor) {
    Character::equipArmor = equipArmor;
}

const std::string &Character::getUserName() const {
    return userName;
}

Character::~Character() {

}

bool Character::canLevelUp() {
    return currentExp >= expToNextLevel;
}

void Character::levelUp() {
    level++;
    currentExp = 0;
    expToNextLevel = experienceToNextLevel();
}

unsigned int Character::experienceToNextLevel() {
    return static_cast<unsigned int>(4 * (pow(level, 3)));
}

bool Character::equipNewWeapon(Item &item) {
    if(inventory.hasSpace()){
        inventory.store(getEquipWeapon());
        setEquipWeapon(Equip(item));
        return true;
    }else {
        return false;
    }
}

bool Character::equipNewArmor(Item &item) {
    if(inventory.hasSpace()){
        inventory.store(getEquipArmor());
        setEquipArmor(Equip(item));
        return true;
    }else {
        return false;
    }
}

