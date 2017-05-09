# Tanks!

## Controls

The '@' on the left is player 1, the '@' on the right is player 2.
Use 'W' to increase the power of your shot. Use 'S' to decrease the power of your shot.
Use 'D' to increase the angle of your shot, and 'A' to decrease the angle of your shot.
Press 'Enter' to take your shot.
If you wish to move instead of shooting, double tap 'X' to move left, and 'C' to move right.

Every time someone hits a shot, the environment changes.
The first player to hit three shots wins. Wins are recorded for each player under their health counter.

## Code

Created using C++ and Curses.

The game is made up of a ground and player class.
The Player class includes the attributes of the tank, such as angle and power of shots and the position of the tank.
The Ground class includes the height of each piece of the ground, which can change slightly if hit by a shot.

Function overloads are used in the Vec2D class to decrease the amount of variables used in the main source file while doing math by allowing the use of points on the screen instead of two different x and y values.

The main source file includes the shoot and move functions and hit detection.
It also uses keyboard recoginition to allow the user inputs.


Completed by Devin Wermuth and Andrew Senkbeil.
