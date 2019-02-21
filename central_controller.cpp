// Develop branch - test code
#include <iostream>
#include <Windows.h>	// For utilising the sleep function - Windows

using namespace std;

// ------Global variables------
// Ball position vairables
int ball_position_x_now = 0;
int ball_position_y_now = 0;
int ball_position_x_previous = 0;
int ball_position_y_previous = 0;
// Ball movement variables
int ball_vector_x = 0;
int ball_vector_y = 0;
// Ball user input variables
int ball_user_x = 0;
int ball_user_y = 0;
// Soccer field dimension variables - These values will change in the future
int pitch_x_min = 0;
int pitch_y_min = 0;
int pitch_x_max = 1500;
int pitch_y_max = 1000;

//  ------Global functions------
void ball_physics(int state, int x, int y) {
    // Showing the ball's previous position
    cout << "------Start of ball_function------" << endl;   //Debugging purposes only
    cout << "Position of the ball : Previous" << endl;      //Debugging purposes only
    cout << "   X = " << ball_position_x_previous << endl;  //Debugging purposes only
    cout << "   Y = " << ball_position_y_previous << endl;  //Debugging purposes only

    // Executing the requested ball bounce algorithm
    switch (state) {                                    // State == 0 ball bouncing OFF, State == 1 ball bouncing ON, State == 2 ball rests to the middle
        case 0:
            // Checking if the ball is at the boundaries of the pitch
            if (x >= pitch_x_max) {                     // Checking if the ball has gone beyond the x-axis boundaries
                ball_position_x_now = pitch_x_max;
            } if (x <= pitch_x_min) {                   // Checking if the ball has gone beyond the x-axis boundaries
                ball_position_x_now = pitch_x_min;
            } if (y >= pitch_y_max) {                   // Checking if the ball has gone beyond the y-axis boundaries
                ball_position_y_now = pitch_y_max;
            } if (y <= pitch_y_min) {                   // Checking if the ball has gone beyond the y-axis boundaries
                ball_position_y_now = pitch_y_min;
            } if (x < pitch_x_max && x > pitch_x_min) { // If the ball doesn't exceed the x-axis boundaries of the pitch
                ball_position_x_now = x;
            } if (y < pitch_y_max && y > pitch_y_min) { // If the ball doesn't exceed the y-axis boundaries of the pitch
                ball_position_y_now = y;
            }
            // Calculating the movement vector of the ball
            ball_vector_x = ball_position_x_now - ball_position_x_previous;
            ball_vector_y = ball_position_y_now - ball_position_y_previous;
            break;
        case 1:
            // Checking if the ball is at the boundaries of the pitch
            if (x >= pitch_x_max) {                     // Checking if the ball has gone beyond the x-axis boundaries
                // Calculating the movement vector of the ball
                ball_vector_x = x - ball_position_x_previous;
                ball_vector_x = -(ball_vector_x);
                ball_position_x_now = ball_vector_x + x;
            } if (x <= pitch_x_min) {                   // Checking if the ball has gone beyond the x-axis boundaries
                // Calculating the movement vector of the ball
                ball_vector_x = x - ball_position_x_previous;
                ball_vector_x = -(ball_vector_x);
                ball_position_x_now = ball_vector_x + x;
            } if (y >= pitch_y_max) {                   // Checking if the ball has gone beyond the y-axis boundaries
                // Calculating the movement vector of the ball
                ball_vector_y = y - ball_position_y_previous;
                ball_vector_y = -(ball_vector_y);
                ball_position_y_now = ball_vector_y + y;
            } if (y <= pitch_y_min) {                   // Checking if the ball has gone beyond the y-axis boundaries
                // Calculating the movement vector of the ball
                ball_vector_y = y - ball_position_y_previous;
                ball_vector_y = -(ball_vector_y);
                ball_position_y_now = ball_vector_y + y;
            } if (x < pitch_x_max && x > pitch_x_min) { // If the ball doesn't exceed the x-axis boundaries of the pitch
                ball_position_x_now = x;
                // Calculating the movement vector of the ball
                ball_vector_x = ball_position_x_now - ball_position_x_previous;
            } if (y < pitch_y_max && y > pitch_y_min) { // If the ball doesn't exceed the y-axis boundaries of the pitch
                ball_position_y_now = y;
                // Calculating the movement vector of the ball
                ball_vector_y = ball_position_y_now - ball_position_y_previous;
            }
            break;
        case 2:
            // Checking if the ball is at the boundaries of the pitch
            if (x >= pitch_x_max) {                     // Checking if the ball has gone beyond the x-axis boundaries
                ball_position_x_now = pitch_x_max/2;
                ball_vector_x = 0;
            } if (x <= pitch_x_min) {                   // Checking if the ball has gone beyond the x-axis boundaries
                ball_position_x_now = pitch_x_max/2;
                ball_vector_x = 0;
            } if (y >= pitch_y_max) {                   // Checking if the ball has gone beyond the y-axis boundaries
                ball_position_y_now = pitch_y_max/2;
                ball_vector_y = 0;
            } if (y <= pitch_y_min) {                   // Checking if the ball has gone beyond the y-axis boundaries
                ball_position_y_now = pitch_y_max/2;
                ball_vector_y = 0;
            } if (x < pitch_x_max && x > pitch_x_min) { // If the ball doesn't exceed the x-axis boundaries of the pitch
                ball_position_x_now = x;
                // Calculating the movement vector of the ball
                ball_vector_x = ball_position_x_now - ball_position_x_previous;
            } if (y < pitch_y_max && y > pitch_y_min) { // If the ball doesn't exceed the y-axis boundaries of the pitch
                ball_position_y_now = y;
                // Calculating the movement vector of the ball
                ball_vector_y = ball_position_y_now - ball_position_y_previous;
            }
    }
    
    // The ball's previous position
    ball_position_x_previous = ball_position_x_now;
    ball_position_y_previous = ball_position_y_now;

    // Showing the ball's current position
    cout << "Position of the ball : Now" << endl;      //Debugging purposes only
    cout << "   X = " << ball_position_x_now << endl;  //Debugging purposes only
    cout << "   Y = " << ball_position_y_now << endl;  //Debugging purposes only
    // Showing the ball's current movement vector
    cout << "Movement vector of the ball:" << endl;     //Debugging purposes only
    cout << "   Delta X = " << ball_vector_x << endl;   //Debugging purposes only
    cout << "   Delta Y = " << ball_vector_y << endl;   //Debugging purposes only
}

int main() {
    cout << "Hello world!" << endl;
    
    // Loop placed here for testing purposes only
    while(1) {
        // Get the user input for the new X and Y locations of the ball
        cout << "Please enter the new X position of the ball : ";
        cin >>  ball_user_x;
        cout << "Please enter the new Y position of the ball : ";
        cin >>  ball_user_y;

        // Update the location of the ball
        ball_physics(2 ,ball_user_x, ball_user_y);
		Sleep(1000);   // Wait one second before the loop begins again                
    }

    return 0;
}