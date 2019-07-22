/*
Soccer Game Manager to be used for arduino platform
Authors: Sachith Sirimanna, Anthony Milic, Le Hai Truong
 */
#include <Arduino.h>
#include "GameManager.h"
#include "direction.h"
#include "packet.h"

using namespace std;

/**
 * Constructor.
 */
GameManager::GameManager(int w, int h, int np) {
	quit = false;
	num_players = np;   //number of players
	//Set scores to zeros
	score_left = score_right = 0;

	// Width 0 -> +X & Height 0 -> -Y
	width = w; height = h;

	// Set wall parameters
	left_wall = 0;
	dribbling_left_wall = 1;
	
	right_wall = width - 1;
	dribbling_right_wall = width - 2;
	
	top_wall = 0;
	dribbling_top_wall = 1;
	
	bottom_wall = height - 1;
	dribbling_bottom_wall = height - 2;

	// Set goal parameters
	goal_y_min = height*(GOAL_WIDTH - 1)/(2*GOAL_WIDTH);
	goal_y_max = height*(GOAL_WIDTH + 1)/(2*GOAL_WIDTH);
	
	// load players
	for (int i = 0; i < num_players ; i++) {
		// even players on the left side
		if (i % 2 == 0) {
			players[i] = new Player(L_TEAM_X, L_TEAM_Y(i), L_TEAM);
		}

		// odd players on the right side
		else {
			players[i] = new Player(R_TEAM_X, R_TEAM_Y(i), R_TEAM);
		}
	}

	// set up the ball
	ball = new Ball(width / 2, height / 2);
	
}

/**
 * Destructor.
 */
GameManager::~GameManager() {
	for (int i = 0; i < num_players; i++) {
		delete players[i];
	}

	delete ball;
}

/**
 * Reset the players and the ball.
 */
void GameManager::reset() {
	for (int i = 0; i < num_players; i++){
		players[i]->reset();
		players[i]->setDribbling(false);
	}

	ball->reset();
}


/**
 * Draw the field, ball, and players to STDOUT.
 */
void GameManager::draw() {
	// Clear the terminal output
	
	
	// Get the location of all objects
	int player_x[num_players];
	int player_y[num_players];
	eDir player_direction[num_players];
	bool player_stun[num_players];
	for (int i = 0; i < num_players; i++){
		player_x[i] = players[i]->getX();
		player_y[i] = players[i]->getY();
		player_direction[i] = players[i]->getDirection();
		player_stun[i] = players[i]->getStun();
	}
	int ball_x = ball->getX();
	int ball_y = ball->getY();

	//Display current player and ball position
	Serial.println((String)"Ball X: " + ball_x + " Ball Y: " + ball_y);
	for (int i = 0; i < num_players; i++){
		Serial.print("Player ");
		Serial.print(i+1);
		Serial.print(" X: ");
		Serial.print(player_x[i]);
		Serial.print("\tY: ");
		Serial.print(player_y[i]);
		Serial.print("\tDirection: ");
		// Serial.print("Before switch case");
		switch (player_direction[i])
		{
		case STOP:
			Serial.print("STOP");
			break;
		case LEFT:
			Serial.print("LEFT");
			break;
		case RIGHT:
			Serial.print("RIGHT");
			break;
		case UP:
			Serial.print("UP");
			break;
		case DOWN:
			Serial.print("DOWN");
			break;
		case UPLEFT:
			Serial.print("UPLEFT");
			break;
		case UPRIGHT:
			Serial.print("UPRIGHT");
			break;
		case DOWNLEFT:
			Serial.print("DOWNLEFT");
			break;
		case DOWNRIGHT:
			Serial.print("DOWNRIGHT");
			break;
		default:
			break;
		}
		Serial.println();
	}
	
	//Display current score
	Serial.println((String)"Score Left: " + score_left + " Score Right: " + score_right);
	
	
	
	//Draw the top wall for the game
	for (int i = 0; i < width + 2; i++) {
		Serial.print("\xB2");
	}
	Serial.println();

	// Draw columns - Draw the 2 side wall and all the ojebcts inbetween
	for (int i = 0; i < height; i++){

		// Draw rows
		for (int j = 0; j < width; j++){
			
			// Draw the wall part at the start of every row - Using HEX character codes
			//if height is outside goal area then draw wall, else draw goal
			if (j == 0 ) {
				if (i < goal_y_min || i > goal_y_max ){
					Serial.print("\xB2");
				}
				else{
					Serial.print("|");
				}
			}
			
			//Draw player location (modify depends how many players)
			if (player_x[0] == j && player_y[0] == i) {
				if (!player_stun[0]){
					Serial.print("1");
				}
				else {
					Serial.print("X");
				}
				
			}
			else if (player_x[1] == j && player_y[1] == i) {
				if (!player_stun[1]){
					Serial.print("2");
				}
				else {
					Serial.print("X");
				}
			}
			else if (player_x[2] ==j && player_y[2] == i) {
				Serial.print("3");
			}
			else if (player_x[3] == j && player_y[3] == i) {
				Serial.print("4");
			}
			// else if (player_x[4] ==j && player_y[4] == i) {
			//     Serial.print("5");
			// }
			// else if (player_x[5] == j && player_y[5] == i) {
			//     Serial.print("6");
			// }
			// Draw the ball
			else if (ball_x == j && ball_y == i) {
				Serial.print("O");
			}
			// Draw empty space
			else { Serial.print(" "); }

		   // Draw the wall part at the end of every row
			if (j == width - 1) {
				//if height is outside goal area then draw wall, else draw goal
				if (i < goal_y_min || i > goal_y_max ){
					Serial.print("\xB2");
				}
				else{
					Serial.print("|");
				}
			}
		}
		Serial.println();
	}

	// Draw the bottom wall
	for (int i = 0; i < width + 2; i++) {
		Serial.print("\xB2");
	}
	Serial.println();
	

}

