#include "Ball.h"

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
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case UPLEFT:
            x--;
            y--;
            break;
        case UPRIGHT:
            x++;
            y--;
            break;
        case DOWNLEFT:
            x--;
            y++;
            break;
        case DOWNRIGHT:
            x++;
            y++;
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
    direction = rand() % 8 + 1;
}
