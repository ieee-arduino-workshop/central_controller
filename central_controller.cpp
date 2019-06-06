// TO DO: Bug - After going to the edge of a boundary (whether it be the top, bottom, right or left)
//              and kicking the ball along the boundary such that the ball does not hit the boundary
//              which it is parallel to but will hit the boundaries that is it perpendicular to
//              the player cannot move towards the boundary after the player has kicked the ball
//              even when the player is not next to the boundary.
//              E.g. Move to the left boundary, line up such that the player is right next to the
//                   boundary as well as parallel to the boundary. Kick the ball along the boundary
//                   such that the ball travels parallel to the left boundary but bounces off the
//                   the top and bottom boundary. Move the player away from the boundary by pressing
//                   the "D" key (you can change the vertical position of the player by pressing "W"
//                   or "S" as well) and attempt to move towards the boundary which the ball is bouncing
//                   parallel to. Notice that you cannot move in the right direction by pressing "A".


#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

// Variable for the 8 directions
enum eDir {STOP = 0, LEFT, UPLEFT, DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT, UP, DOWN};

/****************************************************************************************************
*****************************************************************************************************
** Name:        Player Class
** Description: Player's properties (E.g. movement abilities)
*****************************************************************************************************
****************************************************************************************************/
class Player {
    private:
        //Position of player
        int x, y;

        // Reset co-ordinates
        int original_x, original_y;
    
    public:
        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Player constructor
        ** Description: Player class constructor and setting player location history variables
        *****************************************************************************************************
        ****************************************************************************************************/
        Player(int pos_x, int pos_y) {
            // Used to reset the player later
            original_x = pos_x;
            original_y = pos_y;
            
            // Set the current position of the player
            x = pos_x;
            y = pos_y;
        }

        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Position reset
        ** Description: Player's location on the field will be reset using the following function
        *****************************************************************************************************
        ****************************************************************************************************/
        void Reset() {
            x = original_x; y = original_y;
        }
        
        // Public - Get x and y function (use inline to replace those function definition wherever those are being called)
        inline int getX() { return x; }
        inline int getY() { return y; }
        inline void moveUp() { y--; }
        inline void moveDown() { y++; }
        inline void moveLeft() { x--; }
        inline void moveRight() { x++; }
};

/****************************************************************************************************
*****************************************************************************************************
** Name:        Ball Class
** Description: Ball's properties (E.g. movement properties)
*****************************************************************************************************
****************************************************************************************************/
class Ball {
    private:
        int x, y;
        int ori_x, ori_y;
        eDir direction;
    public:
        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Ball constructor
        ** Description: Ball class constructor and setting ball location history variables
        *****************************************************************************************************
        ****************************************************************************************************/
        Ball(int pos_x, int pos_y) {
            ori_x = pos_x;
            ori_y = pos_y;
            x = pos_x;
            y = pos_y;
            direction = STOP;
        }

        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Position reset
        ** Description: The ball's location on the field will be reset using the following function
        *****************************************************************************************************
        ****************************************************************************************************/
        void Reset() {
            x = ori_x; y = ori_y;
            direction = STOP;
        }
        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Direction change
        ** Description: The ball's location is changed using the following function
        *****************************************************************************************************
        ****************************************************************************************************/
        void changeDirection(eDir d) { //function to change direction of the ball
            direction = d;
        }
        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Random direction change
        ** Description: The ball's direction will be changed randomly
        *****************************************************************************************************
        ****************************************************************************************************/
        void randomDirection() {
            direction = (eDir)((rand() % 8) + 1); //random number from 1-8
        }
        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Ball direction change mechanics
        ** Description: The ball's direction change mechanics are handled by the following function
        *****************************************************************************************************
        ****************************************************************************************************/
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

        //Public - Get x and y functions (use inline to replace those function definition wherever those are being called)
        inline int getX() { return x; }
        inline int getY() { return y; }
        inline void setX(int newX) { x = newX; }
        inline void setY(int newY) { y = newY; }
        inline void moveUp() { y--; }
        inline void moveDown() { y++; }
        inline void moveLeft() { x--; }
        inline void moveRight() { x++; }

        //Public - Get current direction
        inline int getDirection() { return direction; }
};

