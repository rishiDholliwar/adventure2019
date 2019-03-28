#ifndef ALTERSPACE_COMBAT_H
#define ALTERSPACE_COMBAT_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "Character.h"
#include "AlterSpace.h"

/*
 * Combat contains all the logic for a battle.
 */

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

    bool isGameOver = false;

    struct Fighter {
        bool readyForNextRound;
        Character fighter;
    };

    static const int MAX_NUM_PLAYERS = 2; //TODO try to make work for greater than 2 players

    int MAX_NUM_ROUNDS = 50; //used for quick attack todo change later

    struct Fighter fighterInstigator;
    struct Fighter fighterOpponent;
    int roundCounter = 0;

public:

    Combat() = default;

    void addInstigator(Character &instigator);

    void addOpponent(Character &opponent);

    Character &getInstigator();

    Character &getOpponent();

    const Name getInstigatorName();

    const Name getOpponentName();

    bool nameIsPendingWithInstigator(const Name &fighter1, const Name &fighter2);

    //TODO will be used when player can enter options for each round
    std::string processInput(const Input &input);

    bool battleReady();

    //todo modify names
    std::vector<Name> getOpponents();

    bool isInBattle(const Name &fighter);

    bool isNextRoundReady();

    void setPlayerReadyForNextRound(const Name &fighter);

    void resetRoundReady();

    void updateFighters(Character &fighter1, Character &fighter2);

    std::string runQuickBattle();

    std::string runBattleRound();

    std::string attack(Character &attacker, Character &defender);

    std::string printWinner(const Character &character);

    std::string printRoundNumber(int number);

    void setCombatState();

    bool isPendingState();

    bool isCombatState();

    bool isGameOverState();

    bool surrenderFighter(const Name &surrenderer);

private :

    void setState(STATE state);

    double attackMultiplier();

    int getNetDamage(unsigned int damage, unsigned int defence);

    int getDefenderHP(Character &defender, unsigned int netDamage);

    Character &getAttacker(int i);

    Character &getDefender(int i);

    std::string printAttackInfo(Character &attacker, Character &defender);

    std::string printAttackerDamage(Character &attacker, unsigned int damage);

    std::string printDefenderDefence(Character &defender, unsigned int defence);

    std::string printNetDamage(unsigned int netDamage);

    std::string printDefenderHP(Character &defender);
};

#endif //ALTERSPACE_COMBAT_H
