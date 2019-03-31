#include <string>
#include <sstream>
#include <iomanip>

#include "Board.h"
#include "Constants.h"

std::string Board::displayBoard() {
    return rowToString(0) + rowToString(1) + rowToString(2);
}

void Board::makeMove(Pieces piece, int row, int col) {
    map[row][col].setPlayer(piece);
}

bool Board::checkWin() {
    return checkHorizontal() || checkVertical() || checkDiagonal();
}

bool Board::validBounds(int row, int col) {
    if (row < MIN_ROW_COL || row > MAX_ROW_COL) {
        return false;
    }

    if (col < MIN_ROW_COL || col > MAX_ROW_COL) {
        return false;
    }

    return true;
}

bool Board::spotTaken(int row, int col) {
    char spot = map[row][col].getPlayer();

    if (spot == x || spot == o) {
        return true;
    }

    return false;
}

std::string Board::rowToString(int row) {
    std::stringstream rowCells("");
    rowCells << std::setw(BOARD_INDENT);

    for (int i = MIN_ROW_COL; i <= MAX_ROW_COL; i++) {
        if (i == 0) {
            rowCells << CELL_SEPRATOR;
        }
        rowCells << (char) map[row][i].getPlayer();
        rowCells << CELL_SEPRATOR;
    }

    rowCells << "\n";
    return rowCells.str();

}

void Board::initializeBoard() {
    for (int row = MIN_ROW_COL; row <= MAX_ROW_COL; row++) {
        for (int col = MIN_ROW_COL; col <= MAX_ROW_COL; col++) {
            Cell cell(CELL_EMPTY);
            map[row][col] = cell;
        }
    }
}

bool Board::checkHorizontal() {
    std::string currRow = "";

    for (int row = MIN_ROW_COL; row <= MAX_ROW_COL; row++) {
        for (int col = MIN_ROW_COL; col <= MAX_ROW_COL; col++) {
            currRow += map[row][col].getPlayer();
        }

        if (checkWinner(currRow)) {
            return true;
        }
        currRow = "";

    }

    return false;
}


bool Board::checkVertical() {
    std::string currRow = "";

    for (int col = MIN_ROW_COL; col <= MAX_ROW_COL; col++) {
        for (int row = MIN_ROW_COL; row <= MAX_ROW_COL; row++) {
            currRow += map[row][col].getPlayer();
        }

        if (checkWinner(currRow)) {
            return true;
        }
        currRow = "";

    }

    return false;
}

bool Board::checkDiagonal() {
    std::string currDag = "";

    currDag += map[MIN_ROW_COL][MIN_ROW_COL].getPlayer();
    currDag += map[MID_ROW_COL][MID_ROW_COL].getPlayer();
    currDag += map[MAX_ROW_COL][MAX_ROW_COL].getPlayer();

    if (checkWinner(currDag)) {
        return true;
    }

    currDag = "";

    currDag += map[MIN_ROW_COL][MAX_ROW_COL].getPlayer();
    currDag += map[MID_ROW_COL][MID_ROW_COL].getPlayer();
    currDag += map[MAX_ROW_COL][MIN_ROW_COL].getPlayer();

    if (checkWinner(currDag)) {
        return true;
    }

    return false;
}

bool Board::checkWinner(const Input &input) {
    if ("xxx" == input || "ooo" == input) {
        return true;
    }

    return false;
}
