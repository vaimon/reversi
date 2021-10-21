//
// Created by niko1 on 19.10.2021.
//

#include <iostream>
#include "Game.h"

Game::Game(unsigned short ourColor) : ourColor(ourColor) {
    if(ourColor == 1){
        opponentColor = 2;
    }else{
        opponentColor = 1;
    }
}

Field Game::getInitialState() {
    Field res{};
    res[3][3] = 2;
    res[3][4] = 1;
    res[4][3] = 1;
    res[4][4] = 2;
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

std::map<int, std::vector<std::pair<int,int>>> Game::getAvailableMoves(Field f) const {
    std::map<int, std::vector<std::pair<int,int>>> res{};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(f[i][j] == ourColor){
                for(int dir = 1; dir <=8; dir++){
                    int k = i, l = j, c = 0;
                    while(evalDirection(dir,&k,&l) && f[k][l] != ourColor && f[k][l] != 0){
                        c++;
                    }
                    if(f[k][l] == 0 && c > 0){
                        res[k*8+l].push_back({i*8+j, dir});
                    }
                }
            }
        }
    }
    return res;
}

std::map<int, std::vector<std::pair<int,int>>> Game::getOpponentMoves(Field f) const {
    std::map<int, std::vector<std::pair<int,int>>> res{};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(f[i][j] == opponentColor){
                for(int dir = 1; dir <=8; dir++){
                    int k = i, l = j, c = 0;
                    while(evalDirection(dir,&k,&l) && f[k][l] != opponentColor && f[k][l] != 0){
                        c++;
                    }
                    if(f[k][l] == 0 && c > 0){
                        res[k*8+l].push_back({i*8+j, dir});
                    }
                }
            }
        }
    }
    return res;
}

void Game::makeMove(Field& f, int move, const std::vector<std::pair<int,int>>& affectedCheckers, bool isOurMove) const{
    //currentState[move/8][move%8] = ourColor;
    for (std::pair<int,int> pos : affectedCheckers) {
        int i = pos.first/8, j = pos.first % 8;
        while(i!=move/8 && j!=move%8){
            evalDirection(pos.second,&i,&j);
            f[i][j] = isOurMove ? ourColor: opponentColor;
        }
    }
}

void Game::makeOpponentMove(Field& f, const std::string &botMove) const {
    int move = debotifyMove(botMove);
    for (int dir = 1; dir <= 8; dir++) {
        int k = move / 8, l = move % 8, c = 0;
        while (evalDirection(dir, &k, &l) && f[k][l] == ourColor) {
            c++;
        }
        if (f[k][l] == opponentColor && c > 0) {
            int i = move / 8, j = move % 8;
            while(i!=k && j!=l){
                evalDirection(dir,&i,&j);
                f[i][j] = opponentColor;
            }
        }
    }
}

int Game::debotifyMove(std::string move) {
    int res = 0;
    switch(move[0]){
        case 'a': res = 0; break;
        case 'b': res = 1; break;
        case 'c': res = 2; break;
        case 'd': res = 3; break;
        case 'e': res = 4; break;
        case 'f': res = 5; break;
        case 'g': res = 6; break;
        case 'h': res = 7; break;
    }
    res += (std::stoi(move.substr(1,1)) -1) * 8;
    return res;
}

std::string Game::botifyMove(int move) {
    std::stringstream ss;
    switch(move % 8){
        case 0: ss << "a"; break;
        case 1: ss << "b"; break;
        case 2: ss << "c"; break;
        case 3: ss << "d"; break;
        case 4: ss << "e"; break;
        case 5: ss << "f"; break;
        case 6: ss << "g"; break;
        case 7: ss << "h"; break;
    }
    ss << (move/8 + 1);
    return ss.str();
}

int Game::h(Field f) {

}

int Game::alphaBeta(Field f, int depth, int alpha, int beta, bool isMax) {
    if (depth == 0 || isFinish(f)) {
        return h(f);
    }
    if (isMax) {
        int value = INT32_MIN;
        for (const std::pair<const int, std::vector<std::pair<int, int>>>& child: getAvailableMoves(f)) {
            makeMove(f,child.first,child.second, true);
            value = std::max(value, alphaBeta(f,depth - 1, alpha, beta, false));
            if(value >= beta){
                break;
            }
            alpha = std::max(alpha,value);
        }
        return value;
    } else{
        int value = INT32_MAX;
        for (const std::pair<const int, std::vector<std::pair<int, int>>>& child: getOpponentMoves(f)) {
            makeMove(f,child.first,child.second,false);
            value = std::min(value, alphaBeta(f,depth - 1, alpha, beta, true));
            if(value <= alpha){
                break;
            }
            beta = std::min(beta,value);
        }
        return value;
    }
}

std::string Game::decideHowToMove() {
    alphaBeta(currentState,5,INT32_MIN,INT32_MAX,true);
}




