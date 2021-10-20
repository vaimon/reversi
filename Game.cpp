//
// Created by niko1 on 19.10.2021.
//

#include <iostream>
#include "Game.h"

Field Game::getInitialState() {
    Field res{};
    res[3][3] = 1;
    res[3][4] = 2;
    res[4][3] = 2;
    res[4][4] = 1;
    return res;
}

bool Game::isFinish(Field f) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (f[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}

void Game::printField(Field f) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (f[i][j] == 0){
                std::cout << "  -";
            } else if (f[i][j] == 1){
                std::cout << "  x";
            } else{
                std::cout << "  o";
            }
        }
        std::cout << std::endl;
    }
}
