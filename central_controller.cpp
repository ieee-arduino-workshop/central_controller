//player test code - Hai
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
	void move_player() {
		switch (direction) {
		case STOP:
			break;
		case LEFT:
			x--;
		case RIGHT:
			x++;
		case UP:
			y--;
		case DOWN:
			y++;
		default:
			break;
		}
	}
	inline int getX() { return x; } //public get x and y function (use inline to replace those function definition wherever those are being called)
	inline int getY() { return y; }
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
	bool quit;
	Player * p1;
public:
	game_manager(int w, int h) {	//constructor
		quit = false;
		up = 'w', down = 's', left = 'a', right = 'd';
		width = w; height = h;
		p1 = new Player(w / 2, h / 2);	//set player in the middle
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
				int playery = p1->getY();	//Get location of all objects

				if (j == 0)	//draw the wall part at the start of every row
					cout << "\xB2";	//hex character code

				//Draw player location
				if (playerx == j && playery == i)
					cout << "O"; //player

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
		p1->move_player();

		int playerx = p1->getX();
		int playery = p1->getY();	//Get location of all objects

		if (_kbhit())	//get user input
		{
			if (GetAsyncKeyState(87))	//ascii W checking asynchorously for Key state
				if (playery > 0)
					p1->moveUp();
			if (GetAsyncKeyState(83))	//	S
				if (playery < height -1)
					p1->moveDown();
			if (GetAsyncKeyState(65))	//	A
				if (playerx > 0)
					p1->moveLeft();
			if (GetAsyncKeyState(68))	//	D
				if (playery < width - 1)
					p1->moveRight();
			if (GetAsyncKeyState(82))	// R
				p1->Reset();
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

	game_manager g(40, 20);
	g.Run();
	return 0;
}