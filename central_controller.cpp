// Develop branch - test code
#include <iostream>
#include <Windows.h>	// For utilising the sleep function - Windows

using namespace std;

// ------Global variables------
// Ball movement vairables
int ball_position_x_now = 0;
int ball_position_y_now = 0;
int ball_position_x_previous = 0;
int ball_position_y_previous = 0;
// Ball user input variables
int ball_user_x = 0;
int ball_user_y = 0;

//  ------Global functions------
void ball_function(int x, int y) {
    // Showing the ball's previous position
    cout << "------Start of ball_function------" << endl;   //Debugging purposes only
    cout << "Position of the ball : Previous" << endl;      //Debugging purposes only
    cout << "   X = " << ball_position_x_previous << endl;  //Debugging purposes only
    cout << "   Y = " << ball_position_y_previous << endl;  //Debugging purposes only
    
    // The ball's current position
    ball_position_x_now = x;
    ball_position_y_now = y;
    // The ball's previous position
    ball_position_x_previous = ball_position_x_now;
    ball_position_y_previous = ball_position_y_now;

    // Showing the ball's current position
    cout << "Position of the ball : Now" << endl;      //Debugging purposes only
    cout << "   X = " << ball_position_x_now << endl;  //Debugging purposes only
    cout << "   Y = " << ball_position_y_now << endl;  //Debugging purposes only
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
        ball_function(ball_user_x, ball_user_y);
		Sleep(1000);   // Wait one second before the loop begins again                
    }

    return 0;
}