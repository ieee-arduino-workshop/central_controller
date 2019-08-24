#include "Ball.h"
#include <Arduino.h>

/**
 * Constructor.
 */
Ball::Ball(int pos_x, int pos_y, int s, int srr)
{
    x = pos_x;
    y = pos_y;
    ori_x = pos_x;
    ori_y = pos_y;
    current_speed = s;
    init_speed = s;
    direction = STOP;
    speed_reduction_rate = srr;
    //tick_counter = speed_reduction_rate;
    speed_float = (float)current_speed*1.0;
    momentum = false;
}

/**
 * Reset the ball to it's initial co-ordinates.
 */
void Ball::reset()
{
    x = ori_x;
    y = ori_y;
    direction = STOP;
    current_speed=init_speed;
    speed_float = (float)current_speed*1.0;
}

/**
 * Ball direction change mechanics.
 */
void Ball::move()
{
    // if (getSpeed())
    // {
    // decreaseSpeed();
    switch (direction)
    {
    case LEFT:
        x -= current_speed;
        break;
    case RIGHT:
        x += current_speed;
        break;
    case UP:
        y -= current_speed;
        break;
    case DOWN:
        y += current_speed;
        break;
    case UPLEFT:
        x -= current_speed;
        y -= current_speed;
        break;
    case UPRIGHT:
        x += current_speed;
        y -= current_speed;
        break;
    case DOWNLEFT:
        x -= current_speed;
        y += current_speed;
        break;
    case DOWNRIGHT:
        x += current_speed;
        y += current_speed;
        break;
    default:
        break;
    }

    /// when ball direction is not stop and speed is >0 
    if (current_speed > 0 && direction!=STOP)
    {
        // current_speed--;
        decreaseSpeed();
        // Serial.print("curent speed: ");
        // Serial.println(current_speed);
    }
    else
    {
        direction = STOP;
        current_speed=init_speed;
        speed_float = (float)current_speed*1.0;
    }
    
}

/**
 * Get the ball's x co-ordinate.
 */
int Ball::getX()
{
    return x;
}

/**
 * Get the ball's y co-ordinate.
 */
int Ball::getY()
{
    return y;
}

/**
 * Set the x co-ordinate of the ball.
 *
 * @param new_x
 */
void Ball::setX(int new_x)
{
    x = new_x;
}

/**
 * Set the y co-ordinate of the ball.
 *
 * @param new_y
 */
void Ball::setY(int new_y)
{
    y = new_y;
}

/**
 * Move the ball up one unit.
 */
void Ball::moveUp()
{
    y--;
}

/**
 * Move the ball down one unit.
 */
void Ball::moveDown()
{
    y++;
}

/**
 * Move the ball left one unit.
 */
void Ball::moveLeft()
{
    x--;
}

/**
 * Move the ball right one unit.
 */
void Ball::moveRight()
{
    x++;
}

/**
 * Get the ball's current direction.
 *
 * @return Enumerated ball direction.
 */
eDir Ball::getDirection()
{
    return direction;
}

/**
 * Set the ball's current direction.
 *
 * @param d
 */
void Ball::setDirection(eDir d)
{
    direction = d;
}

/**
 * Set the ball's direction randomly.
 */
void Ball::randomDirection()
{
    //random number from 1-9
    direction = (eDir)(random(1, 9));
}

void Ball::decreaseSpeed()
{

    if (momentum == true)
    {
        // if (tick_counter % speed_reduction_rate)
        // {
        //     // current_speed = current_speed - 1;
        // }
        // else if (!current_speed)
        // {
        //     tick_counter = 0;
        // }
        speed_float = speed_float*(100-speed_reduction_rate)/100.0;
        current_speed  = (int)speed_float;
    }
    else
    {
        current_speed = init_speed;
    }
    // // tick_counter++;
    // Serial.print("Momentum: ");
    // Serial.println(current_speed);
}

void Ball::setMomentum(bool m)
{
    momentum = m;
}

int Ball::getSpeed()
{
    return current_speed;
}

void Ball::resetSpeed()
{
    current_speed=init_speed;
    speed_float = (float)current_speed*1.0;
}