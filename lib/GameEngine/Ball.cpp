#include "Ball.h"
#include <Arduino.h>

#define BALL_SPEED 5

/**
 * Constructor.
 */
Ball::Ball(int pos_x, int pos_y) {
    x = pos_x;
    y = pos_y;
    ori_x = pos_x;
    ori_y = pos_y;
    direction = STOP;
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
    switch (direction) {
        case LEFT:
            x = x - BALL_SPEED;
            break;
        case RIGHT:
            x = x + BALL_SPEED;
            break;
        case UP:
            y = y - BALL_SPEED;
            break;
        case DOWN:
            y = y + BALL_SPEED;
            break;
        case UPLEFT:
            x = x - BALL_SPEED;
            y = y - BALL_SPEED;
            break;
        case UPRIGHT:
            x = x + BALL_SPEED;
            y = y - BALL_SPEED;
            break;
        case DOWNLEFT
            x = x - BALL_SPEED;
            y = y + BALL_SPEED;
            break;
        case DOWNRIGHT:
            x = x + BALL_SPEED;
            y = y + BALL_SPEED;
            break;
        default:
            break;
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
