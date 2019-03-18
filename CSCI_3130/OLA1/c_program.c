// Greg Wagner
// CSCI 3130 Dr. Phillips
// c_function.c
// declare asm_function using asm_function.o

#include <string.h>

void asm_function(const char *s); // declaration of asm_function found in asm_function.o

int main()
{
	const char* haiku = "From time to time\nThe clouds give rest\nTo the moon-beholders.\n\0";
	
	asm_function(haiku);
	
	return 0;
}