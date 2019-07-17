#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#ifdef DEBUG
    #include <iostream>
    #include <conio.h>
    #include <Windows.h>
#endif

#include <math.h>
#include <Arduino.h>
#include "Ball.h"
#include "Player.h"
#include "packet.h"
#include "direction.h"

#define MAX_PLAYERS 12

#define L_TEAM 0
#define R_TEAM 1

#define L_TEAM_X (width / 4)
#define R_TEAM_X (3 * width / 4)

#define L_TEAM_Y(c) (height * (c + 2) / (num_players + 2))
#define R_TEAM_Y(c) (height * (c + 1) / (num_players + 2))

//change the wideness of the goal here (the smaller the wider)
//1 = height of the field, 2 = 1/2 height, 3 = 1/3, etc.
#define GOAL_WIDTH 4

class GameManager {
    private:
        bool quit;
        Ball* ball;
        int num_players;
        int width, height;
        int score_left, score_right;
        Player* players[MAX_PLAYERS];
        int dribbling_left_wall, dribbling_right_wall;
        int dribbling_top_wall, dribbling_bottom_wall;
        int top_wall, left_wall, bottom_wall, right_wall;
        int goal_y_max, goal_y_min;

    public:
        GameManager(int, int, int);
        ~GameManager();
        void score(bool);
        void reset();
        void raw_output();
        void draw();
        void input(packet *);
        void logic();
        void run();
};

#endif