/**
 * Listen for the player's inputs. update current player input
 */
void GameManager::input(packet *p) {
	// Get location of all objects of the certain player
	int i = p->player_id - 1;
	int player_x = players[i]->getX();
	int player_y = players[i]->getY();
	int player_dribble = players[i]->isDribbling();
	bool player_stun = players[i]->getStun();
	Serial.println("\033[0H\033[0J");
	Serial.print("INPUT STR:");
	Serial.print(" R: "); Serial.print(p->right);
	Serial.print(" L: "); Serial.print(p->left);
	Serial.print(" U: "); Serial.print(p->up);
	Serial.print(" D: "); Serial.print(p->down);
	Serial.print(" ID: "); Serial.println(p->player_id);

	
	//if dribble is on, the "dribble_wall" position is changed
	//When the player is dribbling the ball, they cannot move
	//up against the wall or the ball may clip through
	if(player_dribble) {
		dribbling_left_wall = 1;
		dribbling_top_wall = 1;
		dribbling_right_wall = width - 2;
		dribbling_bottom_wall = height - 2;
	}
	else{
		dribbling_left_wall = left_wall;
		dribbling_top_wall = top_wall;
		dribbling_right_wall = right_wall;
		dribbling_bottom_wall = bottom_wall;
	}

	if (!player_stun){
		
		if (p->left) { 
			//Prevents player from moving through wall
			if (player_x > dribbling_left_wall){
				players[i]->moveLeft();
			}
			//Prevents player from looking at wall while next to it
			//This could cause the ball to clip through the wall
			if (player_x > left_wall){
				players[i]->setDirection(LEFT);
			//changes the direction the player is looking 
			//if they are looking directly at the wall
			}else if (players[i]->getDirection() == LEFT){
				players[i]->setDirection(RIGHT);
			}
		} 
		else if(p->right){ 
			//Prevents player from moving through wall
			if (player_x < dribbling_right_wall){
				players[i]->moveRight();
			}
			//Prevents player from looking at wall while next to it
			//This could cause the ball to clip through the wall
			if (player_x < right_wall){
				players[i]->setDirection(RIGHT);
			//changes the direction the player is looking 
			//if they are looking directly at the wall
			}else if (players[i]->getDirection() == RIGHT){
				players[i]->setDirection(LEFT);
			}
		} 
		
		if (p->up){
			//Prevents player from moving through wall
			if (player_y > dribbling_top_wall){
				players[i]->moveUp();
			}
			//Prevents player from looking at wall while next to it
			//This could cause the ball to clip through the wall
			if (player_y > top_wall){
				//checks whether right or left have been detected previously
				//If so, enables diagonal facing
				if(players[i]->getDirection() == LEFT ){
					players[i]->setDirection(UPLEFT);
				} else if (players[i]->getDirection() == RIGHT ){
					players[i]->setDirection(UPRIGHT);
				} else {
					players[i]->setDirection(UP);
				} 
			//changes the direction the player is looking 
			//if they are looking directly at the wall
			}else if (players[i]->getDirection() == UP ){
				players[i]->setDirection(DOWN);
			}
		}
		else if (p->down){
			//Prevents player from moving through wall
			if (player_y < dribbling_bottom_wall){
				players[i]->moveDown();
			}
			//Prevents player from looking at wall while next to it
			//This could cause the ball to clip through the wall
			if (player_y < bottom_wall){
				//checks whether right or left have been detected previously
				//If so, enables diagonal facing
				if(players[i]->getDirection() == LEFT ){
					players[i]->setDirection(DOWNLEFT);
				} else if (players[i]->getDirection() == RIGHT ){
					players[i]->setDirection(DOWNRIGHT);
				} else {
					players[i]->setDirection(DOWN);
				}
			//changes the direction the player is looking 
			//if they are looking directly at the wall
			}else if (players[i]->getDirection() == DOWN ){
				players[i]->setDirection(UP);
			}
		}

		//Changes the balls position based upon the 
		//direction the dribbling player is facing
		player_x = players[i]->getX();
		player_y = players[i]->getY();
		if(player_dribble){
			switch(players[i]->getDirection()){
				case LEFT:
					ball->setX(player_x - 1);
					ball->setY(player_y);
					break;
				case UP:
					ball->setX(player_x);
					ball->setY(player_y - 1);
					break;
				case RIGHT:
					ball->setX(player_x + 1);
					ball->setY(player_y);
					break;
				case DOWN:
					ball->setX(player_x);
					ball->setY(player_y + 1);
					break;
				case UPLEFT:
					ball->setX(player_x - 1);
					ball->setY(player_y - 1);
					break;
				case UPRIGHT:
					ball->setX(player_x + 1);
					ball->setY(player_y - 1);
					break;
				case DOWNRIGHT:
					ball->setX(player_x + 1);
					ball->setY(player_y + 1);
					break;
				case DOWNLEFT:
					ball->setX(player_x - 1);
					ball->setY(player_y + 1);
					break;
				default: break;
			}
			ball->setDirection(players[i]->getDirection());

			// kick - Key press
			if (p->kick) {
				players[i]->setDribbling(false);
			}
		}
	}

}


