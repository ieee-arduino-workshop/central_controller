// TODO :  Feature - draw player dynamically when adding more players

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cmath>
#include <vector>
#include "controller_packet.h"
#include "direction.h"
#include "Player.h"

using namespace std;

/****************************************************************************************************
*****************************************************************************************************
** Name:        Game manager class
** Description: Game mechanics (E.g. size of field, player movement restrictions, ball movement restrictions, ball bounch mechanics)
*****************************************************************************************************
****************************************************************************************************/
class game_manager {
    private:
        int num_players, width, height, left_wall, top_wall, bottom_wall, right_wall, dribbling_left_wall, dribbling_top_wall, dribbling_bottom_wall, dribbling_right_wall;
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

            // Set wall parameters
            left_wall = 0;              dribbling_left_wall = 1;
            right_wall = width - 1;     dribbling_right_wall = width - 2;
            top_wall = 0;               dribbling_top_wall = 1;
            bottom_wall = height - 1;   dribbling_bottom_wall = height - 2;
            
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
            player[i]->reset();
            player[i]->setDribbling(false);
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
                else if (player_x[2] ==j && player_y[2] == i) {
                    cout << "\xFE";
                }
                else if (player_x[3] == j && player_y[3] == i) {
                    cout << "\xFE";
                }
                else if (player_x[4] ==j && player_y[4] == i) {
                    cout << "\xFE";
                }
                else if (player_x[5] == j && player_y[5] == i) {
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
            player_dribble[i] = player[i]->isDribbling();
        }

        int ball_x = b1->getX();
        int ball_y = b1->getY();

        // Get user input - Asynchronous ASCII key press check
        if (_kbhit()) {

            for (int i = 0; i < num_players; i++){

                //if dribble is on, the wall of the player 
                if(player_dribble[i]) {
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

                if (GetAsyncKeyState(65+(i*9))) { //A - Keypressed
                    if (player_x[i] > dribbling_left_wall){    //if player 
                        player[i]->moveLeft();
                    }
                    if (player_x[i] > left_wall){
                        player[i]->setDirection(LEFT);
                    }
                } else if(GetAsyncKeyState(68+(i*8))){ //D - Keypressed
                    if (player_x[i] < dribbling_right_wall){
                        player[i]->moveRight();
                    }
                    if (player_x[i] < right_wall){
                        player[i]->setDirection(RIGHT);
                    }
                } 
                
                if (GetAsyncKeyState(87-(i*14))){ //W - Key press
                    if (player_y[i] > dribbling_top_wall){
                        player[i]->moveUp();
                    }
                    if (player_y[i] > top_wall){
                        if(player[i]->getDirection() == LEFT ){
                            player[i]->setDirection(UPLEFT);
                        } else if (player[i]->getDirection() == RIGHT ){
                            player[i]->setDirection(UPRIGHT);
                        } else {
                            player[i]->setDirection(UP);
                        }
                    }
                } else if (GetAsyncKeyState(83-(i*8))){ //S - Keypress
                    if (player_y[i] < dribbling_bottom_wall){
                        player[i]->moveDown();
                    }
                    if (player_y[i] < bottom_wall){
                        if(player[i]->getDirection() == LEFT ){
                            player[i]->setDirection(DOWNLEFT);
                        } else if (player[i]->getDirection() == RIGHT ){
                            player[i]->setDirection(DOWNRIGHT);
                        } else {
                            player[i]->setDirection(DOWN);
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
                    b1->setDirection(player[i]->getDirection());
                }

                // kick - Key press
                if (GetAsyncKeyState(32-(i*19))) {
                    player[i]->setDribbling(false);
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
            player_dribble[i] = player[i]->isDribbling();
        }
        int ball_x = b1->getX();
        int ball_y = b1->getY();

        // Bottom wall hit. TODO: ADD REFLECTED BOUNCE FOR STRAIGHT DIRECTION
        if (ball_y == height - 1) {
            switch (b1->getDirection()) {
            case DOWN:
                b1->setDirection(UP);
                break;
            case DOWNRIGHT:
                b1->setDirection(UPRIGHT);
                break;
            case DOWNLEFT:
                b1->setDirection(UPLEFT);
                break;
            default:
                break;
            }
        }

        // Top wall hit
        if (ball_y == 0) {
            switch (b1->getDirection()) {
            case UP:
                b1->setDirection(DOWN);
                break;
            case UPRIGHT:
                b1->setDirection(DOWNRIGHT);
                break;
            case UPLEFT:
                b1->setDirection(DOWNLEFT);
                break;
            default:
                break;
            }
        }

        // Right wall hit
        if (ball_x == width - 1) {
            switch (b1->getDirection()) {
            case RIGHT:
                b1->setDirection(LEFT);
                break;
            case UPRIGHT:
                b1->setDirection(UPLEFT);
                break;
            case DOWNRIGHT:
                b1->setDirection(DOWNLEFT);
                break;
            default:
                break;
            }
        }

        // Left wall hit
        if (ball_x == 0) {
            switch (b1->getDirection()) {
            case LEFT:
                b1->setDirection(RIGHT);
                break;
            case UPLEFT:
                b1->setDirection(UPRIGHT);
                break;
            case DOWNLEFT:
                b1->setDirection(DOWNRIGHT);
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
            player_dribble[i] = player[i]->isDribbling();
        }
        ball_x = b1->getX();
        ball_y = b1->getY();
    
        // Calculate the distance between the ball and player
        for (int i = 0; i < num_players; i++){
            int distance_between_player_and_ball = sqrt(pow((ball_x - player_x[i]), 2) + pow((ball_y - player_y[i]), 2));
            // Catching the ball when it touches the player
            if (distance_between_player_and_ball == 1 || distance_between_player_and_ball == 0) {
                //set the new player dribbling to true
                player[i]->setDribbling(true);
            }
            else {
                //otherwise the player is not dribbling the ball
                player[i]->setDribbling(false);
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
    game_manager g(70, 20, 6);
    g.Run();
    return 0;
}