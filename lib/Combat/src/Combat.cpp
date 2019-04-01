#include "Combat.h"
#include <cmath>
#include <sstream>

//todo go to vector to non vector!!!
void Combat::addInstigator(Character &instigator) {
    fighterInstigator.fighter = instigator;
}




void Combat::addOpponent(Character &opponent) {
    fighterOpponent.fighter = opponent;
}

Character &Combat::getInstigator() {
    return fighterInstigator.fighter;
}

Character &Combat::getOpponent() {
    return fighterOpponent.fighter;
}

const Name Combat::getInstigatorName() {
    return fighterInstigator.fighter.getName();
}

const Name Combat::getOpponentName() {
    return fighterOpponent.fighter.getName();
}

//todo refactor
bool Combat::nameIsPendingWithInstigator(const Name &fighter1, const Name &fighter2) {
    if (getInstigatorName() == fighter1) {
        if (getOpponentName() == fighter2) {
            return true;
        }
    }

    if (getInstigatorName() == fighter2) {
        if (getOpponentName() == fighter1) {
            return true;
        }
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

    std::cout << fighter1.getName() << std::endl;
    if (fighter1.getName() == fighterInstigator.fighter.getName()) {
        addInstigator(fighter1);
        addOpponent(fighter2);

        std::cout << fighter1.getName() << std::endl;
    } else {
        addInstigator(fighter2);
        addOpponent(fighter1);

        std::cout << fighter1.getName() << std::endl;
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
            //setState(STATE::END); //todo this breaks the code, no idea why??
            isGameOver = true;
            return output.str();
        }

    } //end for

    return output.str();
}

Character &Combat::getAttacker(int i) {
    if (i % 2) {
        return fighterInstigator.fighter;
    }
    return fighterOpponent.fighter;
}

Character &Combat::getDefender(int i) {
    if (i % 2) {
        return fighterOpponent.fighter;
    }
    return fighterInstigator.fighter;
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

    int netDamage = getNetDamage(damage, defence);
    attackString << printNetDamage(netDamage);

    int defenderHP = getDefenderHP(defender, netDamage);
    defender.setCurrentHP(defenderHP);
    attackString << printDefenderHP(defender);

    return attackString.str();
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

void Combat::setState(STATE state) {
    this->currentState = state;
}

bool Combat::isPendingState() {
    if (this->currentState == STATE::PENDING) {
        return true;
    }
    return false;
}

bool Combat::isCombatState() {
    if (this->currentState == STATE::COMBAT) {
        return true;
    }
    return false;
}

bool Combat::isGameOverState() {
    return isGameOver;
}

bool Combat::isFleeState() {
    return isFlee;
}

bool Combat::isDecoyState(){
    return isDecoy;
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

void Combat::setDecoyState(){
    isDecoy = true;
}

void Combat::setTargetLogoutState() {
    isTargetLogout = true;
}

std::string Combat::logout(const Name &winner) {
    Character winnerCharacter;
    if (winner != getInstigatorName()) {
        winnerCharacter = fighterInstigator.fighter;
    } else {
        winnerCharacter = fighterOpponent.fighter;
    }

    std::stringstream output;
    output << printWinner(winnerCharacter);
    isGameOver = true;
    return output.str();

}

std::string Combat::flee(const Name &surrenderer) {
    Character winner;
    if (surrenderer != getInstigatorName()) {
        winner = fighterInstigator.fighter;
    } else {
        winner = fighterOpponent.fighter;
    }
    isFlee = true;
    std::stringstream output;
    output << printWinner(winner);
    isGameOver = true;
    return output.str();

}