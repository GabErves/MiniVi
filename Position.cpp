#include <iostream>
#include "Position.h"

Position::Position() { //default constructor
	coord.X = 0;
	coord.Y = 0;
}

Position::Position(int x, int y) //constructor that sends parameters x and y of type int to setCursorPos fnc
{
	setCursorPos(x, y);
}

void Position::setCursorPos(int x, int y) //sets users cursor coord.X to x and cord.Y to y where each coordinate space is one char 

{
	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Position::moveCursor(int x, int y) // function that moves the cursor around
{
	coord.X += x; // increases the x coordinate by 1
	coord.Y += y; // increases the y coordinate by 1
}

void Position::setX(int x) //sets the x coordinate 
{
	coord.X = x;
}

void Position::setY(int y) //sets the y coordinate 
{
	coord.Y = y;
}

int Position::getX() //returns the x coordinate

{
	return coord.X;
}

int Position::getY() //returns the y coordinate

{ 
	return coord.Y;
}