#ifndef ALTERSPACE_COMMANDSLISTING_H
#define ALTERSPACE_COMMANDSLISTING_H

#include <string>

/**
 * This namespace is used to display all the
 * commands available and a short description
 * for each command.
 */
namespace CommandsListing {
    static std::string getCommands() {
        return "Commands:\n"

               "\n Combat:\n"
               "\t /combat: Displays combat information for all players in room.\n"
               "\t /combat [name]: Displays combat information for [name].\n"
               "\t /attack [name]: Send battle request to [name] or accept if sent a request.\n"
               "\t /battles: See list of pending battles.\n"
               "\t /flee: Not implemented yet.\n"

               "\n MiniGames: (not added yet)\n"
               "     TicTacToe:\n"
               "\t /ttt: Opens the tic tac toe game in browser.\n"
               "\t /tttt: Opens the tic tac toe game in terminal.\n"
               "\t  /tttt [0-2,0-2]: Make move on the game board.\n"
               "\t  /tttt reset: Resets the game board.\n"
               "\t  /tttt quitGame: Quits the game.\n";
    }
}

#endif //ALTERSPACE_COMMANDSLISTING_H
