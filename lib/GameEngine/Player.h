#ifndef PLAYER_H
#define PLAYER_H

#include "direction.h"
#include <Arduino.h>
// #include "GameManager.h"

#define SPEED 2

class Player {
    private:
        // position of the player
        int x, y;

        // id of the player
        uint8_t id;

        // whether or not the player is dribbling the ball
        bool dribbling;

        // the team assigned to the player (left[0] or right[1] team)
        bool team;

        // tackled status of the player
        bool stunned;
        int stun_time;

        // direction of the player
        eDir direction;

        // initial co-ordinates
        int original_x, original_y;

    public:
        Player(int, int, bool, uint8_t);

        void reset();

        int getX();
        int getY();

        void setX(int);
        void setY(int);

        void moveUp();
        void moveDown();

        void moveLeft();
        void moveRight();

        void moveUpRight();
        void moveUpLeft();

        void moveDownLeft();
        void moveDownRight();

        void setDirection(eDir);
        eDir getDirection();
        
        bool getTeam();
        
        bool getStun();
        void setStun(int);
        void decreaseStun();
        
        void setDribbling(bool);
        bool isDribbling();

        uint8_t getId ();
};

#endif
