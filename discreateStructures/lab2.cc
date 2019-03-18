// Greg Wagner
// Discrete Structures
// Lab2 truth table program
// This programs purpose is to allow input from a user in the form of a 
// "well formed formula" (wff), with one of four logical operators (and 
// = A, or = O, not = N, and implies = I), and produce the correct truth
// table for that wff.

#include <iostream>
using namespace std;

const int SIZE = 4; // constant size of 2 element truth table
bool pTable[SIZE] = {true, true, false, false}; // 'P's truth table
bool qTable[SIZE] = {true, false, true, false}; // 'Q's truth table

void ReadTable(char character, bool truthTable[]);
void EvaluateWff(bool table1[], bool table2[], char op);

main()
{

	bool table1[SIZE];
	bool table2[SIZE];
	
	char char1, char2, char3; // possible three characters read in as input
	cout << "Please input the wff: ";
	cin.get(char1);					// read in input and identify correct
	ReadTable(char1, table1);		// tables for that character
	cin.get(char2);
	if (char2 != 'N')				// short cuircut evaluation for only
	{								// two character input
		ReadTable(char2, table2);
		cin.get(char3);
	}
	else 
	{
		char3 = char2;				// char3 is operator character
	}
	EvaluateWff(table1, table2, char3);

	return 0;
}

// this function fills out the working arrays within the program
// with the desired values
void ReadTable(char character, bool table[])
{
	if (character == 'P')
	{
		for (int i=0; i<SIZE; i++)
		{
			table[i] = pTable[i];
		}
	}
	else
	{
		for (int i=0; i<SIZE; i++)
		{
			table[i] = qTable[i];
		}
	}
	return;
}

// this function makes a comparison based on the logic operator character
// and displays the related truth table based on it two elements
void EvaluateWff(bool table1[], bool table2[], char op)
{
	if (op == 'N') // "not" operator identified
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (table1[i] != true)
				cout << 'T' << endl;
			else
				cout << 'F' << endl;
		}
	}
	else if (op == 'A') // "and" operator identified
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (table1[i] == true && table2[i] == true)
				cout << 'T' << endl;
			else
				cout << 'F' << endl;
		}
	}
	else if (op == 'O') // "or" operator identified
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (table1[i] == true || table2[i] == true)
				cout << 'T' << endl;
			else
				cout << 'F' << endl;
		}
	}
	else // only other input identified as "implies"
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (table1[i] == true && table2[i] == false)
				cout << 'F' << endl;
			else
				cout << 'T' << endl;
		}
	}
}	
