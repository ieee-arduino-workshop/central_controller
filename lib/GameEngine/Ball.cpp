#include "Ball.h"
#include <Arduino.h>

/**
 * Constructor.
 */
Ball::Ball(int pos_x, int pos_y, int s, int srr) {
    x = pos_x;
    y = pos_y;
    ori_x = pos_x;
    ori_y = pos_y;
    speed_temp = s;
    speed_original = s;
    direction = STOP;
    speed_reduction_rate = srr;
}

/**
 * Reset the ball to it's initial co-ordinates.
 */
void Ball::reset() {
    x = ori_x;
    y = ori_y;
    direction = STOP;
}

/**
 * Ball direction change mechanics.
 */
void Ball::move() {
    if(getSpeed()){
        decreaseSpeed();
        switch (direction) {
            case LEFT:
                x -= speed_temp;
                break;
            case RIGHT:
                x += speed_temp;
                break;
            case UP:
                y -= speed_temp;
                break;
            case DOWN:
                y += speed_temp;
                break;
            case UPLEFT:
                x -= speed_temp;
                y -= speed_temp;
                break;
            case UPRIGHT:
                x += speed_temp;
                y -= speed_temp;
                break;
            case DOWNLEFT:
                x -= speed_temp;
                y += speed_temp;
                break;
            case DOWNRIGHT:
                x += speed_temp;
                y += speed_temp;
                break;
            default:
                break;
        }
    }
}

/**
 * Get the ball's x co-ordinate.
 */
int Ball::getX() {
    return x;
}

/**
 * Get the ball's y co-ordinate.
 */
int Ball::getY() {
    return y;
}

/**
 * Set the x co-ordinate of the ball.
 *
 * @param new_x
 */
void Ball::setX(int new_x) {
    x = new_x;
}

/**
 * Set the y co-ordinate of the ball.
 *
 * @param new_y
 */
void Ball::setY(int new_y) {
    y = new_y;
}

/**
 * Move the ball up one unit.
 */
void Ball::moveUp() {
    y--;
}

/**
 * Move the ball down one unit.
 */
void Ball::moveDown() {
    y++;
}

/**
 * Move the ball left one unit.
 */
void Ball::moveLeft() {
    x--;
}

/**
 * Move the ball right one unit.
 */
void Ball::moveRight() {
    x++;
}

/**
 * Get the ball's current direction.
 *
 * @return Enumerated ball direction.
 */
eDir Ball::getDirection() {
    return direction;
}

/**
 * Set the ball's current direction.
 *
 * @param d
 */
void Ball::setDirection(eDir d) {
    direction = d;
}

/**
 * Set the ball's direction randomly.
 */
void Ball::randomDirection() {
    //random number from 1-9
    direction = (eDir) (random(1,9));
}

void Ball::decreaseSpeed() {
    if (momentum == true) {
        if (tick_counter % speed_reduction_rate) {
            speed_temp = speed_temp - 1;
        } else if (!speed_temp) {
            tick_counter = 0;
        }
    } else {
        speed_temp = speed_original;
    }
    tick_counter++;
    Serial.print("Momentum: ");
    Serial.println(speed_reduction_rate);
}

void Ball::setMomentum(bool m){
    momentum = m;
}

int Ball::getSpeed() {
    return speed_temp;
}