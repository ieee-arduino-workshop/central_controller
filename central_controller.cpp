#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum eDir {STOP = 0, LEFT, UPLEFT, DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT, UP, DOWN};	// 8 direction

class Player {
private:
	int x, y;	//position of player
	int original_x, original_y;	//reset coordinates
	
public:
	Player(int pos_x, int pos_y){ //constructor that take x and y coordinate
	
		original_x = pos_x; //used to reset the player later
		original_y = pos_y;
		x = pos_x; //set the current position of the player
		y = pos_y;
		
	}
	void Reset(){ //reset function
		x = original_x; y = original_y;
	}
	
	inline int getX() { return x; } //public get x and y function (use inline to replace those function definition wherever those are being called)
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	inline void moveLeft() { x--; }
	inline void moveRight() { x++; }
	
};

class Ball {
private:
	int x, y;
	int ori_x, ori_y;
	eDir direction;
public:
	Ball(int pos_x, int pos_y) {
		ori_x = pos_x;
		ori_y = pos_y;
		x = pos_x;
		y = pos_y;
		direction = STOP;
	}
	void Reset() {
		x = ori_x; y = ori_y;
		direction = STOP;
	}
	void changeDirection(eDir d){ //function to change direction of the ball
		direction = d;
	}
	void randomDirection() {
		direction = (eDir)((rand() % 8) + 1); //random number from 1-8
	}
	void Move() {
		switch (direction) {
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		default:
			break;
		}
	}
	inline int getX() { return x; } //public get x and y function (use inline to replace those function definition wherever those are being called)
	inline int getY() { return y; }
	inline void setX(int newX) { x = newX; }
	inline void setY(int newY) { y = newY; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	inline void moveLeft() { x--; }
	inline void moveRight() { x++; }
	inline int getDirection() { return direction; } //public get current direction
};

class game_manager {
private:
	int width, height;
	char up, down, left, right;
	bool quit, dribble;
	Player * p1;
	Ball * b1;
public:
	game_manager(int w, int h) {	//constructor
		quit = false;
		dribble = true;
		up = 'w', down = 's', left = 'a', right = 'd';
		width = w; height = h;
		p1 = new Player(w / 2, h / 2);	//set player in the middle
		b1 = new Ball(w / 2 + 1, h / 2);
	}

	~game_manager(){
		delete p1;
	}

	void reset() {
		p1->Reset();
	}

	void Draw() {	//for debug purposes

		system("cls");
		for (int i = 0; i < width + 2; i++) {	//draw the top wall for the game
			cout << "\xB2";
		}
		cout << endl;

		for (int i = 0; i < height; i++){	//2 side wall and all the ojects inbetween. COLUMN
		
			for (int j = 0; j < width; j++){	// ROW
				int player_x = p1->getX();
				int player_y = p1->getY();	//Get location of all objects (player)
				int ball_x = b1->getX();
				int ball_y = b1->getY();		//Get local of ball

				if (j == 0) {	//draw the wall part at the start of every row
					cout << "\xB2";	//hex character code
				}
				//Draw player location
				if (player_x == j && player_y == i) {
					cout << "\xFE"; //player
				}
				else if (ball_x == j && ball_y == i) {
					cout << "O"; //ball
				}
				else { cout << " "; }

				if (j == width - 1) {	//draw the wall part at the end of every row
					cout << "\xB2";
				}
			}
			cout << endl;
		}
		for (int i = 0; i < width + 2; i++) {	//draw the bottom wall
			cout << "\xB2";
		}
		cout << endl;
		
	}

