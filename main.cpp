#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <conio.h>
#include "Editor.h"
#include "Position.h"

using namespace std;

//Initialize cursor 

int main()
{
	string text; 
	Editor ed("input.txt"); // passes the text file into the editor class


	ed.run(); // calls the program to run the run function from the editor implementation file

	//(int arg c, char* agr v []);
}