#include "Combat.h"
#include <cmath>

void Combat::addFighter(Character &character) {
    fighters.push_back(character);
}

std::vector<Character> &Combat::getFighters() {
    return fighters;
}

const Name &Combat::getOwner() {
    return owner;
}

const Name &Combat::getNonOwner(const Name &fighter1, const Name &fighter2) {
    if (fighter1 == owner) {
        return fighter2;
    }

    if (fighter2 == owner) {
        return fighter1;
    }
}

std::string Combat::getPendingNames() {
    std::string output = "";
    for (auto &character : fighters) {
        if (character.getName() != owner) {
            output += character.getName();
            //output += ", ";
        }
    }

    return output;
}

bool Combat::nameIsPendingWithOwner(const Name &fighter1, const Name &fighter2) {
    if (Combat::getOwner() == fighter1) {
        for (auto &character : fighters) {
            if (character.getName() == fighter2) {
                return true;
            }
        }
    }

    if (Combat::getOwner() == fighter2) {
        for (auto &character : fighters) {
            if (character.getName() == fighter1) {
                return true;
            }
        }
    }

    return false;
}

//TODO will be used when player can enter options for each round
std::string Combat::processInput(const Input &input) {
    return "";
}

bool Combat::battleReady() {
    if (fighters.size() == MAX_NUM_PLAYERS) {
        return true;
    }

    return false;
}

void Combat::updateFighters(Character &f1, Character &f2) {
    fighters.clear();
    fighters.push_back(f1);
    fighters.push_back(f2);
}

std::string Combat::runCombat() {
    setCombatState();
    int roundCounter = 0;
    bool isWinner = false;
    std::string output;

    while (!isWinner) {
        roundCounter++;
        output += printRoundNumber(roundCounter);

        for (unsigned int i = 0; i < getFighters().size(); i++) {
            Character &attacker = getFighter(i);
            Character &defender = getFighter(getDefender(i));

            output += attack(attacker, defender);
            output += "\n";

            if (defender.getCurrentHP() == 0) {
                output += printWinner(attacker);
                output += "\n";
                isWinner = true;
                setEndState();
                break;
            }
        } //end for
    }// end while

    return output;
}

double Combat::attackMultiplier() {
    return rand() / (RAND_MAX + 1.);
}

int Combat::getDefender(int index) {
    if (index == (getFighters().size() - 1)) {
        return 0;
    } else {
        return index + 1;
    }
}

std::string Combat::attack(Character &attacker, Character &defender) {
    std::string attackString = "";

    attackString += printAttackInfo(attacker, defender);

    unsigned int damage = std::round(attacker.getAttack() * attackMultiplier());
    attackString += printAttackerDamage(attacker, damage);

    unsigned int defence = std::round(defender.getDefense() * attackMultiplier());
    attackString += printDefenderDefence(defender, defence);

    int netDamage = getNetDamage(damage, defence);
    attackString += printNetDamage(netDamage);

    int defenderHP = getDefenderHP(defender, netDamage);
    defender.setCurrentHP(defenderHP);
    attackString += printDefenderHP(defender);

    return attackString;
}

int Combat::getNetDamage(unsigned int damage, unsigned int defence) {
    int netDamage = damage - defence;
    if (netDamage < 0) {
        netDamage = 0;
    }

    return netDamage;
}

int Combat::getDefenderHP(Character &defender, unsigned int netDamage) {
    int defenderHP = defender.getCurrentHP() - netDamage;
    if (defenderHP < 0) {
        defenderHP = 0;
    }
    return defenderHP;
}

std::string Combat::printWinner(const Character &character) {
    return "\t" + character.getName() + " wins the fight\n";
}

std::string Combat::printRoundNumber(int number) {
    return "\tRound:" + std::to_string(number) + "\n";
}

std::string Combat::printAttackInfo(Character &attacker, Character &defender) {
    return "\t\t" + attacker.getName() + " attacks " + defender.getName() + " with "
           + std::to_string(defender.getCurrentHP()) + "hp" + "\n";
}

std::string Combat::printAttackerDamage(Character &attacker, unsigned int damage) {
    return "\t\t" + attacker.getName() + " damage is " + std::to_string(damage) + "\n";
}

std::string Combat::printDefenderDefence(Character &defender, unsigned int defence) {
    return "\t\t" + defender.getName() + " defence is " + std::to_string(defence) + "\n";
}

std::string Combat::printNetDamage(unsigned int netDamage) {
    return "\t\tNet Damage is " + std::to_string(netDamage) + "\n";
}

std::string Combat::printDefenderHP(Character &defender) {
    return "\t\t" + defender.getName() + " health is now " + std::to_string(defender.getCurrentHP()) + "hp"
           + "\n";
}

Character &Combat::getFighter(int i) {
    return fighters[i];
}

void Combat::setPendingState() {
    currentState = STATE::PENDING;
}

void Combat::setCombatState() {
    currentState = STATE::COMBAT;
}

void Combat::setEndState() {
    currentState = STATE::END;
}

bool Combat::isPendingState() {
    if (currentState == STATE::PENDING) {
        return true;
    }
    return false;
}

bool Combat::isCombatState() {
    if (currentState == STATE::COMBAT) {
        return true;
    }
    return false;
}

bool Combat::isGameOverState() {
    if (currentState == STATE::END) {
        return true;
    }
    return false;
}