	void Input() {
		
		
		int player_x = p1->getX();
		int player_y = p1->getY();	//Get location of all objects
		int ball_x = b1->getX();
		int ball_y = b1->getY();

		if (_kbhit())	//get user input
		{
			if (GetAsyncKeyState(87)) {	//ascii W checking asynchorously for Key state
				if ((player_y > 0) && (ball_y > 0)) {
					p1->moveUp();  	//move player
					if (dribble) {	//dribble ball if dribble flag is set
						b1->setY(p1->getY() - 1); b1->setX(p1->getX());	//set ball position near the player
						b1->changeDirection(UP);						//change current direction of the ball
					}
				}
			}
			if (GetAsyncKeyState(83)) {	//	S
				if ((player_y < height - 1) && (ball_y < height - 1)) {
					p1->moveDown();	 
					if (dribble) {
						b1->setY(p1->getY() + 1); b1->setX(p1->getX());
						b1->changeDirection(DOWN);
					}
				}
			}
			if (GetAsyncKeyState(65)) {	//	A
				if ((player_x > 0) && (ball_x > 0)) {
					p1->moveLeft();	
					if (dribble) {
						b1->setX(p1->getX() - 1); b1->setY(p1->getY());
						b1->changeDirection(LEFT);
					}
				}
			}
			if (GetAsyncKeyState(68)) {	//	D
				if ((player_x < width - 1) && (ball_x < width - 1)) {
					p1->moveRight(); 
					if (dribble) {
						b1->setX(p1->getX() + 1); b1->setY(p1->getY());
						b1->changeDirection(RIGHT);
					}
				}
			}
			if (dribble) {
				if (GetAsyncKeyState(87) && GetAsyncKeyState(68)) {	//W&D	sticky ball
					if ((ball_y > 0) && (ball_x < width - 1)) {
						b1->setY(p1->getY() - 1); b1->setX(p1->getX() + 1);
						b1->changeDirection(UPRIGHT);
					}
				}
				else if (GetAsyncKeyState(87) && GetAsyncKeyState(65)) {	//W&A
					if ((ball_y > 0) && (ball_x > 0)) {
						b1->setY(p1->getY() - 1); b1->setX(p1->getX() - 1);
						b1->changeDirection(UPLEFT);
					}
				}
				else if (GetAsyncKeyState(83) && GetAsyncKeyState(65)) {	//S&A
					if ((ball_y < height - 1) && (ball_x > 0)) {
						b1->setY(p1->getY() + 1); b1->setX(p1->getX() - 1);
						b1->changeDirection(DOWNLEFT);
					}
				}
				else if (GetAsyncKeyState(83) && GetAsyncKeyState(68)) {	//S&D
					if ((ball_y < height - 1) && (ball_x < width - 1)) {
						b1->setY(p1->getY() + 1); b1->setX(p1->getX() + 1);
						b1->changeDirection(DOWNRIGHT);
					}
				}
			}
			if (GetAsyncKeyState(VK_SPACE)) {
				dribble = false;
			}
			if (GetAsyncKeyState(82)) {	// R
				p1->Reset();
				b1->Reset();
			}
			if (GetAsyncKeyState(81)) {	//ascii Q quit the game with q
				quit = true;
			}
		}
	}

	void Logic() {
		if (!dribble) {
			b1->Move(); //if ball is not being dribble by player it moves freely
		}
		int player_x = p1->getX();
		int player_y = p1->getY();	//Get location of all objects
		int ball_x = b1->getX();
		int ball_y = b1->getY();

		int d_AB = sqrt(pow((ball_x - player_x), 2) + pow((ball_y - player_y), 2));// calculate the distance between the ball and player
		//catching the ball when it touches the player
		if (d_AB == 1) {
			dribble = true;
		}
		//bottom wall hit. TODO: ADD REFLECTED BOUNCE FOR STRAIGHT DIRECTION
		if (ball_y == height - 1) {
			switch (b1->getDirection()) {
			case DOWN:
				b1->changeDirection(UP);
				break;
			case DOWNRIGHT:
				b1->changeDirection(UPRIGHT);
				break;
			case DOWNLEFT:
				b1->changeDirection(UPLEFT);
				break;
			default:
				break;
			}
		}
		//top wall hit
		if (ball_y == 0) {
			switch (b1->getDirection()) {
			case UP:
				b1->changeDirection(DOWN);
				break;
			case UPRIGHT:
				b1->changeDirection(DOWNRIGHT);
				break;
			case UPLEFT:
				b1->changeDirection(DOWNLEFT);
				break;
			default:
				break;
			}
		}
		//right wall hit
		if (ball_x == width - 1) {
			switch (b1->getDirection()) {
			case RIGHT:
				b1->changeDirection(LEFT);
				break;
			case UPRIGHT:
				b1->changeDirection(UPLEFT);
				break;
			case DOWNRIGHT:
				b1->changeDirection(DOWNLEFT);
				break;
			default:
				break;
			}
		}
		//left wall hit
		if (ball_x == 0) {
			switch (b1->getDirection()) {
			case LEFT:
				b1->changeDirection(RIGHT);
				break;
			case UPLEFT:
				b1->changeDirection(UPRIGHT);
				break;
			case DOWNLEFT:
				b1->changeDirection(DOWNRIGHT);
				break;
			default:
				break;
			}
		}

	}

	void Run(){	//run the game 
	
		while (!quit){	//while q button is not pressed
					
			Draw();		//draw the board
			Input();	//record input from player
			Logic();	//check logic each frame (not needed atm)
		}
	}
};


int main() {

	game_manager g(70, 20);
	g.Run();
	return 0;
}