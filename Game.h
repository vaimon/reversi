//
// Created by niko1 on 19.10.2021.
//

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

#include <array>
#include <vector>
#include <set>
#include <map>

typedef std::array<std::array<unsigned short,8>,8> Field;

class Game {
    Field currentState = getInitialState();
    // 0 - empty 1 = black, 2 = white
    unsigned short ourColor = 2;
public:
    static Field getInitialState();

    static bool evalDirection(int dir, int* i, int* j);

    std::map<int, std::vector<std::pair<int,int>>> getAvailableMoves();

    static bool isFinish(Field f);

    static void printField(Field f);

    void makeMove(int move, std::vector<std::pair<int,int>>);
};


#endif //REVERSI_GAME_H
