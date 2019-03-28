#include "CombatController.h"
#include "Combat.h"
//todo error, not finding specific game
bool CombatController::isNewBattle(const Name &instigator, const Name &target) {
    return (!isBattleAssociation(instigator, target));
}

void CombatController::createNewBattle(Character &instigator, Character &target) {
    battleList.push_back(Combat());
    battleList.back().addInstigator(instigator);
    battleList.back().addOpponent(target);
}

//std::string CombatController::sendQuickBattleRequest(const Character &fighter1, const Character &fighter2) {
//    if (isBattleOwner(fighter1.getName(), fighter2.getName())) {
//        auto &battle = getBattle(fighter1.getName(), fighter2.getName());
//        auto owner = battle.getOwner();
//        if (owner == fighter1.getName()) {
//            return sendQInvitationMsg(fighter1.getName());
//        } else {
//            return sendQInvitationMsg(fighter2.getName());
//        }
//    }
//
//    return "error sending invite";
//}

std::string CombatController::sendRoundBattleRequest(const Character &fighter1, const Character &fighter2) {
    if (isBattleOwner(fighter1.getName(), fighter2.getName())) {
        auto &battle = getBattle(fighter1.getName(), fighter2.getName());
        auto &instigator = battle.getInstigator();

        if (instigator.getName() == fighter1.getName()) {
            return sendRoundInvitationMsg(fighter1.getName());
        } else {
            return sendRoundInvitationMsg(fighter2.getName());
        }
    }

    return "error sending invite";
}

//todo fix or see if needed
bool CombatController::battleReady(const Name &fighter1, const Name &fighter2) {
    if (isBattleAssociation(fighter1, fighter2)) {
        auto &battle = getBattle(fighter1, fighter2);

        return battle.battleReady();
    }

    return false;
}

bool CombatController::checkDuplicateSendRequest(const Name &instigator, const Name &target) {
    if (isBattleAssociation(instigator, target)) {
        auto &battle = getBattle(instigator, target);

        //todo maybe only need pending part
        if (battle.getInstigator().getName() == instigator && battle.isPendingState()) {
            return true;
        }
    }

    return false;
}

//todo error, not finding specific game
bool CombatController::replyPendingRequest(const Name &instigator, const Name &target) {
    if (isBattleAssociation(instigator, target)) {
        auto &battle = getBattle(instigator, target);
      //  auto owner = battle.getOwner();
      //  auto nonOwner = battle.getNonOwner(instigator, target);

        if (battle.getInstigator().getName() != instigator) {
            return battle.nameIsPendingWithInstigator(instigator, target);
        }
    }

    return false;
}

void CombatController::setCombatState(const Name &instigator, const Name &target) {
    if (isBattleAssociation(instigator, target)) {
        auto &battle = getBattle(instigator, target);
        battle.setCombatState();
    }
}

bool CombatController::isBattleStarted(const Name &fighter1, const Name &fighter2) {
    if (isBattleAssociation(fighter1, fighter2)) {
        auto &battle = getBattle(fighter1, fighter2);
        if (battle.isCombatState()) {
            return true;
        }
    }
    return false;
}

bool CombatController::isBattleState(const Name &fighter) {
    for (auto &battle: battleList) {
        if (battle.isCombatState()) {
            if (battle.isInBattle(fighter)) {
                return true;
            }
        }
    }

    return false;
}

//
////todo fix
//bool CombatController::isTargetBattleState(const Name &target) {
//    for (auto &battle: battleList) {
//        if (!isBattleAssociation(instigator, target)) {
//            if (battle.isCombatState()) {
//                if (battle.getInstigator().getName() ==  instigator || battle.nameIsPendingWithInstigator(instigator,  target)) {
//                    return true;
//                }
//            }
//
//        }
//
//    }
//
//    return false;
//}

