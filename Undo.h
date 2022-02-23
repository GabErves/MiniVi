#ifndef UNDO_H
#define UNDO_H

#include <string>
#include "Position.h"

using namespace std;

class Undo {
public:
	void setChar(char C); //Sets the last deleted character 
	void setString(string S);  //Sets the last deleted line (string of characters)
	void setLastPos(Position LP);  //Sets the last position
	void setLastCMD(char LCMD); //Sets the last user command
	char getC(); //gets the last deleted character
	char getCMD(); //gets the last user command
	string getS(); //gets the last deleted line
	Position getPos(); //gets the last position
private:
	char deletedC;
	string deletedS;
	Position lastPos;
	char lastCMD;
};

#endif
#pragma once
