#ifndef ALTERSPACE_CONSTANTS_H
#define ALTERSPACE_CONSTANTS_H

#include "string"
#include "AlterSpace.h"
#include <map>

using AlterSpace::Name;
using AlterSpace::Input;

enum Pieces {
    x = 'x',
    o = 'o',
    CELL_EMPTY = '-'
};

enum class GameState {
    PLAYING_GAMESTATE,
    X_WON_GAMESTATE,
    O_WON_GAMESTATE,
    TIE_GAMESTATE
};

const static std::map<GameState, std::string> tttStateMap = {
        {GameState::PLAYING_GAMESTATE, "PLAYING:"},
        {GameState::X_WON_GAMESTATE,   "X_WON"},
        {GameState::O_WON_GAMESTATE,   "O_WON"},
        {GameState::TIE_GAMESTATE,     "TIE"},
};

const std::string GAME_WINDOW = "-GAME";
const std::string COORDINATE_SEPARATOR = ",";
const std::string INPUT_SEPARATOR = " ";

const std::string RESET_CODE = "reset";
const std::string QUIT_CODE = "quitGame ";
const std::string INITIAL_INSTRUCTION_CODE = "gameInstruction";

const char CELL_SEPRATOR = '|';

const int NUM_COORDINATES = 2;
const int MOVES_TILL_TIE = 9;
const int RESET_TOKEN = 0;
const int ROW = 0;
const int COL = 1;

#endif //ALTERSPACE_CONSTANTS_H
