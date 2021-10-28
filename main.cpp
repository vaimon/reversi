#include <iostream>
#include "Game.h"

void g(int& z){
    z =666;
}

void f(int z){
    g(z);
}

int main(int argc, char *argv[]) {
    bool isBotFightMode = false;
    int order = 1;
    if(argc > 1){
        isBotFightMode = true;
        order = (int)(*argv[1] - '0') + 1;
    }
    std::cout<< isBotFightMode << " " << order << std::endl;
    Game g(order);

    g.printField();
    if(order == 2){
        std::string oppMove;
        std::cin >> oppMove;
        g.makeBotMove(oppMove,false);
        std::cout << "Opponent move: " << oppMove << std::endl;
        g.printField();
        std::cout<<std::endl<<std::endl;
    }
    while (true){
        auto move = g.decideHowToMove();
        if (move == "skip"){
            std::cout << "Skip move " << std::endl;
        } else if (move == "draw"){
            std::cout << "Draw! " << std::endl;
            return 4;
        }else if (move == "win"){
            std::cout << "Win! " << std::endl;
            return 0;
        }else if (move == "lose"){
            std::cout << "Lose! " << std::endl;
            return 3;
        }else {
            g.makeBotMove(move,true);
            std::cout << order << " Our move: " << move << std::endl;
            if(isBotFightMode){
                std::cerr << move << std::endl;
            }
            g.printField();
            std::string state = g.checkForWin();
            std::cout << "state: " << state << std::endl;
            if(state != ""){
                if (state == "draw"){
                    std::cout << "Draw! " << std::endl;
                    return 4;
                }else if (state == "win"){
                    std::cout << "Win! " << std::endl;
                    return 0;
                }else if (state == "lose") {
                    std::cout << "Lose! " << std::endl;
                    return 3;
                }
            }

        }

        std::string oppMove;
        std::cout << "I am " << order << " waiting for my dumb opponent..." << std::endl;
        std::cin >> oppMove;
        if (move == "skip"){
            std::cout << "Skip move " << std::endl;
        } else if (move == "draw"){
            std::cout << "Draw! " << std::endl;
            return 4;
        }else if (move == "win"){
            std::cout << "Win! " << std::endl;
            return 0;
        }else if (move == "lose"){
            std::cout << "Lose! " << std::endl;
            return 3;
        }else {
            g.makeBotMove(oppMove, false);
            std::cout << order << " Opponent move: " << oppMove << std::endl;
            g.printField();
            std::cout << std::endl << std::endl;
        }
    }
    return 1;
}
