#include <iostream>
#include "Game.h"

void g(int& z){
    z =666;
}

void f(int z){
    g(z);
}

int main() {
    for(int i = 0; i < 64; i++){
        std::cout << i << " => " << Game::botifyMove(i) << " => " << Game::debotifyMove(Game::botifyMove(i)) << std::endl;
    }
    return 0;
}
