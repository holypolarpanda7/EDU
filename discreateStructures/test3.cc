
// Discrete Structures
// Lab2 truth table program
// This programs purpose is to allow input from a user in the form of a 
// "well formed formula" (wff), with one of four logical operators (and 
// = A, or = O, not = N, and implies = I), and produce the correct truth
// table for that wff.

#include <iostream>
using namespace std;

const int SIZE = 8; // constant size of 2 element truth table
bool pTable[SIZE] = {true, true, true, true, false, false, false, false}; // 'P's truth table
bool qTable[SIZE] = {true, true, false, false, true, true, false, false}; // 'Q's truth table
bool rTable[SIZE] = {true, false, true, false, true, false, true, false}; //  boom

void ReadTable(char character, bool truthTable[]);
void NegateTable(bool table[]);
void DisplayTable(bool table[]);

main()
{

	bool table1[SIZE];
	bool table2[SIZE];
    bool table3[SIZE];
	
     // possible characters read in as input
	char char1, char2, char3;
	cout << "Please input the first expression: ";
	cin.get(char1);					// read in input and identify correct
	ReadTable(char1, table1);		// tables for that character
	NegateTable(table1);
    DisplayTable(table1);
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
	else if (character == 'Q')
	{
		for (int i=0; i<SIZE; i++)
		{
			table[i] = qTable[i];
		}
	}
    else
	{
		for (int i=0; i<SIZE; i++)
		{
			table[i] = rTable[i];
		}
	}
	return;
}

void NegateTable(bool table[])
{
    for (int i = 0; i < SIZE; i++)
		{
			table[i] = !table[i];
		}
    return;
}

void DisplayTable(bool table[])
{
    for (int i = 0; i < SIZE; i++)
		{
			if (table[i] == true)
            {
                cout << 'T' << endl;
            }
            else
            {
                cout << 'F' << endl;
            }
		}
    return;
}