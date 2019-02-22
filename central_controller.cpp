#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum eDir {STOP = 0, LEFT, RIGHT, UP, DOWN};	//TODO: start with basic and later maybe add 8 direction

class Player {
private:
	int x, y;	//position of player
	int originalX, originalY;	//reset coordinates
	eDir direction;
public:
	Player(int posX, int posY) //constructor that take x and y coordinate
	{
		originalX = posX; //used to reset the player later
		originalY = posY;
		x = posX; //set the current position of the player
		y = posY;
		direction = STOP;
	}
	void Reset() //reset function
	{
		x = originalX; y = originalY;
		direction = STOP;
	}
	void changeDirection(eDir d) //function to change direction of the player
	{
		direction = d;
	}
	inline int getX() { return x; } //public get x and y function (use inline to replace those function definition wherever those are being called)
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	inline void moveLeft() { x--; }
	inline void moveRight() { x++; }
	inline int getDirection() { return direction; } //public get current direction
};

class Ball {
private:
	int x, y;
	int oriX, oriY;
public:
	Ball(int posX, int posY) {
		oriX = posX;
		oriY = posY;
		x = posX;
		y = posY;
	}
	void Reset() {
		x = oriX; y = oriY;
	}
	inline int getX() { return x; } //public get x and y function (use inline to replace those function definition wherever those are being called)
	inline int getY() { return y; }
	inline void setX(int newX) { x = newX; }
	inline void setY(int newY) { y = newY; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	inline void moveLeft() { x--; }
	inline void moveRight() { x++; }
};

class game_manager {
private:
	int width, height;
	char up, down, left, right;
	bool quit;
	Player * p1;
	Ball * b1;
public:
	game_manager(int w, int h) {	//constructor
		quit = false;
		up = 'w', down = 's', left = 'a', right = 'd';
		width = w; height = h;
		p1 = new Player(w / 2, h / 2);	//set player in the middle
		b1 = new Ball(w / 2 + 1, h / 2);
	}

	~game_manager()
	{
		delete p1;
	}

	void reset() {
		p1->Reset();
	}

	void Draw() {	//for debug purposes

		system("cls");
		for (int i = 0; i < width + 2; i++)	//draw the top wall for the game
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++)	//2 side wall and all the ojects inbetween. COLUMN
		{
			for (int j = 0; j < width; j++)	// ROW
			{
				int playerx = p1->getX();
				int playery = p1->getY();	//Get location of all objects (player)
				int ballx = b1->getX();
				int bally = b1->getY();		//Get local of ball

				if (j == 0)	//draw the wall part at the start of every row
					cout << "\xB2";	//hex character code

				//Draw player location
				if (playerx == j && playery == i)
					cout << "\xFE"; //player
				else if (ballx == j && bally == i)
					cout << "O"; //ball
				
				else
					cout << " ";

				if (j == width - 1)	//draw the wall part at the end of every row
					cout << "\xB2";
			}
			cout << endl;
		}
		for (int i = 0; i < width + 2; i++)	//draw the bottom wall
			cout << "\xB2";
		cout << endl;
		
	}

	void Input() {
		int playerx = p1->getX();
		int playery = p1->getY();	//Get location of all objects
		int ballx = b1->getX();
		int bally = b1->getY();

		if (_kbhit())	//get user input
		{
			if (GetAsyncKeyState(87)) {	//ascii W checking asynchorously for Key state
				if ((playery > 0) && (bally > 0)) {
					p1->moveUp(); b1->setY(p1->getY() - 1); b1->setX(p1->getX());	//move player and ball
				}
			}
			if (GetAsyncKeyState(83)) {	//	S
				if ((playery < height - 1) && (bally < height - 1)) {
					p1->moveDown();	b1->setY(p1->getY() + 1); b1->setX(p1->getX());
				}
			}
			if (GetAsyncKeyState(65)) {	//	A
				if ((playerx > 0) && (ballx > 0)) {
					p1->moveLeft();	b1->setX(p1->getX() - 1); b1->setY(p1->getY());
				}
			}
			if (GetAsyncKeyState(68)) {	//	D
				if ((playerx < width - 1) && (ballx < width - 1)) {
					p1->moveRight(); b1->setX(p1->getX() + 1); b1->setY(p1->getY());
				}
			}
			if (GetAsyncKeyState(87) && GetAsyncKeyState(68)) {	//W&D	sticky ball
				if ((bally > 0) && (ballx < width - 1)) {
					b1->setY(p1->getY() - 1); b1->setX(p1->getX() + 1);
				}
			}
			else if (GetAsyncKeyState(87) && GetAsyncKeyState(65)) {	//W&A
				if ((bally > 0) && (ballx > 0)) {
					b1->setY(p1->getY() - 1); b1->setX(p1->getX() - 1);
				}
			}
			else if (GetAsyncKeyState(83) && GetAsyncKeyState(65)) {	//S&A
				if ((bally < height - 1) && (ballx > 0)) {
					b1->setY(p1->getY() + 1); b1->setX(p1->getX() - 1);
				}
			}
			else if (GetAsyncKeyState(83) && GetAsyncKeyState(68)) {	//S&D
				if ((bally < height - 1) && (ballx < width - 1)) {
					b1->setY(p1->getY() + 1); b1->setX(p1->getX() + 1);
				}
			}
			if (GetAsyncKeyState(82)) {	// R
				p1->Reset();
				b1->Reset();
			}
			if (GetAsyncKeyState(81))	//ascii Q quit the game with q
				quit = true;
			
		}
	}

	void Logic() {
		int playerx = p1->getX();
		int playery = p1->getY();	//Get location of all objects
		// nothing need to interact yet
	}

	void Run()	//run the game 
	{
		while (!quit)	//while q button is not pressed
		{
			Draw();		//draw the board
			Input();	//record input from player
			//Logic();	//check logic each frame (not needed atm)
		}
	}
};


int main() {

	game_manager g(70, 20);
	g.Run();
	return 0;
}