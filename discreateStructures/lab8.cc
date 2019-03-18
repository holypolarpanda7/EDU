// Greg Wagner
// Discrete Structures
// Lab8
// This programs purpose is to read a trasmission from a '.dat' file do some magic and determine what message was sent

#include <iostream>
#include <fstream>

using namespace std;

const int SIZE = 12;
const int NEW_SIZE = 8;

int main()
{
	ifstream myIn;
    char no1, no2, no3, no4, no5, no6, no7, no8, no9, no10, no11, no12, correct, converted; 
	bool word[SIZE];
    int binary[NEW_SIZE];
    int par1, par2, par4, par8, character;
	myIn.open("packets.dat");

	while(myIn >> no1 >> no2 >>  no3 >> no4 >> no5 >> no6 >> no7 >> no8 >> no9 >> no10 >> no11 >> no12)
    {
        word[0] = no1 - '0'; //*
        word[1] = no2 - '0'; //*
        word[2] = no3 - '0';
        word[3] = no4 - '0'; //*         had to do this way cause packets.dat would not read as ints
        word[4] = no5 - '0';
        word[5] = no6 - '0';
        word[6] = no7 - '0';
        word[7] = no8 - '0'; //*
        word[8] = no9 - '0';
        word[9] = no10 - '0';
        word[10] = no11 - '0';
        word[11] = no12 - '0';
        
        
        //decode hamming and correct
        par1 = (word[0] + word[2] + word[4] + word[6]+ word[8] + word[10]) % 2;
        par2 = (word[1] + word[2] + word[5] + word[6]+ word[9] + word[10]) % 2;
        par4 = (word[3] + word[5] + word[4] + word[6]+ word[11]) % 2;
        par8 = (word[7] + word[8] + word[9] + word[10]+ word[11]) % 2;
        
        correct = par1 + 2*par2 + 4*par4 + 8*par8;
        
        if (correct > 0)
        {
            word[correct-1] = !word[correct-1];
        }
        // convert from gray to binary
        binary[0] = word[2];                 //1
        if (word[2] % 2 == 0)                //2
            binary[1] = word[4];
        else
            binary[1] = !word[4];            //3
        if ((word[2] + word[4]) % 2 == 0)
            binary[2] = word[5];
        else
            binary[2] = !word[5];            //4 
        if ((word[2] + word[4] + word[5]) % 2 == 0)
            binary[3] = word[6];
        else
            binary[3] = !word[6];            //5
        if ((word[2] + word[4] + word[5] + word[6]) % 2 == 0)
            binary[4] = word[8];
        else
            binary[4] = !word[8];            //6
        if ((word[2] + word[4] + word[5] + word[6] + word[8]) % 2 == 0)
            binary[5] = word[9];
        else
            binary[5] = !word[9];            //7
        if ((word[2] + word[4] + word[5] + word[6] + word[8] + word[9]) % 2 == 0)
            binary[6] = word[10];
        else
            binary[6] = !word[10];           //8
        if ((word[2] + word[4] + word[5] + word[6] + word[8] + word[9] + word[10]) % 2 == 0)
            binary[7] = word[11];
        else
            binary[7] = !word[11];
        
        character = (binary[7] + binary[6]*2 + binary[5]*4 + binary[4]*8 + binary[3]*16 + binary[2]*32 + binary[1]*64 + binary[0] *128)-3;
        converted = character;
        
        cout << converted;
        
        myIn.ignore(100, '\n');
	}
    cout << endl;
	myIn.close();

	return 0;
}