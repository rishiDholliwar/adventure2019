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
 * Currently combat is only 1 vs 1 against users and not npcs.
 */

class CombatController {
private:

    std::vector<Combat> battleList;

public:

    CombatController() = default;

    bool isBattleState(const Name &instigator);

    bool isNewBattle(const Name &instigator, const Name &target);

    void createNewBattle(Character &instigator, Character &target);

    std::string sendRoundBattleRequest(const Character &fighter1, const Character &fighter2);

    bool battleReady(const Name &fighter1, const Name &fighter2);

    bool checkDuplicateSendRequest(const Name &instigator, const Name &target);

    bool replyBattleRequest(const Name &instigator, const Name &target);

    void setCombatState(const Name &instigator, const Name &target);

    const Name getTargetName(const Name &instigator);

    Character &getFighter(Name &fighterName);

    const std::string executeBattleRound(Character &fighter1, Character &fighter2, const Input &input);

    bool isBattleOver(const Name &fighter);

    void deleteBattle(const Name fighter1, const Name fighter2);

    bool isFleeState(Name &fighter);

    void setFleeState(Name &fighter);

    bool isTargetLogoutState(Name &fighter);

    void setTargetLogoutState(Name &fighter);

    std::string logout(Name &winner);

    const std::string flee(Character &fighter1, Character &fighter2, const Input &input);

    std::string printAllBattles();

    std::string sendRoundInvitationMsg(const Name &inviterName);

    std::string sendDuplicateRequestMsg(const Name &joiner);

    std::string selfAttackMsg();

    std::string sendThreatMsg();

    std::string sendBattleStartedMsg();

    std::string sendCharacterNotFoundMsg(const Name &target);

    std::string sendTargetInCombatState(const Name &target);

    std::string sendTargetOfflineMsg();

    std::string sendNotInBattleMsg();

    std::string sendYouFledMsg(std::string direction);

    std::string sendTargetFledMsg();

private:

    Combat &getBattle(const Name fighter1, const Name fighter2);

    Combat &getBattleInCombatState(const Name &fighter);

    bool isBattleOwner(const Name fighter1, const Name fighter2);

    bool isBattleAssociation(const Name fighter1, const Name fighter2);
};

#endif //ALTERSPACE_COMBATCONTROLLER_H
