#include "Combat.h"
#include <cmath>
#include <sstream>

Character &Combat::getInstigator() {
    return fighterInstigator;
}

Character &Combat::getOpponent() {
    return fighterOpponent;
}

const Name Combat::getInstigatorName() {
    return fighterInstigator.getName();
}

const Name Combat::getOpponentName() {
    return fighterOpponent.getName();
}

bool Combat::nameIsPendingWithInstigator(const Name &fighter1, const Name &fighter2) {
    if (getInstigatorName() == fighter1 && getOpponentName() == fighter2) {
        return true;
    }

    if (getInstigatorName() == fighter2 && getOpponentName() == fighter1) {
        return true;
    }

    return false;
}

bool Combat::isInBattle(const Name &fighter) {
    if (getInstigatorName() == fighter || getOpponentName() == fighter) {
        return true;
    }

    return false;
}

bool Combat::battleReady() {
    if (getInstigatorName().empty() && getOpponentName().empty()) {
        return false;
    }

    return true;
}

void Combat::updateFighters(Character &fighter1, Character &fighter2) {
    if (fighter1.getName() == fighterInstigator.getName()) {
        fighterInstigator = fighter1;
        fighterOpponent = fighter2;
    } else {
        fighterInstigator = fighter2;
        fighterOpponent = fighter1;
    }
}

std::string Combat::runBattleRound() {
    std::stringstream output;

    this->roundCounter++;
    output << printRoundNumber(this->roundCounter);

    for (unsigned int i = 0; i < MAX_NUM_PLAYERS; i++) {

        Character &attacker = getAttacker(i);
        Character &defender = getDefender(i);

        output << attack(attacker, defender);
        output << "\n";

        if (defender.getCurrentHP() == 0) {
            output << printWinner(attacker);
            // setState(STATE::END); //todo this breaks the code, no idea why??
            isGameOver = true;
            return output.str();
        }

    } //end for

    return output.str();
}

Character &Combat::getAttacker(int i) {
    if (i % 2) {
        return fighterInstigator;
    }
    return fighterOpponent;
}

Character &Combat::getDefender(int i) {
    if (i % 2) {
        return fighterOpponent;
    }
    return fighterInstigator;
}

double Combat::attackMultiplier() {
    return rand() / (RAND_MAX + 1.);
}

std::string Combat::attack(Character &attacker, Character &defender) {
    std::stringstream attackString;

    attackString << printAttackInfo(attacker, defender);

    unsigned int damage = std::round(attacker.getAttack() * attackMultiplier());
    attackString << printAttackerDamage(attacker, damage);

    unsigned int defence = std::round(defender.getDefense() * attackMultiplier());
    attackString << printDefenderDefence(defender, defence);

    int netDamage = updateNetDamage(damage, defence);
    attackString << printNetDamage(netDamage);

    int defenderHP = updateDefenderHP(defender, netDamage);
    defender.setCurrentHP(defenderHP);
    attackString << printDefenderHP(defender);

    return attackString.str();
}

int Combat::updateNetDamage(unsigned int damage, unsigned int defence) {
    int netDamage = damage - defence;
    if (netDamage < 0) {
        netDamage = 0;
    }

    return netDamage;
}

int Combat::updateDefenderHP(Character &defender, unsigned int netDamage) {
    int defenderHP = defender.getCurrentHP() - netDamage;
    if (defenderHP < 0) {
        defenderHP = 0;
    }

    return defenderHP;
}

std::string Combat::printWinner(const Character &character) {
    std::stringstream ss;
    ss << "\t" << character.getName() << " wins the fight\n";
    return ss.str();
}

std::string Combat::printRoundNumber(int number) {
    std::stringstream ss;
    ss << "\tRound:" << std::to_string(number) << "\n";
    return ss.str();
}

std::string Combat::printAttackInfo(Character &attacker, Character &defender) {
    std::stringstream ss;
    ss << "\t\t" << attacker.getName() << " attacks " << defender.getName() << " with "
       << std::to_string(defender.getCurrentHP()) << "hp" << "\n";
    return ss.str();
}

std::string Combat::printAttackerDamage(Character &attacker, unsigned int damage) {
    std::stringstream ss;
    ss << "\t\t" << attacker.getName() << " damage is " << std::to_string(damage) << "\n";
    return ss.str();
}

std::string Combat::printDefenderDefence(Character &defender, unsigned int defence) {
    std::stringstream ss;
    ss << "\t\t" << defender.getName() << " defence is " << std::to_string(defence) << "\n";
    return ss.str();
}

std::string Combat::printNetDamage(unsigned int netDamage) {
    std::stringstream ss;
    ss << "\t\tNet Damage is " << std::to_string(netDamage) << "\n";
    return ss.str();
}

std::string Combat::printDefenderHP(Character &defender) {
    std::stringstream ss;
    ss << "\t\t" << defender.getName() << " health is now " << std::to_string(defender.getCurrentHP()) << "hp"
       << "\n";
    return ss.str();
}

void Combat::setState(STATE state) {
    this->currentState = state;
}

bool Combat::isPendingState() {
    return this->currentState == STATE::PENDING;
}

bool Combat::isCombatState() {
    return this->currentState == STATE::COMBAT;
}

bool Combat::isGameOverState() {
    // return this->currentState == STATE::END;
    return isGameOver;
}

bool Combat::isFleeState() {
    return isFlee;
}

bool Combat::isTargetLogoutState() {
    return isTargetLogout;
}

void Combat::setCombatState() {
    setState(STATE::COMBAT);
}

void Combat::setFleeState() {
    isFlee = true;
}

void Combat::setTargetLogoutState() {
    isTargetLogout = true;
}

std::string Combat::logout(const Name &winner) {
    std::stringstream output;
    if (winner != getInstigatorName()) {
        output << printWinner(fighterInstigator);
    } else {
        output << printWinner(fighterOpponent);
    }

    isGameOver = true;
    return output.str();
}

std::string Combat::flee(const Name &winner) {
    std::stringstream output;
    if (winner != getInstigatorName()) {
        output << printWinner(fighterInstigator);
    } else {
        output << printWinner(fighterOpponent);
    }

    isFlee = true;
    isGameOver = true;
    return output.str();
}
