#include <iostream>
#include "Game.h"

int main() {
    Game g;
    g.getAvailableMoves();
    for(int i = 0; i < 64; i++){
        std::cout << i << " => " << Game::botifyMove(i) << " => " << Game::debotifyMove(Game::botifyMove(i)) << std::endl;
    }
    return 0;
}
