#include "Player.h"
#include <Arduino.h>
/**
 * Constructor.
 */
Player::Player(int pos_x, int pos_y, bool t) {
    dribbling = false;
    stunned = false;
    original_x = pos_x;
    original_y = pos_y;
    direction = STOP;
    team = t;
    x = pos_x;
    y = pos_y;
}

/**
 * Reset the player's position to their initial co-ordinates.
 */
void Player::reset() {
    x = original_x;
    y = original_y;
}

/**
 * Set the player's x co-ordinate.
 *
 * @param new_x
 */
void Player::setX(int new_x) {
    x = new_x;
}

/**
 * Get the x co-ordinate.
 *
 * @return The X position of the player.
 */
int Player::getX() {
    return x;
}

/**
 * Set the y co-ordinate.
 *
 * @param new_y
 */
void Player::setY(int new_y) {
    y = new_y;
}

/**
 * Get the y co-ordinate.
 *
 * @return The Y postion of the player.
 */
int Player::getY() {
    return y;
}

/**
 * Move up one unit.
 */
void Player::moveUp() {
    y--;
}

/**
 * Move down one unit.
 */
void Player::moveDown() {
    y++;
}

/**
 * Move left one unit.
 */
void Player::moveLeft() {
    x--;
}

/**
 * Move right one unit.
 */
void Player::moveRight() {
    x++;
}

/**
 * Move diagonally up and left one unit.
 */
void Player::moveUpLeft() {
    y--;
    x--;
}

/**
 * Move diagnolly up and right one unit.
 */
void Player::moveUpRight() {
    y--;
    x++;
}

/**
 * Move diagonally down and left one unit.
 */
void Player::moveDownLeft() {
    y++;
    x--;
}

/**
 * Move diagonally down and right one unit.
 */
void Player::moveDownRight() {
    y++;
    x++;
}

/**
 * Set the direction of the player.
 *
 * @param d The new direction of the player.
 */
void Player::setDirection(eDir d) {
    direction = d;
}

/**
 * Get the player's direction.
 *
 * @return The current direction of the player.
 */
eDir Player::getDirection() {
    return direction;
}

/**
 * Get the player's team.
 *
 * @return The current team of the player.
 */
bool Player::getTeam() {
    return team;
}

/**
 * Set the player's state as dribbling.
 *
 * @param b
 */
void Player::setDribbling(bool b) {
    dribbling = b;
}

/**
 * Get the player's dribbling state.
 *
 * @return Whether or not the player is dribbling.
 */
bool Player::isDribbling() {
    return dribbling;
}

bool Player::getStun(){
    return stunned;
}

void Player::setStun(int count){
    stun_time = count;
    stunned = true;
}

void Player::decreaseStun(){
    stun_time--;
    if (stun_time <= 0){
        stunned = false;
    }
    Serial.print("Stun Time: ");
    Serial.println(stun_time);
}