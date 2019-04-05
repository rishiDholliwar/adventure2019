#include "MiniGameController.h"

const std::string MiniGameController::getResults(const Name &userName, Input &input, Interface interface, Games game) {

    switch (game) {
        case TTT: {
            if (interface == Browser) {
                return getGame(ttt, TicTacToe(), userName).processInputBrowser(input);
            } else {
                return getGame(ttt, TicTacToe(), userName).processInputTerminal(input);
            }

        }
        default: {
            std::cout << "MiniGameController error" << std::endl;
            return "MiniGameController error";
        }
    }

}

template<typename GamesList, typename GameInstance>
GameInstance &MiniGameController::getGame(std::vector<GamesList> &gameList, GameInstance, const Name &userName) {
    for (auto &game : gameList) {
        if (game.getUserName() == userName) {
            return game;
        }
    }

    gameList.push_back(GameInstance(userName));
    return gameList.back();
}

