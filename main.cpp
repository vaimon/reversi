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
        if (move == "skip"){
            std::cout << "Skip move " << std::endl;
        } else if (move == "finish"){
            std::cout << "Finish! " << std::endl;
            return 0;
        }else {
            g.makeBotMove(move,true);
            std::cout << "Our move: " << move << std::endl;
            g.printField();
        }

        std::string oppMove;
        std::cin >> oppMove;
        g.makeBotMove(oppMove,false);
        std::cout << "Opponent move: " << oppMove << std::endl;
        g.printField();
        std::cout<<std::endl<<std::endl;
    }
    return 0;
}
