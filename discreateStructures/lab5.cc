// Greg Wagner
// Discrete Structures
// Lab5 
// This programs purpose is to read in an array-pointer representation via an array.  Then calculate the adjacency matrix of the arrays graph.
// It also notifies the user of any nodes that may be isolated in the graph.

#include <iostream>
#include <iomanip>

using namespace std;

const int ROW_SIZE = 30;
const int COL_SIZE = 2;
const int ADJ_SIZE = 5;

void LoadArrayPointer(int a[][COL_SIZE], int rows);
void LoadAdjMat(int m[][ADJ_SIZE], int a[][COL_SIZE], int rows);
void Isolated(int a[][ADJ_SIZE], int size);
void DisplayArray(int a[][ADJ_SIZE], int size);

int main()
{
    int arrPointer[ROW_SIZE][COL_SIZE] = {0};
    int adjMat[ADJ_SIZE][ADJ_SIZE] = {0};
    int nodesNo, aPRows;
    
    cout << "Please input the number of nodes: ";
    cin >> nodesNo;
    cout << "How many rows are in the array-pointer representation? ";
    cin >> aPRows;
    cout << "Please inout the array-pointer representation of the graph: " << endl;
    LoadArrayPointer(arrPointer, aPRows);
    LoadAdjMat(adjMat, arrPointer, aPRows);
    cout << endl;
    Isolated(adjMat, nodesNo);
    cout << "The adjacency matrix is" << endl;
    DisplayArray(adjMat, nodesNo);
   
   return 0;
}

void LoadArrayPointer(int a[][COL_SIZE], int rows)
{
    for (int i =0; i < rows; i++)
    {
        for (int k = 0; k < COL_SIZE; k++)
        {
            cin >> a[i][k];
        }
    }
}

void LoadAdjMat(int m[][ADJ_SIZE], int a[][COL_SIZE], int rows)
{
    int fromNode, toNode, index;
    
    for (int i = 0; i < rows; i++)
    {
        index = a[i][1];
        if (index != -1)
        {
            fromNode = a[i][0];
            toNode = a[index-1][0];
            m[fromNode-1][toNode-1] = 1;
            m[toNode-1][fromNode-1] = 1;
        }
    }
}

void Isolated(int a[][ADJ_SIZE], int size)
{
    int sum, count;
    
    count = 0;
    for (int i =0; i < size; i++)
    {
        sum = 0;
        for (int k = 0; k < size; k++)
            sum += a[i][k];
        if (sum == 0)
            cout << "node " << i+1 << " is isolated" << endl;
        else
            count += 1;
    }
    if (count == size)
        cout << "There are no isolated nodes" << endl;
}

void DisplayArray(int a[][ADJ_SIZE], int size)
{
    for (int i =0; i < size; i++)
    {
        for (int k = 0; k < size; k++)
        {
            if (k != 0)
                cout << " ";
            cout << setw(2) << left << a[i][k];
        }
        cout << endl;
    }
}