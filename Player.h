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

        inline int getX();
        inline int getY();

        inline void setX(int);
        inline void setY(int);

        inline void moveUp();
        inline void moveDown();

        inline void moveLeft();
        inline void moveRight();

        inline void moveUpRight();
        inline void moveUpLeft();

        inline void moveDownLeft();
        inline void moveDownRight();

        void changeDirection(eDir);
        inline eDir getDirection();
        
        void setDribbling(bool);
        inline bool isDribbling();
};

#endif