/**
 * Update the game score
 */
void GameManager::score(bool team)  //update score of a particular player
	{
		if (team == L_TEAM) //if address of player belong to player 1
			score_left++;
		else if (team == R_TEAM)    //else if address of player belong to player 2
			score_right++;

		reset();
	}

/**
 * Game logic functionality. Ball bouncing, kicking, player position boundary
 * check, and ball position boundary check.
 */
void GameManager::logic() {
	// Get location of all objects
	int player_x[num_players];
	int player_y[num_players];
	int player_dribble[num_players];

	for (int i = 0; i < num_players; i++){
		player_x[i] = players[i]->getX();
		player_y[i] = players[i]->getY();
		player_dribble[i] = players[i]->isDribbling();
	}

	int ball_x = ball->getX();
	int ball_y = ball->getY();

	// Bottom wall hit. TODO: ADD REFLECTED BOUNCE FOR STRAIGHT DIRECTION
	if (ball_y == height - 1) {
		switch (ball->getDirection()) {
		case DOWN:
			ball->setDirection(UP);
			break;
		case DOWNRIGHT:
			ball->setDirection(UPRIGHT);
			break;
		case DOWNLEFT:
			ball->setDirection(UPLEFT);
			break;
		default:
			break;
		}
	}

	// Top wall hit
	if (ball_y == 0) {
		switch (ball->getDirection()) {
		case UP:
			ball->setDirection(DOWN);
			break;
		case UPRIGHT:
			ball->setDirection(DOWNRIGHT);
			break;
		case UPLEFT:
			ball->setDirection(DOWNLEFT);
			break;
		default:
			break;
		}
	}

	// Right wall hit
	if (ball_x == (width - 1) && (ball_y < goal_y_min || ball_y > goal_y_max)) {
		switch (ball->getDirection()) {
		case RIGHT:
			ball->setDirection(LEFT);
			break;
		case UPRIGHT:
			ball->setDirection(UPLEFT);
			break;
		case DOWNRIGHT:
			ball->setDirection(DOWNLEFT);
			break;
		default:
			break;
		}
	}
	// Right goal hit
	else if (ball_x == (width - 1) && (ball_y >= goal_y_min || ball_y <= goal_y_max )){
		score(L_TEAM);
	}

	// Left wall hit
	if (ball_x == 0 && (ball_y < goal_y_min || ball_y > goal_y_max )) {
		switch (ball->getDirection()) {
		case LEFT:
			ball->setDirection(RIGHT);
			break;
		case UPLEFT:
			ball->setDirection(UPRIGHT);
			break;
		case DOWNLEFT:
			ball->setDirection(DOWNRIGHT);
			break;
		default:
			break;
		}
	}
	// Left goal hit
	else if (ball_x == 0 && (ball_y >= goal_y_min || ball_y <= goal_y_max )){
		score(R_TEAM);
	}

	//ball should move if no player is dribbling it
	bool dribbling = false;
	// checking ball not being dribble by players
	for (int i = 0; i < num_players; i++){
		if (player_dribble[i]) {
			dribbling = true;
		}
	}
	//if ball is not being dribble by players then ball can move
	if (!dribbling){
		ball->move();
	}

	// Get location of all objects
	for (int i = 0; i < num_players; i++){
		player_x[i] = players[i]->getX();
		player_y[i] = players[i]->getY();
		player_dribble[i] = players[i]->isDribbling();
	}
	ball_x = ball->getX();
	ball_y = ball->getY();

	

	//Resets variables used for game logic
	bool same_player = false;
	bool tackling = false;
	Player *player_close = NULL;
	Player *tackle_player = NULL;
	if(last_player != NULL){
		last_player->setDribbling(false);
	}

	// Calculate the distance between the ball and player
	for (int i = 0; i < num_players; i++){
		// check if the current player is stunned, if they are decrease stun
		if((players[i]->getStun())) {
			players[i]->decreaseStun();
		}else{
			//Checks which players are close enough to contest the ball
			int distance_between_player_and_ball = sqrt(pow((ball_x - player_x[i]), 2) + pow((ball_y - player_y[i]), 2));
			if (distance_between_player_and_ball <= 1) {
				//Stores a player who could get the ball
				//Often overwritten
				player_close = players[i];
				//Check whether last dribbling player is still near ball
				if(last_player == players[i]){
					same_player = true;
				}
				//Checks whether a tackle is occuring
				if (players[i]->getTeam() != last_player_team){
					//stores a player who could tackle the ball
					//Often overwritten
					tackle_player = players[i];
					tackling = true;
				}
			}
		}
		
	}
	//If the same player as last time is near the ball and there is no tackle
	//That player shall keep the ball
	if (same_player && !tackling){
		last_player->setDribbling(true);
	//If the same player as last time is near the ball and there is tackling
	//The previous player is stunned, and a tackling player gets the ball
	//Priority given to players later in the players[] array
	}else if (same_player && tackling){
		if(last_player != NULL){
			last_player->setStun(50);// set stun to true for 10 frames
		}
		tackle_player->setDribbling(true);
		last_player = tackle_player;
		last_player_team = tackle_player->getTeam();
	//If the player who was dribbling the ball is no longer dribbling the ball
	//A nearby player will get the ball
	//Priority given to players later in the players[] array
	}else if (!same_player){
		last_player = player_close;
		if(player_close != NULL){
			player_close->setDribbling(true);
			last_player_team = player_close->getTeam();
		//If there were no players nearby, last_player is NULL
		}else{
			last_player = NULL;
		}
	}
}
/*
	Output Raw data from game engine
 */
