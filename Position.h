#ifndef POSITION_H
#define POSITION_H

#include <Windows.h>

class Position
{
public:
	Position(); //default position class constructor
	Position(int x, int y); //constructor that sends parameters x and y of type into the setCursorPos fun
	void setCursorPos(int x, int y); //sets users cursor coord.X to x and cord.Y to y where each coordinate space is one char
	void moveCursor(int x, int y); // function that moves the cursor around
	void setX(int x); //set x invididually
	void setY(int y); //set y invididually
	int getX(); //returns the postion coordinate of x
	int getY(); //returns the postion coordinate of y S
private:
	COORD coord;
	int xBound, yBound;
};

#endif // !POSITION_H