//todo this should be done thru character class later when states are implemented
//bool CombatController::isCorrectAttackTarget(const Name &instigator) {
//    for (auto &battle: battleList) {
//        if (battle.isCombatState()) {
//            for (auto &fighter: battle.getFighters()) {
//                if (fighter.getName() == instigator) {
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
//}

//const std::string
//CombatController::executeQuickBattle(Character &fighter1, Character &fighter2, const Input &input) {
//    auto &battle = getBattle(fighter1.getName(), fighter2.getName());
//    battle.updateFighters(fighter1, fighter2);
//    std::string results = battle.runBattleRound();
//
//    return results;
//}

const std::string
CombatController::executeBattleRound(Character &fighter1, Character &fighter2, const Input &input) {
//return getBattle(combat, Combat(), userName).processInput(input); // Todo use when implemented for rounds
    auto &battle = getBattle(fighter1.getName(), fighter2.getName());
    battle.updateFighters(fighter1, fighter2);
    return battle.runBattleRound();

}


bool CombatController::checkInputForNextRound(const Name &instigator, const Input &input) {
    if (input.empty()) {
        return true;
    }
    return false;
}

void CombatController::setFighterReady(const Name &fighter) {
    auto &battle = getBattleInCombatState(fighter);
    battle.setPlayerReadyForNextRound(fighter);
}

bool CombatController::isNextRoundReady(const Name &fighter) {
//    for (auto &battle: battleList) {
//        if(battle.isCombatState()){
//            if (battle.getOwner() == instigator || battle.nameIsPendingWithOwner(battle.getOwner(), instigator)) {
//                if(battle.isNextRoundReady()){
//                    return true;
//                }
//            }
//        }
//    }
    auto &battle = getBattleInCombatState(fighter);
    return battle.isNextRoundReady();
}

//const std::string CombatController::executeBattleRound(std::vector<Character> &fighters) {
//    auto &battle = getBattleInCombatState(fighters[0].getName());
//    battle.updateFighters(fighters);
//    return battle.runBattleRound();
//}

//std::vector<Name> CombatController::getOpponents(const Name &fighter) {
//    auto &battle = getBattleInCombatState(fighter);
//    return battle.getOpponents();
//}
//
//bool CombatController::isGameOver(const Name &fighter1, const Name &fighter2) {
//    if (isBattleAssociation(fighter1, fighter2)) {
//        auto &battle = getBattle(fighter1, fighter2);
//        if (battle.isGameOverState()) {
//            return true;
//        }
//    }
//
//    return false;
//}

void CombatController::resetRoundReady(const Name &fighterName) {
    auto &battle = getBattleInCombatState(fighterName);
    battle.resetRoundReady();
}


//std::vector<Character> CombatController::getFighters(Name &fighter1, Name &fighter2) {
//    if (isBattleAssociation(fighter1, fighter2)) {
//        auto &battle = getBattle(fighter1, fighter2);
//        return battle.getFighters();
//    }
//}

//todo change name to make sense with the other one
//std::vector<Character> &CombatController::getFighters(Name &fighter) {
//    auto &battle = getBattleInCombatState(fighter);
//    return battle.getFighters();
//}

Character &CombatController::getFighter(Name &fighter) {
    auto &battle = getBattleInCombatState(fighter);

    if(fighter == battle.getInstigatorName()){
        return battle.getInstigator();
    }

    return battle.getOpponent();

}
bool CombatController::isGameOver(const Name &fighter) {
    auto &battle = getBattleInCombatState(fighter);

    if (battle.isGameOverState()) {
        return true;
    }

    return false;

}

//todo rename to getOPoonent()
const Name CombatController::getTargetName(const Name &fighter){
    auto &battle = getBattleInCombatState(fighter);
    if(battle.getInstigatorName() == fighter){
        return battle.getOpponentName();
    }

    return battle.getInstigatorName();
}

