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

bool Game::evalDirection(int dir, int *i, int *j) {
    switch (dir) {
        case 1: return --*j >= 0;
        case 2: return --*j >= 0 && --*i >= 0;
        case 3: return --*i >= 0;
        case 4: return --*i >= 0 && ++*j < 8;
        case 5: return ++*j < 8;
        case 6: return ++*i < 8 && ++*j < 8;
        case 7: return ++*i < 8;
        case 8: return ++*i < 8 && --*j >= 0;
        default: return false;
    }
}

std::map<int, std::vector<std::pair<int,int>>> Game::getAvailableMoves() {
    std::map<int, std::vector<std::pair<int,int>>> res{};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(currentState[i][j] == ourColor){
                for(int dir = 1; dir <=8; dir++){
                    int k = i, l = j, c = 0;
                    while(evalDirection(dir,&k,&l) && currentState[k][l] != ourColor && currentState[k][l] != 0){
                        c++;
                    }
                    if(currentState[k][l] == 0 && c > 0){
                        res[k*8+l].push_back({i*8+j, dir});
                    }
                }
            }
        }
    }
    return res;
}

void Game::makeMove(int move, std::vector<std::pair<int,int>> affectedCheckers){
    //currentState[move/8][move%8] = ourColor;
    for (std::pair<int,int> pos : affectedCheckers) {
        int i = pos.first/8, j = pos.first % 8;
        while(i!=move/8 && j!=move%8){
            evalDirection(pos.second,&i,&j);
            currentState[i][j] = ourColor;
        }
    }
}
