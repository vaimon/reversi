//
// Created by niko1 on 19.10.2021.
//

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

#include <array>

typedef std::array<std::array<unsigned short,8>,8> Field;

class Game {
    Field currentState = getInitialState();
    // 1 = black, 2 = white
    unsigned short ourColor = 1;
public:
    static Field getInitialState();

    static bool isFinish(Field f);

    static void printField(Field f);
};


#endif //REVERSI_GAME_H
