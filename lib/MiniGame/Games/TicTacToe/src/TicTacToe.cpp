#include "TicTacToe.h"
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>


std::string TicTacToe::getBoard() {
    return board.displayBoard();
}

std::string TicTacToe::processInputBrowser(Input &input) {
    std::vector<Input> messageTokens;
    boost::split(messageTokens, input, boost::is_any_of(INPUT_SEPARATOR));

    if (quit(input)) {
        return QUIT_CODE;
    }

    if (!initialSetupDone()) {
        return getInitialSetup();
    }

    if (reset(messageTokens)) {
        reset();
    }

    if (!reset(messageTokens) && !isGameOver) {
        processCoordinates(input, messageTokens);
    }

    return GAME_WINDOW + " \t" + getGameState() + "\n" + getBoard();
}

std::string TicTacToe::processInputTerminal(const Input &input) {
    std::vector<Input> messageTokens;
    boost::split(messageTokens, input, boost::is_any_of(INPUT_SEPARATOR));

    if (quit(input)) {
        return QUIT_CODE;
    }

    if (!initialSetupDone()) {
        return getInitialSetup();
    }

    if (reset(messageTokens)) {
        reset();
    }

    if (!reset(messageTokens) && !isGameOver) {
        processCoordinates(input, messageTokens);
    }

    return getGameState() + "\n" + getBoard();
}


void TicTacToe::processCoordinates(const Input &input, std::vector<Input> messageTokens) {

    if (!containsCoordinateSeparator(input)) {
        return;
    }

    boost::split(messageTokens, input, boost::is_any_of(COORDINATE_SEPARATOR));

    if (!correctNumCoordinates(messageTokens)) {
        return;
    }

    if (coordinatesEmpty(messageTokens)) {
        return;
    }

    if (coordinatesNumeric(messageTokens)) {
        makeMove(stoi(messageTokens[ROW]), stoi(messageTokens[COL]));
    }
}

void TicTacToe::makeMove(int row, int col) {
    if (validBoardMove(row, col)) {
        makePlayerMove(row, col);
        if (isWin()) {
            setXWin();

        } else {
            if (getMoveNumber() == MOVES_TILL_TIE) {
                setGameTie();

            } else {
                makeAIMove();
                if (isWin()) {
                    setOWin();
                }
            }
        }
    }
}

void TicTacToe::makePlayerMove(int row, int col) {
    board.makeMove(x, row, col);
    incrementMoveNumber();
}

void TicTacToe::makeAIMove() {
    ai.makeMove(board);
    incrementMoveNumber();
}

void TicTacToe::reset() {
    this->currentGameState = GameState::PLAYING_GAMESTATE;
    setGameOver(false);
    this->moveNumber = 0;
    board.initializeBoard();
}

bool TicTacToe::quit(const Input &input) {
    if ((input + INPUT_SEPARATOR) == QUIT_CODE) {
        reset();
        return true;
    }

    return false;
}

bool TicTacToe::reset(const std::vector<Input> &messageTokens) {
    if (messageTokens[RESET_TOKEN] == RESET_CODE) {
        return true;
    } else {
        return false;
    }
}

bool TicTacToe::containsCoordinateSeparator(const Input &input) {
    if (input.find(COORDINATE_SEPARATOR) != std::string::npos) {
        return true;
    } else {
        return false;
    }
}

bool TicTacToe::correctNumCoordinates(const std::vector<Input> &messageTokens) {
    if (messageTokens.size() == NUM_COORDINATES) {
        return true;
    } else {
        return false;
    }
}

bool TicTacToe::coordinatesEmpty(const std::vector<Input> &messageTokens) {
    if (!((messageTokens[ROW]).empty()) && !((messageTokens[COL]).empty())) {
        return false;
    } else {
        return true;
    }
}

bool TicTacToe::coordinatesNumeric(const std::vector<Input> &messageTokens) {
    if (numeric(messageTokens[ROW]) && numeric(messageTokens[COL])) {
        return true;
    } else {
        return false;
    }
}

bool TicTacToe::validBoardMove(int row, int col) {
    if (!board.spotTaken(row, col)) {
        if (board.validBounds(row, col)) {
            return true;
        }
    }
    return false;
}

std::string TicTacToe::getInitialSetup() {
    //TODO nothing yet, will implement in phase 2
    //TODO could implement feature to choose your piece of x or o
    //TODO Later add option to choose to play ai or another player
    return "";
}