/****************************************************************************************************
*****************************************************************************************************
** Name:        Game manager class
** Description: Game mechanics (E.g. size of field, player movement restrictions, ball movement restrictions, ball bounch mechanics)
*****************************************************************************************************
****************************************************************************************************/
class game_manager {
    private:
        int width, height;
        char up, down, left, right;
        bool quit, dribble;
        Player * p1;
        Ball * b1;
    public:
        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Game manager constructor
        ** Description: Game manager class constructor and setting initial variables for game mechanics
        *****************************************************************************************************
        ****************************************************************************************************/
        game_manager(int w, int h) {
            quit = false;
            dribble = true;
            up = 'w', down = 's', left = 'a', right = 'd';
            
            // Width 0 -> +X & Height 0 -> -Y
            width = w; height = h;

            // Set player in the middle
            p1 = new Player(w / 2, h / 2);
            b1 = new Ball(w / 2 + 1, h / 2);
    }

    /****************************************************************************************************
    *****************************************************************************************************
    ** Name:        Game manager destructor
    ** Description: Game manager destructor and deletes a player in the process
    *****************************************************************************************************
    ****************************************************************************************************/
    ~game_manager(){
        delete p1;
    }

    /****************************************************************************************************
    *****************************************************************************************************
    ** Name:        Position reset
    ** Description: The players's location on the field will be reset by calling the reset() function in the player class corresponding the player in question
    *****************************************************************************************************
    ****************************************************************************************************/
    void reset() {
        p1->Reset();
    }

    /****************************************************************************************************
    *****************************************************************************************************
    ** Name:        Game draw function (debugging)
    ** Description: The following function will draw the field, ball and player within the command line insterface for debugging purposes only
    *****************************************************************************************************
    ****************************************************************************************************/
    void Draw() {
        // Clear the terminal output
        system("cls");
        
        // Draw the top wall for the game
        for (int i = 0; i < width + 2; i++) {
            cout << "\xB2";
        }
        cout << endl;

        // Draw columns - Draw the 2 side wall and all the ojebcts inbetween
        for (int i = 0; i < height; i++){

            // Draw rows
            for (int j = 0; j < width; j++){
                // Get the location of all objects
                int player_x = p1->getX();
                int player_y = p1->getY();
                int ball_x = b1->getX();
                int ball_y = b1->getY();

                // Draw the wall part at the start of every row - Using HEX character codes
                if (j == 0) {
                    cout << "\xB2";
                }
                
                //Draw player location
                if (player_x == j && player_y == i) {
                    cout << "\xFE";
                }

                // Draw the ball
                else if (ball_x == j && ball_y == i) {
                    cout << "O";
                }

                // Draw empty sapace
                else { cout << " "; }

               // Draw the wall part at the end of every row
                if (j == width - 1) {
                    cout << "\xB2";
                }
            }
            cout << endl;
        }

        // Draw the bottom wall
        for (int i = 0; i < width + 2; i++) {
            cout << "\xB2";
        }
        cout << endl;
    }

