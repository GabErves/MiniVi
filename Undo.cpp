#include "Undo.h"

void Undo::setChar(char C) { //Sets the last deleted character
	deletedC = C;
}
void Undo::setString(string S) { //Sets the last deleted line (string of characters)
	deletedS = S;
}
void Undo::setLastPos(Position LP) { //Sets the last position
	lastPos = LP;
}
void Undo::setLastCMD(char LCMD) {//Sets the last user command
	lastCMD = LCMD;
}
char Undo::getC() { //gets the last deleted character
	return deletedC;
}
char Undo::getCMD() { //gets the last user command
	return lastCMD;
}
string Undo::getS() { //gets the last deleted line
	return deletedS;
}
Position Undo::getPos() { //gets the last position
	return lastPos;
}