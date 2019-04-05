#ifndef ALTERSPACE_MINIGAME_H
#define ALTERSPACE_MINIGAME_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "TicTacToe.h"

/**
 * MiniGame is used to play the games in the Games folder.
 * Currently, Tic Tac Toe is the only game mode available.
 */
class MiniGameController {
public:
    enum Games {
        TTT //tic tac toe
    };

    enum Interface {
        Browser,
        Terminal
    };

private:
    std::vector<TicTacToe> ttt;

    /*
     * Returns a game based on username. If the user has no current game
     * then a new one is returned.
     *
     * Pre-Condition: GameList is list of games and GameInstance is an instance of the game.
     *
     * Post-Condition:
     *
     */
    template<typename GamesList, typename GameInstance>
    GameInstance &getGame(std::vector<GamesList> &gameList, GameInstance, const Name &userName);


public:
    MiniGameController() = default;

    /*
     * When a user performs an action for a mini game, then this
     * function will return the results in a form of a string.
     *
     * Pre-Condition: userName is the owner of the game.
     *                input is the action taken in the game.
     *                interface is where the output will be
     *                displayed.
     *                game is the type of game.
     *
     * Post-Condition:
     *
     */
    const std::string getResults(const Name &userName, Input &input, Interface interface, Games game);

};

#endif
