#ifndef BALL_H
#define BALL_H
// #include <cstdlib>
#include "direction.h"
#include <Arduino.h>

/**
 * @brief class ball
 * 
 */
class Ball {
    private:
        int x, y;
        int ori_x, ori_y;
        eDir direction;
        int current_speed;  
        int init_speed; //store the init speed of the ball
        // int tick_counter;
        float speed_float;  // need to save speed in float number to calculate momemtum
        int speed_reduction_rate;   // rate from 0 - 100%. The bigger rate, the faster the ball stop.
        bool momentum;  //  enable/disable ball momentum 20/08/2019

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
        void resetSpeed(); //reset ball init speed;
};

#endif
