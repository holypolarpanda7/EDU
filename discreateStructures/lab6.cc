// Greg Wagner
// Discrete Structures
// Lab6 
// This programs purpose is to read in a left-right child arra of a binary tree graph, reprint the tree and notify the user of any leafs.


#include <iostream>
#include <iomanip>

using namespace std;

const int COL_SIZE = 2;
const int ROW_SIZE = 10;

void LoadLRArray(int a[][COL_SIZE], int rows);
void DisplayArray(int a[][COL_SIZE], int size);
int FindLeafs(int a[][COL_SIZE], int lA[], int size);

int main()
{
    int lRArray[ROW_SIZE][COL_SIZE] = {0};
    int leafArray[ROW_SIZE] = {0};
    int nodesNo, leaves;
    
    cout << "Please input the number of nodes: ";
    cin >> nodesNo;
    cout << "Please enter the left child - right child array representation of the graph:" << endl;
    LoadLRArray(lRArray, nodesNo);
    cout << "The left child - right child array representation is..." << endl;
    DisplayArray(lRArray, nodesNo);
    leaves = FindLeafs(lRArray, leafArray, nodesNo);
    
    if (leaves > 1)
    {
        cout << "The leaves are ";
        for (int i = 0; i < leaves; i++)
        {
            if (i != leaves -1)
                cout << leafArray[i] << ", ";
            else
                cout << "and " << leafArray[i] << endl;
        }   
    }
    else if (leaves == 1)
        cout << "The only leaf is " << leafArray[0] << "." << endl;
    
    return 0;
}

void LoadLRArray(int a[][COL_SIZE], int rows)
{
    for (int i =0; i < rows; i++)
    {
        for (int k = 0; k < COL_SIZE; k++)
        {
            cin >> a[i][k];
        }
    }
}

void DisplayArray(int a[][COL_SIZE], int size)
{
    for (int i =0; i < size; i++)
    {
        for (int k = 0; k < COL_SIZE; k++)
        {
            if (k != 0)
                cout << " ";
            cout << setw(1) << left << a[i][k];
        }
        cout << endl;
    }
}

int FindLeafs(int a[][COL_SIZE], int lA[], int size)
{
    int sum, count;
    
    count = 0;
    for (int i =0; i < size; i++)
    {
        sum = 0;
        for (int k = 0; k < COL_SIZE; k++)
            sum += a[i][k];
        if (sum == 0)
        {
            lA[count] = i+1;
            count += 1;
        }
    }
    return count;
}