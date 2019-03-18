// Greg Wagner
// Discrete Structures
// Lab4 
// This programs purpose is to multiply two user input arrays, as long as they 
// are of dimensions <=10 by <=10, and as long as they can be multiplied. 
// i.e. dimensions: MxA * AxW
// Finally showing the equivalent array as output.

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int MAX_SIZE = 10; // max size of any array entered

void GetDimensions(int& r, int& c);
void ReadArrayInput(int array[][MAX_SIZE], int row, int column);
void MultiplyArrays(int a1[][MAX_SIZE], int a2[][MAX_SIZE], int a3[][MAX_SIZE], int r1, int c1, int r2, int c2);
int MultiplyRC(int a1[][MAX_SIZE], int a2[][MAX_SIZE], int currentR, int currentC, int c1, int r2);
void DisplayArray(int array[][MAX_SIZE], int row, int column);

int main()
{
    int row1, column1, row2, column2;
    int array1[MAX_SIZE][MAX_SIZE] = {0};
    int array2[MAX_SIZE][MAX_SIZE] = {0};
    int array3[MAX_SIZE][MAX_SIZE] = {0};

    cout << "Please input the row and column dimensions of the first array: ";
    GetDimensions(row1, column1);
    
    cout << "Please input array 1:" << endl;
    ReadArrayInput(array1, row1, column1);
    cout << endl;

    cout << "Please input the row and column dimensions of the second array: ";
    GetDimensions(row2, column2);
    
    cout << "Please input array 2:" << endl;
    ReadArrayInput(array2, row2, column2);
    cout << endl;
    
    if (column1 == row2)
    {
        MultiplyArrays(array1, array2, array3, row1, column1, row2, column2);
        cout << "The answer is" << endl;
        DisplayArray(array3, row1, column2);
        cout << endl << endl;
    }
    else cout << "These arrays cannot be multiplied." << endl << endl;
    
    return 0;
}

void GetDimensions(int& r, int& c)
{
    string intRow;
    
    while (true) 
    {
        getline(cin, intRow);

        // This code converts from string to number and checks input
        stringstream myStream(intRow);
        if (myStream >> r >> c)
            break;
        cout << "Invalid number, please try again" << endl;
    }
}

void ReadArrayInput(int array[][MAX_SIZE], int row, int column)
{
    string rowOfInt;
    int count;
    
    
    for (int i = 0; i < row; i++)
    {
        count = 0;
        while (count < column)
        {
            count = 0;
            getline(cin, rowOfInt);
            stringstream rowStream(rowOfInt);
            for (int j = 0; j < column; j++)
            {
                if (rowStream >> array[i][j])
                    count ++;
                else
                {
                    cout << "Invalid number, please try again" << endl;
                    continue;
                }
            }
        }
    }
}

void MultiplyArrays(int a1[][MAX_SIZE], int a2[][MAX_SIZE], int a3[][MAX_SIZE], int r1, int c1, int r2, int c2)
{
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j< c2; j++)
        {
            a3[i][j] = MultiplyRC(a1, a2, i, j, c1, r2);
        }
    }
}

int MultiplyRC(int a1[][MAX_SIZE], int a2[][MAX_SIZE], int currentR, int currentC, int c1, int r2)
{
    int sum = 0;
    
    for (int i = 0; i < r2; i++)
    {
        sum += a1[currentR][i] * a2[i][currentC];
    }
    
    return sum;
}

void DisplayArray(int array[][MAX_SIZE], int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j< column; j++)
            cout << array[i][j] << " ";
        cout << endl;
    }
}