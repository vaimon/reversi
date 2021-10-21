#include <iostream>
#include "Game.h"

void g(int& z){
    z =666;
}

void f(int z){
    g(z);
}

int main() {
    Game g(1);
    while (true){
        auto move = g.decideHowToMove();
        g.makeBotMove(move,true);
        std::cout << "Our move: " << move << std::endl;
        g.printField();
        std::string oppMove;
        std::cin >> oppMove;
        g.makeBotMove(oppMove,false);
        std::cout << "Opponent move: " << move << std::endl;
        g.printField();
        std::cout<<std::endl<<std::endl;
    }
    return 0;
}
