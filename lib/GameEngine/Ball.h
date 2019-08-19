#ifndef BALL_H
#define BALL_H
// #include <cstdlib>
#include "direction.h"
#include <Arduino.h>

class Ball {
    private:
        int x, y;
        int ori_x, ori_y;
        eDir direction;
        int speed_temp;
        int speed_original;
        int tick_counter = 0;
        int speed_reduction_rate;
        bool momentum;

    public:
        Ball(int, int, int, int);
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

        void decreaseSpeed();
        void setMomentum(bool);
        int getSpeed();
};

#endif
