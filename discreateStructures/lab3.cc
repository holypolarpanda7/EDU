// Greg Wagner
// Discrete Structures
// Lab3 advanced truth table program
// This programs purpose is to allow input from a user in the form of two 
// "well formed formula" (wff)'s, with one of four logical operators (and 
// = A, or = O, not = N, and implies = I), and produce the correct truth
// table for those wff's. Then examines the equivalence of each of those wffs.

#include <iostream>
#include <iomanip>
using namespace std;

const int SIZE = 8; // constant size of all truth table
bool pTable[SIZE] = {true, true, true, true, false, false, false, false}; // 'P's truth table
bool qTable[SIZE] = {true, true, false, false, true, true, false, false}; // 'Q's truth table
bool rTable[SIZE] = {true, false, true, false, true, false, true, false}; //  boom

void ReadTable(char character, bool truthTable[]);
int EvaluateSub(bool table1[], bool table2[]);
void NegateTable(bool table[]);
void EvaluateInTwos(bool table1[], bool table2[], char op);


int main()
{

	bool table1[SIZE];
	bool table2[SIZE]; // represents unused truth table arrays
    bool table3[SIZE];
	
     // possible characters read in as input
	char char1;
    int cont, tracker = 0; // cont is either 0 or 1 and controls wff expression evaluation and 
                            // tracker tracks possible tautology for overall equivalence
    
	cout << "Please input the first expression: ";
	cin.get(char1);					// read in input and identify correct
	ReadTable(char1, table1);		// tables for that character
	while (cont == 0)               // loop continuously to find equivalent TT(truth table) for expression
    {
        cont = EvaluateSub(table1, table2);
    }
    
    cin.ignore(100,'\n');           // eliminates connection of seperate inputs
    cont = 0;
    cout << "Please input the second expression: ";
	cin.get(char1);					// read in input and identify correct
	ReadTable(char1, table2);		// tables for that character
	while (cont == 0)
    {
        cont = EvaluateSub(table2, table3);
    }
    
    for (int i = 0; i<SIZE; i++)        // compare TT of expressions 1 and 2 and create a third table
    {
        if (table1[i] == table2[i])
        {
            table3[i] = true;
            tracker += 1;
        }               // track equivalence of two expressions
        else
            table3[i] = false;
    }
    
    cout << setw(11) << left << "first" << setw(11) << left << "second" << setw(11) << left << "equivalence" << endl;
    for (int i = 0; i<SIZE; i++)
    {
        if (table1[i] == true)
            cout << setw(15) << left << 'T';                // prints truth tables
        else
            cout << setw(15) << left << 'F';
        if (table2[i] == true)
            cout << setw(15) << left << 'T';
        else
            cout << setw(15) << left << 'F';
        if (table3[i] == true)
            cout << setw(15) << left << 'T' << endl;
        else
            cout << setw(15) << left << 'F' << endl;
    }
    
    if (tracker == 8)
        cout << "The two expressions are equivalent." << endl;
    else
        cout << "The two expressions are not equivalent." << endl;
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

// This function reads in the next character of an expression and performs the nessecary operation
int EvaluateSub(bool table1[], bool table2[])
{
    char nextChar1, nextChar2;
    
    cin.get(nextChar1);
    
    if (nextChar1 == 'P' || nextChar1 == 'Q' || nextChar1 == 'R')
    {
        ReadTable(nextChar1, table2);
        cin.get(nextChar2);
        if (nextChar2 == 'N')
            NegateTable(table2);
        else
        {
            EvaluateInTwos(table1, table2, nextChar2);
        }
    }
	else if (nextChar1 == 'N')				// 
    {
        NegateTable(table1);
    }
    else if (nextChar1 == 'E')
    {
        return 1;
    }
    else
    {
        EvaluateInTwos(table1, table2, nextChar1);
    }
    return 0;
} 

void NegateTable(bool table[])
{
    for (int i = 0; i < SIZE; i++)
		{
			table[i] = !table[i];
		}
}

// this function makes a comparison based on the logic operator character
// and condenses the related truth table based on it two elements
void EvaluateInTwos(bool table1[], bool table2[], char op)
{
	if (op == 'A') // "and" operator identified
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (table1[i] == true && table2[i] == true)
				table1[i] = true;
			else
				table1[i] = false;
		}
	}
	else if (op == 'O') // "or" operator identified
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (table1[i] == true || table2[i] == true)
				table1[i] = true;
			else
				table1[i] = false;
		}
	}
	else // only other input identified as "implies"
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (table1[i] == true && table2[i] == false)
				table1[i] = false;
			else
				table1[i] = true;
		}
	}
}	
