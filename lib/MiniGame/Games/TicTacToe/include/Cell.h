#ifndef ALTERSPACE_CELL_H
#define ALTERSPACE_CELL_H

#include "Constants.h"

/**
 * Holds information about individual cell in game board.
 */
class Cell {
private:
    Pieces player;

public:
    Cell(Pieces player) {
        this->player = player;
    }

    Cell() = default;

    Pieces getPlayer() {
        return player;
    }

    void setPlayer(Pieces player) {
        this->player = player;
    }

};

#endif
