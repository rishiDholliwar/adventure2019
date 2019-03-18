#ifndef ALTERSPACE_COMBAT_H
#define ALTERSPACE_COMBAT_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "Character.h"
#include "AlterSpace.h"

using AlterSpace::Name;
using AlterSpace::ID;
using AlterSpace::Input;

class Combat {
private:

    enum class STATE {
        PENDING,
        COMBAT,
        END
    };
    STATE currentState;

    static const int MAX_NUM_PLAYERS = 2; //TODO try to make work for greater than 2 players

    std::vector<Character> fighters;
    Name owner;

public:

    Combat() = default;

    Combat(Character &owner) {
        srand(static_cast<unsigned int>(time(0)));
        setPendingState();
        this->owner = owner.getName();
        addFighter(owner);
    };

    void addFighter(Character &character);

    std::vector<Character> &getFighters();

    const Name &getOwner();

    const Name &getNonOwner(const Name &fighter1, const Name &fighter2);

    bool nameIsPendingWithOwner(const Name &joiner, const Name &owner);

    std::string getPendingNames();

    //TODO will be used when player can enter options for each round
    std::string processInput(const Input &input);

    bool battleReady();

    std::string runCombat();

    std::string attack(Character &attacker, Character &defender);

    std::string printWinner(const Character &character);

    std::string printRoundNumber(int number);

    bool isPendingState();

    bool isCombatState();

    bool isGameOverState();

    bool surrenderFighter(const Name &surrenderer);

private :

    Character &getFighter(int i);

    void setPendingState();

    void setCombatState();

    void setEndState();

    double attackMultiplier();

    int getNetDamage(unsigned int damage, unsigned int defence);

    int getDefenderHP(Character &defender, unsigned int netDamage);

    int getDefender(int index);

    std::string printAttackInfo(Character &attacker, Character &defender);

    std::string printAttackerDamage(Character &attacker, unsigned int damage);

    std::string printDefenderDefence(Character &defender, unsigned int defence);

    std::string printNetDamage(unsigned int netDamage);

    std::string printDefenderHP(Character &defender);
};

#endif //ALTERSPACE_COMBAT_H
