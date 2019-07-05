// TODO :  Feature - draw player dynamically when adding more players

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cmath>
#include <vector>

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

        //Whether or not a player is dribbling the ball
        bool dribble;

        // Reset co-ordinates
        int original_x, original_y;

        //Direction of the player
        eDir direction;
    public:
        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Player constructor
        ** Description: Player class constructor and setting player location history variables
        *****************************************************************************************************
        ****************************************************************************************************/
        Player(int pos_x, int pos_y) {
            // Used to reset the player later
            dribble = false;
            original_x = pos_x;
            original_y = pos_y;
            
            // Set the current position of the player
            x = pos_x;
            y = pos_y;
        }

        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Direction change
        ** Description: The player direction is changed using the following function
        *****************************************************************************************************
        ****************************************************************************************************/
        void changeDirection(eDir d) {
            direction = d;
        }

        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        setDribble
        ** Description: The allow the player to dribble or kick the ball
        *****************************************************************************************************
        ****************************************************************************************************/
        void setDribble(bool b) {
            dribble = b;
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
        inline void moveUpRight() { y--; x++;}
        inline void moveUpLeft() { y--; x--;}
        inline void moveDownRight() { y++; x++;}
        inline void moveDownLeft() { y++; x--;}
        inline void setX(int newX) { x = newX; }
        inline void setY(int newY) { y = newY; }
        //Public - Get current direction
        inline eDir getDirection() { return direction; }
        //Public - Get current player dribble flag
        inline bool getDribble() { return dribble; }
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
        int num_players, width, height, LWALL, UWALL, DWALL, RWALL, d_LWALL, d_UWALL, d_DWALL, d_RWALL;
        bool quit;
        vector<Player*>  player;
        Ball * b1;
    public:
        /****************************************************************************************************
        *****************************************************************************************************
        ** Name:        Game manager constructor
        ** Description: Game manager class constructor and setting initial variables for game mechanics
        *****************************************************************************************************
        ****************************************************************************************************/
        game_manager(int w, int h, int np) {
            quit = false;
            num_players = np;   //number of players

            // Width 0 -> +X & Height 0 -> -Y
            width = w; height = h;

            //set wall parameters
            LWALL = 0; d_LWALL = 1;
            RWALL = width - 1; d_RWALL = width - 2;
            UWALL = 0; d_UWALL = 1;
            DWALL = height - 1; d_DWALL = height - 2;
            
            // Set player in the middle
            for (int i = 0; i < num_players ; i++){
                if (i%2 == 0){  //if i is even (left side)
                    // Player p = Player(i);
                    player.push_back(new Player(width/4, height * (i+2)/(num_players+2)));
                }
                else{           //if i is odd (right side)
                    player.push_back(new Player(3*width/4, height * (i+1)/(num_players+2)));
                }
                
            }

            b1 = new Ball(w / 2, h / 2);

            
    }

    /****************************************************************************************************
    *****************************************************************************************************
    ** Name:        Game manager destructor
    ** Description: Game manager destructor and deletes a player in the process
    *****************************************************************************************************
    ****************************************************************************************************/
    ~game_manager(){
        for (auto i : player){
            delete i;
        }
        player.clear();
        delete b1;
    }

    /****************************************************************************************************
    *****************************************************************************************************
    ** Name:        Position reset
    ** Description: The players's location on the field will be reset by calling the reset() function in the player class corresponding the player in question
    *****************************************************************************************************
    ****************************************************************************************************/
    void reset() {
        for (int i = 0; i < num_players; i++){
            player[i]->Reset();
            player[i]->setDribble(false);
        }
        b1->Reset();
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
        
        //Display current player and ball position
        cout << "Ball X : " << b1->getX() << " Ball Y : " << b1->getY() << endl;
        for (int i = 0; i < num_players; i++){
            cout << "Player_" << i+1 << " X : " << player[i]->getX() << " Player_" << i+1 << " Y : " << player[i]->getY() << endl;
        }
        
        //Draw the top wall for the game
        for (int i = 0; i < width + 2; i++) {
            cout << "\xB2";
        }
		cout << endl;

        // Draw columns - Draw the 2 side wall and all the ojebcts inbetween
        for (int i = 0; i < height; i++){

            // Draw rows
            for (int j = 0; j < width; j++){
                // Get the location of all objects
                int player_x[num_players];
                int player_y[num_players];
                for (int i = 0; i < num_players; i++){
                    player_x[i] = player[i]->getX();
                    player_y[i] = player[i]->getY();
                }
                int ball_x = b1->getX();
                int ball_y = b1->getY();

                // Draw the wall part at the start of every row - Using HEX character codes
                if (j == 0) {
                    cout << "\xB2";
                }
                
                //Draw player location
                if (player_x[0] == j && player_y[0] == i) {
                    cout << "\xFE";
                }
                else if (player_x[1] == j && player_y[1] == i) {
                    cout << "\xFE";
                }
                // Draw the ball
                else if (ball_x == j && ball_y == i) {
                    cout << "O";
                }
                // Draw empty space
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
        int player_x[num_players];
        int player_y[num_players];
        int player_dribble[num_players];
        for (int i = 0; i < num_players; i++){
            player_x[i] = player[i]->getX();
            player_y[i] = player[i]->getY();
            player_dribble[i] = player[i]->getDribble();
        }
        int ball_x = b1->getX();
        int ball_y = b1->getY();

        

        // Get user input - Asynchronous ASCII key press check
        if (_kbhit()) {
            

            for (int i = 0; i < num_players; i++){

                //if dribble is on, the wall of the player 
                if(player_dribble[i]) {
                    d_LWALL = 1;
                    d_UWALL = 1;
                    d_RWALL = width - 2;
                    d_DWALL = height - 2;
                }
                else{
                    d_LWALL = LWALL;
                    d_UWALL = UWALL;
                    d_RWALL = RWALL;
                    d_DWALL = DWALL;
                }

                if (GetAsyncKeyState(65+(i*9))) { //A - Keypressed
                    if (player_x[i] > d_LWALL){    //if player 
                        player[i]->moveLeft();
                    }
                    if (player_x[i] > LWALL){
                        player[i]->changeDirection(LEFT);
                    }
                } else if(GetAsyncKeyState(68+(i*8))){ //D - Keypressed
                    if (player_x[i] < d_RWALL){
                        player[i]->moveRight();
                    }
                    if (player_x[i] < RWALL){
                        player[i]->changeDirection(RIGHT);
                    }
                } 
                
                if (GetAsyncKeyState(87-(i*14))){ //W - Key press
                    if (player_y[i] > d_UWALL){
                        player[i]->moveUp();
                    }
                    if (player_y[i] > UWALL){
                        if(player[i]->getDirection() == LEFT ){
                            player[i]->changeDirection(UPLEFT);
                        } else if (player[i]->getDirection() == RIGHT ){
                            player[i]->changeDirection(UPRIGHT);
                        } else {
                            player[i]->changeDirection(UP);
                        }
                    }
                } else if (GetAsyncKeyState(83-(i*8))){ //S - Keypress
                    if (player_y[i] < d_DWALL){
                        player[i]->moveDown();
                    }
                    if (player_y[i] < DWALL){
                        if(player[i]->getDirection() == LEFT ){
                            player[i]->changeDirection(DOWNLEFT);
                        } else if (player[i]->getDirection() == RIGHT ){
                            player[i]->changeDirection(DOWNRIGHT);
                        } else {
                            player[i]->changeDirection(DOWN);
                        }
                    }
                }

                player_x[i] = player[i]->getX();
                player_y[i] = player[i]->getY();
                if(player_dribble[i]){
                    switch(player[i]->getDirection()){
                        case LEFT:
                            b1->setX(player_x[i] - 1);
                            b1->setY(player_y[i]);
                            break;
                        case UP:
                            b1->setX(player_x[i]);
                            b1->setY(player_y[i] - 1);
                            break;
                        case RIGHT:
                            b1->setX(player_x[i] + 1);
                            b1->setY(player_y[i]);
                            break;
                        case DOWN:
                            b1->setX(player_x[i]);
                            b1->setY(player_y[i] + 1);
                            break;
                        case UPLEFT:
                            b1->setX(player_x[i] - 1);
                            b1->setY(player_y[i] - 1);
                            break;
                        case UPRIGHT:
                            b1->setX(player_x[i] + 1);
                            b1->setY(player_y[i] - 1);
                            break;
                        case DOWNRIGHT:
                            b1->setX(player_x[i] + 1);
                            b1->setY(player_y[i] + 1);
                            break;
                        case DOWNLEFT:
                            b1->setX(player_x[i] - 1);
                            b1->setY(player_y[i] + 1);
                            break;
                    }
                    b1->changeDirection(player[i]->getDirection());
                }

                // kick - Key press
                if (GetAsyncKeyState(32-(i*19))) {
                    player[i]->setDribble(false);
                }
            }

            // R - Key press
            if (GetAsyncKeyState(82)) {
                reset();
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

       // Get location of all objects
        int player_x[num_players];
        int player_y[num_players];
        int player_dribble[num_players];
        for (int i = 0; i < num_players; i++){
            player_x[i] = player[i]->getX();
            player_y[i] = player[i]->getY();
            player_dribble[i] = player[i]->getDribble();
        }
        int ball_x = b1->getX();
        int ball_y = b1->getY();

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
            b1->Move();
        }

        // Get location of all objects
        for (int i = 0; i < num_players; i++){
            player_x[i] = player[i]->getX();
            player_y[i] = player[i]->getY();
            player_dribble[i] = player[i]->getDribble();
        }
        ball_x = b1->getX();
        ball_y = b1->getY();
    
        // Calculate the distance between the ball and player
        for (int i = 0; i < num_players; i++){
            int distance_between_player_and_ball = sqrt(pow((ball_x - player_x[i]), 2) + pow((ball_y - player_y[i]), 2));
            // Catching the ball when it touches the player
            if (distance_between_player_and_ball == 1 || distance_between_player_and_ball == 0) {
                //set the new player dribbling to true
                player[i]->setDribble(true);
            }
            else {
                //otherwise the player is not dribbling the ball
                player[i]->setDribble(false);
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
    game_manager g(70, 20, 2);
    g.Run();
    return 0;
}