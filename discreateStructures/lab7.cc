// Greg Wagner
// Discrete Structures
// Lab7 
// This programs purpose is to read in a graphs binary relation, output an adjacency matrix and decide if an euler path exists in the
// graph that the data describes.


#include <iostream>

using namespace std;

const int SIZE = 10;

void TakeBinaryRel(int a[][SIZE]);
void LoadAdjArray(int a[][SIZE]);
void Pair(int a[][SIZE]);
int DisplayArray(int a[][SIZE], int size);


int main()
{
    int adjArray[SIZE][SIZE] = {0};
    int nodesNo, odds;
    
    cout << "How many nodes are in the graph? ";
    cin >> nodesNo;
    cin.ignore(100, '\n');
    cout << "Please input the binary relation for the graph:" << endl;
    TakeBinaryRel(adjArray);
    cout << "The adjacency matrix is:" << endl;
    odds = DisplayArray(adjArray, nodesNo);
    
    if (odds == 0 || odds == 2)
        cout << "An Euler path does exist in the graph.";
    else
        cout << "An Euler path does not exist in the graph.";
    cout << endl << endl;
    
    return 0;
}

void TakeBinaryRel(int a[][SIZE])
{
    char next;
    
    while (true)
    {
        cin >> next;
        if (next == '{')
        {
            LoadAdjArray(a);
            break;                    //begin taking pairs
        }
        cout << "You must start the relation with a '{'." << endl;
    }
}

void LoadAdjArray(int a[][SIZE])
{
    char next;
    
    while (true)
    {
        cin >> next;
        if (next == '(')
        {
            Pair(a);     //begin taking pairs
            break;
        }
        else if (next == ',' || next == ')')
        {
            LoadAdjArray(a);
            break;
        }
        else
            break;
    }
}

void Pair(int a[][SIZE])
{
    char sep;
    int first, second;
    
    cin >> first;
    cin >> sep;
    cin >> second;
    a[first-1][second-1] = 1;
    LoadAdjArray(a);
}

int DisplayArray(int a[][SIZE], int size)
{
    int sum, count;
    
    count = 0;
    for (int i =0; i < size; i++)
    {
        sum = 0;
        for (int k = 0; k < size; k++)
        {
            sum += a[i][k];
            if (k != 0)
                cout << " ";
            cout << a[i][k];
        }
        if (sum % 2)
            count += 1;
        cout << endl;
    }
    return count;
}
