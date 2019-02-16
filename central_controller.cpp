//  Develop branch - test code
#include <iostream>

using namespace std;

//  Global variables
int ball_position_x = 0;
int ball_position_y = 0;

//  Global functions
void ball_function() {
    cout << "Start of ball_function" << endl;       //Debugging purposes only
    cout << "Position of the ball" << endl;         //Debugging purposes only
    cout << "   X = " << ball_position_x << endl;   //Debugging purposes only
    cout << "   Y = " << ball_position_y << endl;   //Debugging purposes only
}

int main() {
    cout << "Hello world!" << endl;
    ball_function();
    return 0;
}