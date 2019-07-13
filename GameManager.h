#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#ifdef DEBUG
    #include <iostream>
    #include <conio.h>
    #include <Windows.h>
#endif

#include <cmath>

#include "Ball.h"
#include "Player.h"

#define MAX_PLAYERS 6

#define L_TEAM_X (width / 4)
#define R_TEAM_X (3 * width / 4)

#define L_TEAM_Y(c) (height * (c + 2) / (num_players + 2))
#define R_TEAM_Y(c) (height * (c + 1) / (num_players + 2))

class GameManager {
    private:
        bool quit;
        Ball* ball;
        int num_players;
        int width, height;
        Player* players[MAX_PLAYERS];
        int dribbling_left_wall, dribbling_right_wall;
        int dribbling_top_wall, dribbling_bottom_wall;
        int top_wall, left_wall, bottom_wall, right_wall;

    public:
        GameManager(int, int, int);
        ~GameManager();
        void reset();
        void draw();
        void input();
        void logic();
        void run();
};

#endif
