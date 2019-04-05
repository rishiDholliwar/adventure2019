#include "AI.h"

void AI::makeMove(Board &board) {
    int row;
    int col;
    do {
        row = (rand() % (board.getMaxRowCol() + 1));
        col = (rand() % (board.getMaxRowCol() + 1));

    } while (board.spotTaken(row, col));

    board.makeMove(this->piece, row, col);

}