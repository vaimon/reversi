//
// Created by niko1 on 19.10.2021.
//

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

#include <array>
#include <vector>
#include <set>
#include <map>
#include <sstream>

typedef std::array<std::array<unsigned short, 8>, 8> Field;

class Game {
    Field currentState = getInitialState();
    // 0 - empty 1 = black, 2 = white
    unsigned short ourColor = 2;
    unsigned short opponentColor = 1;
public:
    Game(unsigned short ourColor);

    static Field getInitialState();

    static bool evalDirection(int dir, int *i, int *j);

    std::map<int, std::vector<std::pair<int, int>>> getAvailableMoves();

    static bool isFinish(Field f);

    static void printField(Field f);

    void makeMove(int move, const std::vector<std::pair<int, int>> &);

    void makeOpponentMove(const std::string &botMove);

    static std::string botifyMove(int move);

    static int debotifyMove(std::string move);

    std::map<int, std::vector<std::pair<int, int>>> getOpponentMoves();
};


#endif //REVERSI_GAME_H
