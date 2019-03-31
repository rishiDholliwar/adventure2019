#ifndef TTT_BOARD_H
#define TTT_BOARD_H

#include <string>

#include "Cell.h"

/**
 * Board holds all the information of the game board.
 */
class Board {
private:
    const static int MIN_ROW_COL = 0;
    const static int MID_ROW_COL = 1;
    const static int MAX_ROW_COL = 2;
    const static int BOARD_INDENT = 9;

    Cell map[4][4];

    std::string rowToString(int row);

    bool checkHorizontal();

    bool checkVertical();

    bool checkDiagonal();

    bool checkWinner(const Input &input);

public:
    Board() {
        initializeBoard();
    }

    std::string displayBoard();

    void initializeBoard();

    void makeMove(Pieces piece, int row, int col);

    bool checkWin();

    bool validBounds(int row, int col);

    bool spotTaken(int row, int col);

    int getMaxRowCol() {
        return MAX_ROW_COL;
    }
};


#endif
