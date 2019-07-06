#ifndef PLAYER_H
#define PLAYER_H

#include "direction.h"

class Player {
    private:
        // position of the player
        int x, y;

        // whether or not the player is dribbling the ball
        bool dribbling;

        // direction of the player
        eDir direction;

        // initial co-ordinates
        int original_x, original_y;

    public:
        Player(int, int);

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
        
        void setDribbling(bool);
        bool isDribbling();
};

#endif