    /****************************************************************************************************
    *****************************************************************************************************
    ** Name:        Player input function
    ** Description: The following function will listen to the player's inputs and process it accordingly, currently using keyboard inputs for debugging purposes only
    *****************************************************************************************************
    ****************************************************************************************************/
    void Input() {
        // Get location of all objects
        int player_x = p1->getX();
        int player_y = p1->getY();
        int ball_x = b1->getX();
        int ball_y = b1->getY();

        // Get user input - Asynchronous ASCII key press check
        if (_kbhit()) {

            // W - Key press
            if (GetAsyncKeyState(87)) {
                if ((player_y > 0) && (ball_y > 0)) {

                    // Move player
                    p1->moveUp();

                    // Dribble ball if dribble flag is set
                    if (dribble) {

                        // Set ball position near the player
                        b1->setY(p1->getY() - 1); b1->setX(p1->getX());
                        
                        // Change current direction of the ball
                        b1->changeDirection(UP);
                    }
                }
            }

            // S - Key press
            if (GetAsyncKeyState(83)) {
                if ((player_y < height - 1) && (ball_y < height - 1)) {
                    p1->moveDown();     
                    if (dribble) {
                        b1->setY(p1->getY() + 1); b1->setX(p1->getX());
                        b1->changeDirection(DOWN);
                    }
                }
            }

            // A - Key press
            if (GetAsyncKeyState(65)) {
                if ((player_x > 0) && (ball_x > 0)) {
                    p1->moveLeft();    
                    if (dribble) {
                        b1->setX(p1->getX() - 1); b1->setY(p1->getY());
                        b1->changeDirection(LEFT);
                    }
                }
            }

            // D = Key press
            if (GetAsyncKeyState(68)) {
                if ((player_x < width - 1) && (ball_x < width - 1)) {
                    p1->moveRight(); 
                    if (dribble) {
                        b1->setX(p1->getX() + 1); b1->setY(p1->getY());
                        b1->changeDirection(RIGHT);
                    }
                }
            }

            // If dribbling has been detected
            if (dribble) {

                // W&D - Key press
                if (GetAsyncKeyState(87) && GetAsyncKeyState(68)) {
                    if ((ball_y > 0) && (ball_x < width - 1)) {
                        b1->setY(p1->getY() - 1); b1->setX(p1->getX() + 1);
                        b1->changeDirection(UPRIGHT);
                    }
                }

                // W&A - Key press
                else if (GetAsyncKeyState(87) && GetAsyncKeyState(65)) {
                    if ((ball_y > 0) && (ball_x > 0)) {
                        b1->setY(p1->getY() - 1); b1->setX(p1->getX() - 1);
                        b1->changeDirection(UPLEFT);
                    }
                }

                // S&A - Key press
                else if (GetAsyncKeyState(83) && GetAsyncKeyState(65)) {
                    if ((ball_y < height - 1) && (ball_x > 0)) {
                        b1->setY(p1->getY() + 1); b1->setX(p1->getX() - 1);
                        b1->changeDirection(DOWNLEFT);
                    }
                }

                // S&D - Key press
                else if (GetAsyncKeyState(83) && GetAsyncKeyState(68)) {
                    if ((ball_y < height - 1) && (ball_x < width - 1)) {
                        b1->setY(p1->getY() + 1); b1->setX(p1->getX() + 1);
                        b1->changeDirection(DOWNRIGHT);
                    }
                }
            }

            // SPACE - Key press
            if (GetAsyncKeyState(VK_SPACE)) {
                dribble = false;
            }

            // R - Key press
            if (GetAsyncKeyState(82)) {
                p1->Reset();
                b1->Reset();
            }

            // Q - Key press - quit the game with q
            if (GetAsyncKeyState(81)) {
                quit = true;
            }
        }
    }

    /****************************************************************************************************
    *****************************************************************************************************
    ** Name:        Game logic function
    ** Description: The core game logic is found here (E.g. ball bounce, kicking, player position boundary check, ball position boundary check)
    *****************************************************************************************************
    ****************************************************************************************************/
    void Logic() {
        // If ball is not being dribble by player it moves freely
        if (!dribble) {
            b1->Move();
        }

        // Get location of all objects
        int player_x = p1->getX();
        int player_y = p1->getY();
        int ball_x = b1->getX();
        int ball_y = b1->getY();

        // Calculate the distance between the ball and player
        int distance_between_player_and_ball = sqrt(pow((ball_x - player_x), 2) + pow((ball_y - player_y), 2));

        // Catching the ball when it touches the player
        if (distance_between_player_and_ball == 1) {
            dribble = true;
        }

        // Bottom wall hit. TODO: ADD REFLECTED BOUNCE FOR STRAIGHT DIRECTION
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

        // Top wall hit
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

        // Right wall hit
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

        // Left wall hit
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

    /****************************************************************************************************
    *****************************************************************************************************
    ** Name:        Execute game manager
    ** Description: The following function will execute all functions within the game manager class and will run the game
    *****************************************************************************************************
    ****************************************************************************************************/
    void Run() {
            // While q (quit) button is not pressed
            while (!quit){
                // Draw the board
                Draw();

                // Record input from player
                Input();

                // Check logic each frame (not needed atm)
                Logic();
        }
    }
};

int main() {
    game_manager g(70, 20);
    g.Run();
    return 0;
}