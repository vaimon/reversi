#include <iostream>
#include "Game.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"Russian");
    bool isBotFightMode = false;
    int order = 1;
    if (argc > 1) {
        isBotFightMode = true;
        order = (int) (*argv[1] - '0') + 1;
    }
    std::cout << isBotFightMode << " " << order << std::endl;
    Game g(order);
    g.printField();
    if (order == 2) {
        std::string oppMove;
        std::cin >> oppMove;
        g.makeBotMove(oppMove, false);
        std::cout << "Opponent move: " << oppMove << std::endl;
        g.printField();
        std::cout << std::endl << std::endl;
    }
    while (true) {
        if(isBotFightMode){
            g.printSituation();
        }

        auto move = g.decideHowToMove();
        if (move == "skip") {
            std::cout << "Skip move " << std::endl;
        } else if (move == "draw") {
            std::cout << "Well, draw is draw... " << std::endl;
            if(!isBotFightMode){
                system("pause");
            }
            return 4;
        } else if (move == "win") {
            std::cout << "HAHAHAHAHAH SKINSUIT, I WON!! " << std::endl;
            if(!isBotFightMode){
                system("pause");
            }
            return 0;
        } else if (move == "lose") {
            std::cout << "I've missed the battle, but not the war... " << std::endl;
            if(!isBotFightMode){
                system("pause");
            }
            return 3;
        } else {
            g.makeBotMove(move, true);
            if(isBotFightMode){
                std::cout << order;
            }
            std::cout << " Our move: " << move << std::endl;
            if (isBotFightMode) {
                std::cerr << move << std::endl;
            }
            g.printField();
            std::string state = g.checkForWin();
            if(isBotFightMode){
                std::cout << "state: " << state << std::endl;
            }
            if (state != "") {
                if (state == "draw") {
                    std::cout << "Well, draw is draw... " << std::endl;
                    if(!isBotFightMode){
                        system("pause");
                    }
                    return 4;
                } else if (state == "win") {
                    std::cout << "HAHAHAHAHAH SKINSUIT, I WON!! " << std::endl;
                    if(!isBotFightMode){
                        system("pause");
                    }
                    return 0;
                } else if (state == "lose") {
                    std::cout << "I've missed the battle, but not the war... " << std::endl;
                    if(!isBotFightMode){
                        system("pause");
                    }
                    return 3;
                }
            }

        }

        std::string oppMove;

        if(g.isOpponentSkipping()){
            std::cout << "No moves, sweetie? Hahaha, my turn!" << std::endl;
            continue;
        }
        if(isBotFightMode){
            std::cout << "I am " << order << " waiting for my dumb opponent..." << std::endl;
        }
        if(isBotFightMode){
            g.printSituation();
        }
        std::cin >> oppMove;
        if(!g.checkMove(oppMove)){
            std::cout << "You've tried to fool me, aren't you? You can't move that way." << std::endl;
            std::cin >> oppMove;
        }
        if(!g.checkMove(oppMove)){
            std::cout << "Well, I am offended right now. Bye." << std::endl;
            system("pause");
            throw std::exception("CHEATER!...");
        }
        g.makeBotMove(oppMove, false);
        if(isBotFightMode){
            std::cout << order;
        }
        std::cout << " Opponent move: " << oppMove << std::endl;
        g.printField();
        std::cout << std::endl << std::endl;

    }
    return 1;
}
