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

/// declare offset of screen based on FPGA configuration
#define SCR_EDGE_L 20   // x left
#define SCR_EDGE_R 780  //x right
#define SCR_EDGE_T 40   // y top
#define SCR_EDGE_B 560  // y bottom

#define OFFSET_X 40
#define OFFSET_Y 60

#define MAX_PLAYERS 12

#define L_TEAM 0
#define R_TEAM 1

#define L_TEAM_X (width / 4 +  OFFSET_X)
#define R_TEAM_X (3 * width / 4 + OFFSET_Y)

#define L_TEAM_Y(c) (height * (c + 2) / (num_players + 2) + OFFSET_X)
#define R_TEAM_Y(c) (height * (c + 1) / (num_players + 2) + OFFSET_Y)

#define WITHIN_GOAL(y) (ball_y >= goal_y_min && ball_y <= goal_y_max)

#define BALL_SPEED 10
#define BALL_SPEED_REDUCTION_RATE 5 //  5% - the higher value, the faster the ball stop. 
#define PLAYER_SPEED 6

//change the wideness of the goal here (the smaller the wider)
//1 = height of the field, 2 = 1/2 height, 3 = 1/3, etc.
#define GOAL_WIDTH 4

#define DISTANCE_BETWEEN_BALL_AND_PLAYER 8

#define STUN_TIME 50

class GameManager
{
private:
    bool quit;
    Ball *ball;
    uint16_t num_players;
    uint16_t width, height;
    uint16_t score_left, score_right;
    Player *players[MAX_PLAYERS];
    uint16_t dribbling_left_wall, dribbling_right_wall;
    uint16_t dribbling_top_wall, dribbling_bottom_wall;
    uint16_t top_wall, left_wall, bottom_wall, right_wall;
    uint16_t goal_y_max, goal_y_min;
    Player *last_player;
    bool last_player_team;

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
    void send();
};

#endif
