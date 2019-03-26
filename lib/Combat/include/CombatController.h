#ifndef ALTERSPACE_COMBATCONTROLLER_H
#define ALTERSPACE_COMBATCONTROLLER_H

#include "Combat.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

/*
 * Combat controller is used to handle combat.
 * Currently combat is only 1 vs 1  and all rounds is executed in once instance.
 */

class CombatController {
private:

    std::vector<Combat> battleList;

public:

    CombatController() = default;

    bool isInBattleState(const Name &fighter);

    bool isNewBattle(const Name &instigator, const Name &target);

    void createNewBattle(Character &instigator, Character &target);

    std::string sendQuickBattleRequest(const Character &fighter1, const Character &fighter2);

    std::string sendRoundBattleRequest(const Character &fighter1, const Character &fighter2);

    bool battleReady(const Name &fighter1, const Name &fighter2);

    bool checkDuplicateSendRequest(const Name &instigator, const Name &target);

    bool replyPendingRequest(const Name &instigator, const Name &target);

    void setCombatState(const Name &instigator, const Name &target);

    bool isBattleStarted(const Name &fighter1, const Name &fighter2);

    const std::string executeQuickBattle(Character &fighter1, Character &fighter2, const Input &input);

    const std::string executeBattleRound(Character &fighter1, Character &fighter2, const Input &input);

    bool isGameOver(const Name &fighter1, const Name &fighter2);

    std::vector<Character> &getFighters(Name &fighter1, Name &fighter2);

    void deleteGame(const Name fighter1, const Name fighter2);

    std::string sendQInvitationMsg(const Name &inviterName);

    std::string sendRoundInvitationMsg(const Name &inviterName);

    std::string sendDuplicateRequestMsg(const Name &joiner);

    std::string selfAttackMsg();

    std::string sendThreatMsg();

    std::string sendOwnerFightingMsg(const Name &target);

    std::string sendTargetFightingMsg(const Name &target);

    std::string printAllBattles();

private:

    Combat &getBattle(const Name fighter1, const Name fighter2);

    bool isBattleOwner(const Name fighter1, const Name fighter2);

    bool isBattleAssociation(const Name fighter1, const Name fighter2);
};

#endif //ALTERSPACE_COMBATCONTROLLER_H
