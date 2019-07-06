#include "GameManager.h"

/**
 * Constructor.
 */
GameManager::GameManager(int w, int h, int np) {
    quit = false;
    num_players = np;   //number of players


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
    
    // load players
    for (int i = 0; i < num_players ; i++) {
        // even players on the left side
        if (i % 2 == 0) {
            players[i] = new Player(L_TEAM_X, L_TEAM_Y(i));
        }

        // odd players on the right side
        else {
            players[i] = new Player(R_TEAM_X, R_TEAM_Y(i));
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

#ifdef DEBUG    // debugging methods only
/**
 * Draw the field, ball, and players to STDOUT.
 */
void GameManager::draw() {
    // Clear the terminal output
    system("cls");
    
    //Display current player and ball position
    cout << "Ball X : " << ball->getX() << " Ball Y : " << ball->getY() << endl;
    for (int i = 0; i < num_players; i++){
        cout << "Player_" << i+1 << " X : " << players[i]->getX() << " Player_" << i+1 << " Y : " << players[i]->getY() << endl;
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
                player_x[i] = players[i]->getX();
                player_y[i] = players[i]->getY();
            }
            int ball_x = ball->getX();
            int ball_y = ball->getY();

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

/**
 * Listen for the player's inputs. Debugging purposes only.
 */
void GameManager::input() {
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
                    players[i]->moveLeft();
                }
                if (player_x[i] > left_wall){
                    players[i]->setDirection(LEFT);
                }
            } else if(GetAsyncKeyState(68+(i*8))){ //D - Keypressed
                if (player_x[i] < dribbling_right_wall){
                    players[i]->moveRight();
                }
                if (player_x[i] < right_wall){
                    players[i]->setDirection(RIGHT);
                }
            } 
            
            if (GetAsyncKeyState(87-(i*14))){ //W - Key press
                if (player_y[i] > dribbling_top_wall){
                    players[i]->moveUp();
                }
                if (player_y[i] > top_wall){
                    if(players[i]->getDirection() == LEFT ){
                        players[i]->setDirection(UPLEFT);
                    } else if (players[i]->getDirection() == RIGHT ){
                        players[i]->setDirection(UPRIGHT);
                    } else {
                        players[i]->setDirection(UP);
                    }
                }
            } else if (GetAsyncKeyState(83-(i*8))){ //S - Keypress
                if (player_y[i] < dribbling_bottom_wall){
                    players[i]->moveDown();
                }
                if (player_y[i] < bottom_wall){
                    if(players[i]->getDirection() == LEFT ){
                        players[i]->setDirection(DOWNLEFT);
                    } else if (players[i]->getDirection() == RIGHT ){
                        players[i]->setDirection(DOWNRIGHT);
                    } else {
                        players[i]->setDirection(DOWN);
                    }
                }
            }

            player_x[i] = players[i]->getX();
            player_y[i] = players[i]->getY();
            if(player_dribble[i]){
                switch(players[i]->getDirection()){
                    case LEFT:
                        ball->setX(player_x[i] - 1);
                        ball->setY(player_y[i]);
                        break;
                    case UP:
                        ball->setX(player_x[i]);
                        ball->setY(player_y[i] - 1);
                        break;
                    case RIGHT:
                        ball->setX(player_x[i] + 1);
                        ball->setY(player_y[i]);
                        break;
                    case DOWN:
                        ball->setX(player_x[i]);
                        ball->setY(player_y[i] + 1);
                        break;
                    case UPLEFT:
                        ball->setX(player_x[i] - 1);
                        ball->setY(player_y[i] - 1);
                        break;
                    case UPRIGHT:
                        ball->setX(player_x[i] + 1);
                        ball->setY(player_y[i] - 1);
                        break;
                    case DOWNRIGHT:
                        ball->setX(player_x[i] + 1);
                        ball->setY(player_y[i] + 1);
                        break;
                    case DOWNLEFT:
                        ball->setX(player_x[i] - 1);
                        ball->setY(player_y[i] + 1);
                        break;
                }
                ball->setDirection(players[i]->getDirection());
            }

            // kick - Key press
            if (GetAsyncKeyState(32-(i*19))) {
                players[i]->setDribbling(false);
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
#endif // end debug flag

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
    if (ball_x == width - 1) {
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

    // Left wall hit
    if (ball_x == 0) {
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

    // Calculate the distance between the ball and player
    for (int i = 0; i < num_players; i++){
        int distance_between_player_and_ball = sqrt(pow((ball_x - player_x[i]), 2) + pow((ball_y - player_y[i]), 2));
        // Catching the ball when it touches the player
        if (distance_between_player_and_ball == 1 || distance_between_player_and_ball == 0) {
            //set the new player dribbling to true
            players[i]->setDribbling(true);
        }
        else {
            //otherwise the player is not dribbling the ball
            players[i]->setDribbling(false);
        }
    }
}

/**
 * Draw the game and monitor input if in debugging mode. Run game logic regardless.
 */
void GameManager::run() {
    // While q (quit) button is not pressed
    while (!quit) {
    #ifdef DEBUG
        // Draw the board
        draw();

        // Record input from player
        input();
    #endif

        // Check logic each frame (not needed atm)
        logic();
    }
}