//void CombatController::deleteGame(const Name fighter) {
//    auto &battle = getBattleInCombatState(fighter);
//    auto &owner = battle.getOwner();
//    auto &nonOwner = battle.getNonOwner();
//    battleList.erase(std::remove_if(battleList.begin(), battleList.end(),
//                                    [&owner, &nonOwner](Combat battle) {
//
//                                        if (battle.getOwner() == owner) {
//                                            if (battle.nameIsPendingWithOwner(owner, nonOwner)) {
//                                                return true;
//                                            }
//                                        }
//                                    }),
//
//                     battleList.end());
//}

void CombatController::deleteGame(const Name fighter1, const Name fighter2) {

    battleList.erase(std::remove_if(battleList.begin(), battleList.end(),
                                    [&fighter1, &fighter2](Combat battle) {


                                            if (battle.nameIsPendingWithInstigator(fighter2, fighter1)) {
                                                return true;
                                            }



                                    }),

                     battleList.end());
}

//todo need to add state for pending or in battle
std::string CombatController::printAllBattles() {
    std::stringstream output;
    output << "Battles:\n";

    if (!battleList.empty()) {
        for (auto &battle: battleList) {
            if (battle.isPendingState()) {
                output << "\t Instigator: " << battle.getInstigatorName() << "\n";
                output << "\t Pending requests to: " << battle.getOpponentName() << "\n\n";
                continue;
            }

            if (battle.isCombatState()) {
                output << "\t " << battle.getInstigatorName() << " is fighting " << battle.getOpponentName() << "\n\n";
                continue;

            }

            output << "battle print error for " << battle.getInstigatorName() << "\n\n";

        }
    } else {
        output << "\tNo battles\n";
    }

    return output.str();
}

//Private:
Combat &CombatController::getBattle(const Name fighter1, const Name fighter2) {
    for (auto &battle : battleList) {
        if (battle.nameIsPendingWithInstigator(fighter1, fighter2)) {
            return battle;
        }

    }
}

Combat &CombatController::getBattleInCombatState(const Name &fighter) {
    for (auto &battle: battleList) {
        if (battle.isCombatState()) {
            if (battle.isInBattle(fighter)) {
                return battle;
            }
        }
    }
}

bool CombatController::isBattleOwner(const Name fighter1, const Name fighter2) {
    for (auto &battle : battleList) {
        if (battle.getInstigatorName() == fighter1 || battle.getInstigatorName() == fighter2) {
            return true;
        }
    }

    return false;
}

bool CombatController::isBattleAssociation(const Name fighter1, const Name fighter2) {
    for (auto &battle : battleList) {
        if (battle.nameIsPendingWithInstigator(fighter2, fighter1)) {
            return true;
        }
    }

    return false;
}


std::string CombatController::sendQInvitationMsg(const Name &inviterName) {
    std::string output = "\n\t" + inviterName + " wants to quick attack you \n" +
                         "\tEnter '/qattack " + inviterName + "' to battle\n";
    return output;
}

std::string CombatController::sendRoundInvitationMsg(const Name &inviterName) {
    std::string output = "\n\t" + inviterName + " wants to attack you \n" +
                         "\tEnter '/attack " + inviterName + "' to battle\n";
    //"\tEnter '/flee " + inviterName + "' to surrender.\n";
    return output;
}

std::string CombatController::sendDuplicateRequestMsg(const Name &joiner) {
    return "Combat Request with " + joiner + " is still pending";
}

std::string CombatController::sendThreatMsg() {
    return " sent threat ";
}

std::string CombatController::sendOwnerFightingMsg(const Name &target) {
    return " you are now fighting " + target + "\n";
}

std::string CombatController::sendTargetFightingMsg(const Name &target) {
    return target + " accepts the fight\n";
}

std::string CombatController::selfAttackMsg() {
    return "\tYou committed suicide";
}

std::string CombatController::sendTargetInCombatState(const Name &target) {
    return target + " is in combat, send attack request later.";
}

std::string CombatController::sendSelfInCombatState() {
    return "You cannot attack another player while in  combat.\n"
           "Enter '/flee' to escape (not implemented)";
}