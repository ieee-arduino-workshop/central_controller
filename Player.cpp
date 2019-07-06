#include "Player.h"

/**
 * Constructor.
 */
Player::Player(int pos_x, int pos_y) {
    dribbling = false;
    original_x = pos_x;
    original_y = pos_y;

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
inline void Player::setX(int new_x) {
    x = new_x;
}

/**
 * Get the x co-ordinate.
 *
 * @return The X position of the player.
 */
inline int Player::getX() {
    return x;
}

/**
 * Set the y co-ordinate.
 *
 * @param new_y
 */
inline void Player::setY(int new_y) {
    y = new_y;
}

/**
 * Get the y co-ordinate.
 *
 * @return The Y postion of the player.
 */
inline int Player::getY() {
    return y;
}

/**
 * Move up one unit.
 */
inline void Player::moveUp() {
    y++;
}

/**
 * Move down one unit.
 */
inline void Player::moveDown() {
    y--;
}

/**
 * Move left one unit.
 */
inline void Player::moveLeft() {
    x--;
}

/**
 * Move right one unit.
 */
inline void Player::moveRight() {
    x++;
}

/**
 * Move diagonally up and left one unit.
 */
inline void Player::moveUpLeft() {
    y--;
    x--;
}

/**
 * Move diagnolly up and right one unit.
 */
inline void Player::moveUpRight() {
    y--;
    x++;
}

/**
 * Move diagonally down and left one unit.
 */
inline void Player::moveDownLeft() {
    y++;
    x--;
}

/**
 * Move diagonally down and right one unit.
 */
inline void Player::moveDownRight() {
    y++;
    x++;
}

/**
 * Set the direction of the player.
 *
 * @param d The new direction of the player.
 */
inline void Player::setDirection(eDir d) {
    direction = d;
}

/**
 * Get the player's direction.
 *
 * @return The current direction of the player.
 */
inline eDir Player::getDirection() {
    return direction;
}

/**
 * Set the player's state as dribbling.
 *
 * @param b
 */
inline void Player::setDribbling(bool b) {
    dribbling = b;
}

/**
 * Get the player's dribbling state.
 *
 * @return Whether or not the player is dribbling.
 */
inline bool Player::isDribbling() {
    return dribbling;
}
