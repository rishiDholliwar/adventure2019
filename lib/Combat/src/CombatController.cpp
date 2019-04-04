#include "CombatController.h"
#include "Combat.h"

bool CombatController::isNewBattle(const Name &instigator, const Name &target) {
    return (!isBattleAssociation(instigator, target));
}

void CombatController::createNewBattle(Character &instigator, Character &target) {
    battleList.push_back(Combat(instigator, target));
}

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

        if (battle.getInstigator().getName() == instigator && battle.isPendingState()) {
            return true;
        }
    }

    return false;
}

bool CombatController::replyBattleRequest(const Name &instigator, const Name &target) {
    if (isBattleAssociation(instigator, target)) {
        auto &battle = getBattle(instigator, target);

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

const std::string
CombatController::executeBattleRound(Character &fighter1, Character &fighter2, const Input &input) {
    auto &battle = getBattle(fighter1.getName(), fighter2.getName());
    battle.updateFighters(fighter1, fighter2);
    return battle.runBattleRound();
}

Character &CombatController::getFighter(Name &fighter) {
    auto &battle = getBattleInCombatState(fighter);

    if (fighter == battle.getInstigatorName()) {
        return battle.getInstigator();
    }

    return battle.getOpponent();
}

bool CombatController::isBattleOver(const Name &fighter) {
    auto &battle = getBattleInCombatState(fighter);

    if (battle.isGameOverState()) {
        return true;
    }

    return false;
}

const Name CombatController::getTargetName(const Name &fighter) {
    auto &battle = getBattleInCombatState(fighter);

    if (battle.getInstigatorName() == fighter) {
        return battle.getOpponentName();
    }

    return battle.getInstigatorName();
}

void CombatController::deleteBattle(const Name fighter1, const Name fighter2) {

    battleList.erase(std::remove_if(battleList.begin(), battleList.end(),
                                    [&fighter1, &fighter2](Combat battle) {

                                        if (battle.nameIsPendingWithInstigator(fighter2, fighter1)) {
                                            return true;
                                        }
                                    }),

                     battleList.end());
}

void CombatController::setFleeState(Name &fighter) {
    auto &battle = getBattleInCombatState(fighter);
    battle.setFleeState();
}

const std::string
CombatController::flee(Character &surrenderer, Character &winner, const Input &input) {
    auto &battle = getBattle(surrenderer.getName(), winner.getName());
    battle.updateFighters(surrenderer, winner);
    return battle.flee(surrenderer.getName());
}

bool CombatController::isFleeState(Name &fighter) {
    for (auto &battle: battleList) {
        if (battle.isFleeState()) {
            if (battle.isInBattle(fighter)) {
                return true;
            }
        }
    }

    return false;
}

bool CombatController::isTargetLogoutState(Name &fighter) {
    for (auto &battle: battleList) {
        if (battle.isTargetLogoutState()) {
            if (battle.isInBattle(fighter)) {
                return true;
            }
        }
    }

    return false;
}

void CombatController::setTargetLogoutState(Name &fighter) {
    auto &battle = getBattleInCombatState(fighter);
    battle.setTargetLogoutState();
}

std::string CombatController::logout(Name &winner) {
    auto &battle = getBattleInCombatState(winner);
    return battle.logout(winner);
}

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

//Public messages:
std::string CombatController::sendCharacterNotFoundMsg(const Name &target) {
    std::stringstream ss;
    ss << "\tCharacter " << target << " not found\n\n";
    return ss.str();
}

std::string CombatController::sendRoundInvitationMsg(const Name &inviterName) {
    std::stringstream ss;
    ss << "\n\t" << inviterName << " wants to attack you \n" <<
       "\tEnter '/attack " << inviterName << "' to battle\n";
    return ss.str();
}

std::string CombatController::sendDuplicateRequestMsg(const Name &joiner) {
    std::stringstream ss;
    ss << "Combat Request with " << joiner << " is still pending";
    return ss.str();
}

std::string CombatController::sendThreatMsg() {
    return " sent threat ";
}

std::string CombatController::selfAttackMsg() {
    return "\tYou committed suicide";
}

std::string CombatController::sendTargetInCombatState(const Name &target) {
    std::stringstream ss;
    ss << target << " is in combat, send attack request later.";
    return ss.str();
}

std::string CombatController::sendBattleStartedMsg() {
    return "Battle Started!";
}

std::string CombatController::sendTargetOfflineMsg() {
    return "\nOpponent is offline:\n";
}

std::string CombatController::sendNotInBattleMsg() {
    return "You are not in battle.";
}

std::string CombatController::sendYouFledMsg(std::string direction) {
    return "\nYou have fled " + direction + ":\n";
}

std::string CombatController::sendTargetFledMsg() {
    return "\nOpponent has fled:\n";
}