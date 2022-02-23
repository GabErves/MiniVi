#include <iostream>
#include <conio.h>
#include <fstream>
#include <Windows.h>
#include "Editor.h"
#include "Position.h"
#include "quicksort.cpp"

using namespace std;

//Initialize cursor 
void CursorInit(Position coordinate) { // function that gets the cursor placement and connects it to each coordinate


	HANDLE hStdout;
	COORD coord;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	coord.X = coordinate.getX(); // gets the x coordinate of the cursor


	coord.Y = coordinate.getY(); // gets the y coordinate of the cursor


	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Change color of text
void colorText(string value) {

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	if (value == "white")
		SetConsoleTextAttribute(hConsole, 7);
	if (value == "blue")
		SetConsoleTextAttribute(hConsole, 9);

}

//Search array where the sorted array is repeatedly divided in half
int binarySearch(const string anArray[], int first, int last, string target)
{
	int index;
	if (first > last)
		index = -1; // target not in original array
	else
	{
		// If target is in anArray, anArray[first] <= target <= anArray[last]
		int mid = first + (last - first) / 2;
		if (target == anArray[mid])
			index = mid; // target found at anArray[mid]
		else if (target < anArray[mid])
			// Point X
			index = binarySearch(anArray, first, mid - 1, target);
		else
			// Point Y
			index = binarySearch(anArray, mid + 1, last, target);
	}  // end if

	return index;
}

//Defualt Constructor
Editor::Editor()
{
	ReadKeywords();
}

//Constructor with given file
Editor::Editor(string file) 
{
	ReadKeywords(); //calls the keywords function to read it in 

	fileName = file; // sets filename to the file parameter
	myFile.open(fileName);// defines variable for each line in the text file
	//opens up the file called filename

	if (!myFile.is_open()) {
		cout << "The file is not opened." << endl; 
	}
	int counter = 1;

	while (!myFile.eof())
	{
		getline(myFile, tempText);
		cout << tempText;
		allText.insert(counter, tempText);
		counter++;
	}

	myFile.close();
}

//Read keywords from file into array and sort array
void Editor::ReadKeywords()
{
	fstream file;
	file.open("keywords.txt");

	int counter = 0;
	while (!file.eof())  // gets the text file and each line in the file
	{
		file >> tempText; // gets the line string from the text file
		bstKeywords.add(tempText);
		counter++;
	}

	 
}

//Display the lines from allText LinkedList
void Editor::DisplayLines() 
{
	int position;
	string nextLine, nextWord, line;

	for (position = 1; position <= allText.getLength(); position++) // gets all of the data from the text file
	{
		nextLine = allText.getEntry(position);

		int i = 0;
		while (i < nextLine.length())
		{
			string word;
			if (isalpha(nextLine[i])) {
				while (isalpha(nextLine[i]) || nextLine[i] == '_') {
					word += nextLine[i];
					i++;
				}
				if (bstKeywords.contains(word))  //found
				{
					colorText("blue");
				}
				else
				{
					colorText("white");
				}
				cout << word;
			}
			else {
				colorText("white");
				cout << nextLine[i];
				i++;
			}
		}
		cout << endl;
	}

	CursorInit(pos);
}

//Run loop, fetch in commands from input
void Editor::run()
{
	system("cls");
	DisplayLines();
	command = _getch(); //gets each char input 

	switch (command) // case switch statement for each char user input 
	{
	case 'x':
		DeleteChar();  // user enters backspace, which deletes the leftmost character 
		run();// keeps the case from breaking
		break;
	case 'q': // quit case
		command = _getch(); //gets each char input 
		switch (command)
		{
		case '!': // if user does q!, it will quit without saving 
			pos.setCursorPos(0, allText.getLength()); // sets cursor at the orignal spot
			exit;
			break;
		default:
			if (Quit()) { break; } 
			else { run(); break; }
			run();
			break;
		}
		break;
	case 'w': // save case
		Save();  // user enters w to save the proress. save function will save the contents of the file
		run();
		break;
	case 'j': // Move down
		Move("DOWN"); // moves using the j key
		run();
		break;
	case 80: // Arrow down
		Move("DOWN"); // moves using the ACSII down arrow
		run();
		break;
	case 'k': // Move up
		Move("UP"); // moves using the k key
		run();
		break;
	case 72:  // Arrow up
		Move("UP"); // moves using tha ACSII up arrow
		run();
		break;
	case 'h': // Move left
		Move("LEFT"); // moves using the h key
		run();
		break;
	case 75: // Arrow left
		Move("LEFT"); // moves using tha ACSII left arrow
		run();
		break;
	case 'l': // Move right
		Move("RIGHT");// moves using the l key
		run();
		break;
	case 77: // Arrow right
		Move("RIGHT"); // moves using tha ACSII right arrow
		run();
		break;
	case 'u': //Undo
		undo(); // undos the last change by pressing u
		run();
		break;
	case ':':
		pos.moveCursor(0, allText.getLength()); // moves the cursor down to the bottom
		run();
		break;
	case 'd': // deletes full lines of the text file
		command = _getch(); //gets each char input 
		switch (command)
		{
		case 'd':
			WriteUndo(' ', allText.getEntry(pos.getY() + 1)); // if statement gets the y position of the cursor and removes what is in that position
			allText.remove(pos.getY() + 1);
			run();
			break;
		default:
			WriteChar(command); 
			run(); // if no cases are given, the program continues to run
			break;
		}
	default:
		run(); // allows user to edit the text file
	}
}

//Move cursor
void Editor::Move(string direction)
{
	if (direction == "UP") { // moves the cursor up
		if (pos.getY() > 0) // if the y position is greater than 0,
		{
			pos.moveCursor(0, -1); // move the cursor up ome
			if (pos.getX() > allText.getEntry(pos.getY() + 1).length()) // gets the position of the cursor and moves it depeneding on the position
				pos.setX(allText.getEntry(pos.getY() + 1).length());
		}
	}
	if (direction == "DOWN") {  // moves the cursor down
		if (pos.getY() < allText.getLength() - 1)  // if the y position is less than the current position
		{
			pos.moveCursor(0, 1); // move the cursor down one
			if (pos.getX() > allText.getEntry(pos.getY() + 1).length())  // gets the position of the cursor and moves it depeneding on the position
				pos.setX(allText.getEntry(pos.getY() + 1).length());
		}
	}
	if (direction == "LEFT") { // moves the cursor left
		if (pos.getX() > 0)  // if the x position is greater than 0,
		{
			pos.moveCursor(-1, 0); // gets the position of the cursor and moves it depeneding on the position
		}
	}
	if (direction == "RIGHT") { // moves the cursor right
		if (pos.getX() < allText.getEntry(pos.getY() + 1).length())  // if the y position is less than the current position
		{
			pos.moveCursor(1, 0); // gets the position of the cursor and moves it depeneding on the position
		}
	}
}

//Write char to allText LinkedList 
void Editor::WriteChar(char cmd)  // function that allows user to edit the file
{
	string cur = allText.getEntry(pos.getY() + 1);
	string L1, L2;
	for (int i = 0; i < pos.getX(); i++) // for loop that that increases the position boundries for each line
	{
		L1 += cur[i];  // increases the line 
	}
	for (int i = pos.getX(); i < cur.length(); i++)// for loop that that increases the position boundries for each line
	{
		L2 += cur[i];  // increases the line
	}
	string newline = L1 + cmd + L2; // adds the parameters and line variables together
	allText.replace(pos.getY() + 1, newline); // replaces the original set string variable 
}

//Delete char from allText LinkedList
void Editor::DeleteChar()
{
	string cur = allText.getEntry(pos.getY() + 1); // sets the string cur to the y position 
	string newline;
	for (int i = 0; i < cur.length(); i++) // for loop that that increases the position boundries for each line
	{
		if (i != pos.getX()) // if statment that checks the x position
		{
			newline += cur[i]; // increases the new line by 1
		}
		else {
			WriteUndo(cur[i], ""); // else undos the last change
		}
	}
	allText.replace(pos.getY() + 1, newline);  // deletes each char that the user deletes 
	changes = true;  // makes sure if there are changes to the file
}

//Initlize new Undo object and update latest values then push to undos LinkedStack
void Editor::WriteUndo(char C, string S)
{
	lastAction.setChar(C); //Set last deleted char
	lastAction.setString(S); //Set last deleted line
	lastAction.setLastPos(pos); //Set last pos
	lastAction.setLastCMD(command); //Set last used command
	undos.push(lastAction);
}

//Undo
void Editor::undo()
{
	if (!undos.isEmpty()) { // checks to see if the stack is not empty
		Undo checkLastAction = undos.peek(); // sets the variable checklastaction to peek the stack
		undos.pop(); //pops the value on the stack
		pos = checkLastAction.getPos(); // sets pos to the getposition function
		if (checkLastAction.getCMD() == 'x') { // if the last action was the user typing in x, 
			WriteChar(checkLastAction.getC()); // the write char function will call the get char fucntion from the undo
		}
		if (checkLastAction.getCMD() == 'd') { // if the last action was deleting a line, 
			allText.insert(pos.getY() + 1, checkLastAction.getS()); //gets the position of a line and and gets the last line that was deleteed to pop on the stack again
		}

	}
}

//Save
void Editor::Save() // function that allows user to save their progress
{
	myFile.open(fileName, ofstream::out | ofstream::trunc);// opens the data file, and then overwrites the data file

	for (int i = 0; i < allText.getLength(); i++) // for loop that gets the length of the string
	{
		myFile << allText.getEntry(i + 1) << endl;  // passes the new text into the file
	}

	myFile.close(); // closes file
	

}

//Quit, prompt save
bool Editor::Quit()
{
	string cond;
	pos.setCursorPos(0, allText.getLength());  // sets the position to the position it is currently in

	if (changes) // is statement that checks if there are changes in the file
	{
		cout << "Do you want to quit without saving? y/n" << endl;  // asks user if they want to quit
		cin >> cond;

		if (cond == "y")  // if user types y, the program will quit without saving
		{
			return true;
		}
		else {
			pos.setCursorPos(0, 0);  // sets the position to the original position at 0
			return false;
		}
	}
	else {
		pos.setCursorPos(0, allText.getLength()); //goes back to the position from before
		return true;
	}

}
