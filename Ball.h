#ifndef BALL_H
#define BALL_H
#include <cstdlib>
#include "direction.h"

class Ball {
    private:
        int x, y;
        int ori_x, ori_y;
        eDir direction;

    public:
        Ball(int, int);
        void reset();
        void move();

        int getX();
        int getY();

        void setX(int);
        void setY(int);

        void moveUp();
        void moveDown();

        void moveLeft();
        void moveRight();

        eDir getDirection();
        void setDirection(eDir);
        void randomDirection();
};

#endif
