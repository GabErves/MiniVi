#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <string>
#include <list>
#include "Node.h"
#include "LinkedList.h"
#include "ListInterface.h"
#include "Position.h"
#include "LinkedStack.h"
#include "StackInterface.h"
#include "Undo.h"
#include "BinarySearchTree.h"

using namespace std;

class Editor
{
public:
	Editor(); // default editor construtor
	Editor(string fileName);  // editor construtor that passes the file through
	void run(); // function that runs the editor program and runs the case switch
	void ReadKeywords(); // function that reads the keywords from the keyword file
	void Move(string direction); // function that moves the cursor around
	void DisplayLines(); // function that displays the keywords and sorts them using a binary search
	void CurrentLine();  // function that gets the current line in the text file
	void WriteChar(char cmd);  // function that allows the user to type in a new char, passes in a parameter that 
	void DeleteChar(); // function that allows the user to delete a char
	void WriteUndo(char C, string S); // function that prints out the old undid text
	void undo(); // fucntion that undos the last changes 
	void Save(); // function that saves the user progress
	bool Quit(); // function that quits the program
private:
	//Chars
	char command;  // command variable that is the variable used in the switch statement
	//Strings
	string fileName, tempText; // filename variable
	BinarySearchTree<string>bstKeywords;
	//string keywords[61]; // keywords array
	//Bools
	bool isRunning = true;  // bool that checks if the code is running
	bool changes = false;  // bool that checks if changes are happening true or false
	//Custom Classes
	string writing;
	Undo lastAction; // class object that checks the last stores the last action
	LinkedStack<Undo> undos; // linked stack templated definition for the undo variable
	LinkedList<string> allText;  //linked list templated definition for the allText variable
	Position pos; //position variable from the position class
	//Files
	fstream myFile; // variable for the file
};

#endif // !EDITOR_H

