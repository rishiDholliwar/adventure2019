#ifndef ALTERSPACE_COMBATCONTROLLER_H
#define ALTERSPACE_COMBATCONTROLLER_H

#include "Combat.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

class CombatController {
private:

    std::vector<Combat> battleList;

public:

    CombatController() = default;

    bool isNewBattle(const Name &instigator, const Name &target);

    void createNewBattle(Character &instigator, Character &target);

    std::string sendBattleRequest(const Character &fighter1, const Character &fighter2);

    bool battleReady(const Name &fighter1, const Name &fighter2);

    bool checkDuplicateSendRequest(const Name &instigator, const Name &target);

    bool replyPendingRequest(const Name &instigator, const Name &target);

    const std::string executeBattle(const Name &fighter1, const Name &fighter2, const Input &input);

    bool isGameOver(const Name &fighter1, const Name &fighter2);

    std::vector<Character> &getFighters(Name &fighter1, Name &fighter2);

    void deleteGame(const Name fighter1, const Name fighter2);

    std::string sendInvitationMsg(const Name &inviterName);

    std::string sendDuplicateRequestMsg(const Name &joiner);

    std::string selfAttack();

    std::string sendThreatMsg();

    std::string sendOwnerFightingMsg(const Name &target);

    std::string sendTargetFightingMsg(const Name &target);

    //TODO need specifc one for by name
    //for debug
    std::string printAllBattles();

private:

    Combat &getBattle(const Name fighter1, const Name fighter2);

    bool isBattleOwner(const Name fighter1, const Name fighter2);

    bool isBattleAssociation(const Name fighter1, const Name fighter2);
};

#endif //ALTERSPACE_COMBATCONTROLLER_H

/*
 *  std::string sendSurrenderMesg(const Name &surrenderer) {
        return surrenderer + " has surrendered";
    }


      //TODO surrender should remove character from fighters, if only 1 character left, delete game (if owner delete game)(Need to test if owner delted the game)
    //todo will need message for each individual to surrender as well as game quit message,
    //todo also message if they surrender to wrong person
    std::string surrender(const Name &joiner, const Name &owner) {
//        std::string output = "";
//        if (isBattle(owner)) {
//            auto battle = getBattle(owner);
//
//            //if owner is deleting there own game
//            if (joiner == battle.getOwner()) {
//                deleteGame(owner);
//                output += sendSurrenderMesg(owner);
//            }
//
//            if (battle.nameIsPendingWithOwner(joiner, owner)) {
//                battle.surrenderFighter(joiner);
//                output += sendSurrenderMesg(joiner);
//            }
//        }

        return "";
    }


    //TODO finish or test
    std::string surrenderFromOwner(const Name &owner) {
       // deleteGame(owner);
       return "";
    }
    //TODO finish
    bool ownerSurrender(Name &fighter1, Name &fighter2) {
//        if (isBattle(fighter1, fighter2)) {
//            auto battle = getBattle(fighter1, fighter2);
//            return battle.getFighters();
//        }
//        if (isBattle(owner)) {
//            //if owner is deleting there own game
//            if (joiner == getBattle(owner).getOwner()) {
//                return true;
//
//            }
//            return false;
//        }
        return false;
    }







 *
 *
 */