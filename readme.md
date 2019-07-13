Central controller
------------------

This is the project for the central controller. It receives data from the player controllers and updates the FPGA.

g++ -Wall -pedantic -D DEBUG=1 *.cpp -o central_controller