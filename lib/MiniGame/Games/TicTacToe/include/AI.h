#ifndef ALTERSPACE_AI_H
#define ALTERSPACE_AI_H

#include <ctime>
#include "Board.h"
#include "Constants.h"

/**
 * AI just makes random moves on the board.
 */
class AI {
private:
    Pieces player;

public:
    AI(Pieces player) {
        this->player = player;
        srand(static_cast<unsigned int>(time(0)));
    }

    AI() {
        this->player = player;
        srand(static_cast<unsigned int>(time(0)));
    }

    void setPLayer(Pieces player) {
        this->player = player;
    }

    void makeMove(Board &board);
};

#endif