void GameManager::raw_output(){
	//clear terminal
	Serial.println("\033[0H\033[0J");
	// Get the location of all objects
	int player_x[num_players];
	int player_y[num_players];
	eDir player_direction[num_players];

	
	for (int i = 0; i < num_players; i++){
		player_x[i] = players[i]->getX();
		player_y[i] = players[i]->getY();
		player_direction[i] = players[i]->getDirection();
	}


	//Display ball position
	// Serial.print("Ball X: ");
	Serial.print(ball->getX());
	// Serial.print("\tBall Y: ");
	Serial.println(ball->getY());
	//Display player position
	for (int i = 0; i < num_players; i++){
		Serial.print("Player ");
		Serial.print(i+1);
		Serial.print(" = X: ");
		Serial.print(player_x[i]);
		Serial.print("\tY: ");
		Serial.print(player_y[i]);
		Serial.print("\tDirection: ");
		switch (player_direction[i])
		{
		case STOP:
			Serial.println("STOP");
			break;
		case LEFT:
			Serial.println("LEFT");
			break;
		case RIGHT:
			Serial.println("RIGHT");
			break;
		case UP:
			Serial.println("UP");
			break;
		case DOWN:
			Serial.println("DOWN");
			break;
		case UPLEFT:
			Serial.println("UPLEFT");
			break;
		case UPRIGHT:
			Serial.println("UPRIGHT");
			break;
		case DOWNLEFT:
			Serial.println("DOWNLEFT");
			break;
		case DOWNRIGHT:
			Serial.println("DOWNRIGHT");
			break;
		default:
			break;
		}
	}
	
	//Display current score
	Serial.println((String)"Score Left: " + score_left + " Score Right: " + score_right);
}

/**
 * Draw the game and monitor input if in debugging mode. Run game logic regardless.
 */
void GameManager::run() {
	// While q (quit) button is not pressed
	while (!quit) {
	
		// Draw the board
		draw();

		// Record input from player
		// input();
	

		// Check logic each frame (not needed atm)
		logic();
	}
}