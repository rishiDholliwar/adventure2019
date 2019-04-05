#ifndef ALTERSPACE_TICTACTOE_H
#define ALTERSPACE_TICTACTOE_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "AI.h"
#include "Board.h"
#include "Constants.h"

/**
 * used to play tic tac toe game.
 */
class TicTacToe {

private:

    Name userName;

    Board board;
    AI ai;

    GameState currentGameState;
    int moveNumber = 0;
    bool isGameOver = false;
    bool isInitSetup = true;

public:
    TicTacToe() {
        ai.setPLayer(o);
        this->currentGameState = GameState::PLAYING_GAMESTATE;
    }

    TicTacToe(const Name userName) {
        this->userName = userName;
        ai.setPLayer(o);
        this->currentGameState = GameState::PLAYING_GAMESTATE;
    }

    std::string processInputTerminal(const Input &input);

    std::string processInputBrowser(Input &input);

    void reset();

    const Name getUserName() {
        return userName;
    }

private:
    std::string getBoard();

    bool initialSetupDone() {
        return isInitSetup;
    }

    void makeMove(int row, int col);

    void makePlayerMove(int row, int col);

    void makeAIMove();

    void processCoordinates(const Input &input, std::vector<Input> messageTokens);

    bool quit(const Input &input);

    bool reset(const std::vector<Input> &messageTokens);

    bool containsCoordinateSeparator(const Input &input);

    bool correctNumCoordinates(const std::vector<Input> &messageTokens);

    bool coordinatesEmpty(const std::vector<Input> &messageTokens);

    bool coordinatesNumeric(const std::vector<Input> &messageTokens);

    bool validBoardMove(int row, int cols);

    bool isWin() {
        return board.checkWin();
    }

    void setGameOver(bool gameState) {
        isGameOver = gameState;
    }

    void setGameTie() {
        setGameOver(true);
        currentGameState = GameState::TIE_GAMESTATE;
    }

    void setXWin() {
        setGameOver(true);
        currentGameState = GameState::X_WON_GAMESTATE;
    }

    void setOWin() {
        setGameOver(true);
        currentGameState = GameState::O_WON_GAMESTATE;
    }

    int getMoveNumber() {
        return moveNumber;
    }

    void incrementMoveNumber() {
        this->moveNumber = this->moveNumber + 1;
    }

    std::string getGameState() {
        return tttStateMap.at(currentGameState);
    }

    bool numeric(const Input &input) {
        return std::all_of(input.begin(), input.end(), ::isdigit);
    }

    std::string getInitialSetup();

    void setInitSetup(bool isInitSetup) {
        this->isInitSetup = isInitSetup;
    }

};

#endif
