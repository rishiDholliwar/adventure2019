#include "CombatController.h"
#include "Combat.h"

bool CombatController::isNewBattle(const Name &instigator, const Name &target) {
    for (auto &battle : battleList) {
        if (battle.getOwner() == instigator) {
            if (battle.nameIsPendingWithOwner(target, instigator)) {
                return false;
            }
        }

        if (battle.getOwner() == target) {
            if (battle.nameIsPendingWithOwner(instigator, target)) {
                return false;
            }
        }

    }

    return true;
}

void CombatController::createNewBattle(Character &instigator, Character &target) {
    battleList.push_back(Combat(instigator));
    battleList.back().addFighter(target);
}

std::string CombatController::sendBattleRequest(const Character &fighter1, const Character &fighter2) {
    if (isBattleOwner(fighter1.getName(), fighter2.getName())) {
        auto battle = getBattle(fighter1.getName(), fighter2.getName());
        auto owner = battle.getOwner();

        if (owner == fighter1.getName()) {
            return sendInvitationMsg(fighter1.getName());
        } else {
            return sendInvitationMsg(fighter2.getName());
        }
    }

    return "error sending invite";
}

bool CombatController::battleReady(const Name &fighter1, const Name &fighter2) {
    if (isBattleAssociation(fighter1, fighter2)) {
        auto battle = getBattle(fighter1, fighter2);
        return battle.battleReady();
    }

    return false;
}

bool CombatController::checkDuplicateSendRequest(const Name &instigator, const Name &target) {
    if (isBattleAssociation(instigator, target)) {
        auto battle = getBattle(instigator, target);
        auto owner = battle.getOwner();

        if (owner == instigator) {
            return true;
        }
    }

    return false;
}

bool CombatController::replyPendingRequest(const Name &instigator, const Name &target) {
    if (isBattleAssociation(instigator, target)) {
        auto battle = getBattle(instigator, target);
        auto owner = battle.getOwner();
        auto nonOwner = battle.getNonOwner(instigator, target);

        if (owner != instigator) {
            return battle.nameIsPendingWithOwner(nonOwner, owner);
        }
    }

    return false;
}

const std::string
CombatController::executeBattle(Character &fighter1, Character &fighter2, const Input &input) {
    //return getBattle(combat, Combat(), userName).processInput(input); // Todo use when implemented for rounds
    auto &battle = getBattle(fighter1.getName(), fighter2.getName());
    battle.updateFighters(fighter1, fighter2);
    std::string results = battle.runCombat();

    return results;
}

bool CombatController::isGameOver(const Name &fighter1, const Name &fighter2) {
    if (isBattleAssociation(fighter1, fighter2)) {
        auto battle = getBattle(fighter1, fighter2);
        if (battle.isGameOverState()) {
            return true;
        }
    }

    return false;
}

std::vector<Character> &CombatController::getFighters(Name &fighter1, Name &fighter2) {
    if (isBattleAssociation(fighter1, fighter2)) {
        auto &battle = getBattle(fighter1, fighter2);
        return battle.getFighters();
    }
}

void CombatController::deleteGame(const Name fighter1, const Name fighter2) {

    battleList.erase(std::remove_if(battleList.begin(), battleList.end(),
                                    [&fighter1, &fighter2](Combat battle) {

                                        if (battle.getOwner() == fighter1) {
                                            if (battle.nameIsPendingWithOwner(fighter2, fighter1)) {
                                                return true;
                                            }
                                        }

                                        if (battle.getOwner() == fighter2) {
                                            if (battle.nameIsPendingWithOwner(fighter1, fighter2)) {
                                                return true;
                                            }
                                        }
                                    }),

                     battleList.end());
}

//Private:
Combat &CombatController::getBattle(const Name fighter1, const Name fighter2) {
    for (auto &battle : battleList) {
        if (battle.getOwner() == fighter1 && battle.nameIsPendingWithOwner(fighter2, fighter1)) {
            return battle;
        }

        if (battle.getOwner() == fighter2 && battle.nameIsPendingWithOwner(fighter1, fighter2)) {
            return battle;
        }
    }
}

bool CombatController::isBattleOwner(const Name fighter1, const Name fighter2) {
    for (auto &battle : battleList) {
        if (battle.getOwner() == fighter1 || battle.getOwner() == fighter2) {
            return true;
        }
    }

    return false;
}

bool CombatController::isBattleAssociation(const Name fighter1, const Name fighter2) {
    for (auto &battle : battleList) {
        if (battle.nameIsPendingWithOwner(fighter2, fighter1) || battle.nameIsPendingWithOwner(fighter1, fighter2)) {
            return true;
        }
    }

    return false;
}


//for debug
std::string CombatController::printAllBattles() {
    std::string output;
    output += "Battles:\n";

    if (!battleList.empty()) {
        for (auto &game: battleList) {
            output += "\t Owner: " + game.getOwner() + "\n";
            output += "\t Pending requests to: " + game.getPendingNames() + "\n\n";
        }
    } else {
        output += "\tNo battles\n";
    }

    return output;
}

std::string CombatController::sendInvitationMsg(const Name &inviterName) {
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

std::string CombatController::selfAttack() {
    return "\tYou committed suicide";
}