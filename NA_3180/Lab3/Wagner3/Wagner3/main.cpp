// Greg Wagner
// Intro to Numerical Analysis - 3180
// Due: Feb 5, 2019
// Lab 3 - Loss of Significants
// This program tests the loss of significants for two functions
// each function is rewritten once in order to minimize loss
// Input: NONE
// Output: x, f(x), f2(x), g(x), g2(x) (each set is done in float and double values)

#define _CRT_SECURE_NO_DEPRECATE // for system(pause)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main() {
	int i;
	float answ1, answ2, x;
	double ans1, ans2, y;
	

	FILE *datafile = fopen("data.csv", "w+"); // to make generating 
	if ((datafile == NULL)) {                 // a data table easy in the report
		printf("Could not open the file\n");
	}

	fprintf(datafile, " ,Floating point\nx,f(x),f2(x)\n");
	printf("%35s\n", "float");
	printf("%15c%20s%25s\n", 'x', "f(x)", "f2(x)");
	x = 1; // initial step size
	for (i = 0; i < 10; i++) {
		ans1 = x * (sqrtf(x + 1) - sqrtf(x));
		ans2 =  x / (sqrtf(x + 1) + sqrtf(x));
		printf("%15.0f%26.15f%26.15f\n", x, ans1, ans2);
		fprintf(datafile, "%15.0f%26.15f%26.15f\n", x, ans1, ans2);
		x = x * 10;
	}
	
	fprintf(datafile, " ,Double point\nx,f(x),f2(x)\n");
	printf("\n%35s\n", "double");
	printf("%15c%20s%25s\n", 'x', "f(x)", "f2(x)");
	y = 1; // initial step size
	for (i = 0; i < 10; i++) {
		answ1 = y * (sqrt(y + 1) - sqrt(y));
		answ2 = y / (sqrt(y + 1) + sqrt(y));
		printf("%15.0lf%26.15lf%26.15lf\n", y, answ1, answ2);
		fprintf(datafile, "%15.0lf%26.15lf%26.15lf\n", y, answ1, answ2);
		y = y * 10;
	}

	fprintf(datafile, " ,Floating point\nx,g(x),g2(x)\n");
	printf("%35s\n", "float");
	printf("%15c%20s%25s\n", 'x', "g(x)", "g2(x)");
	x = 1; // initial step size
	for (i = 0; i < 10; i++) {
		ans1 = 1 - cosf(x) / powf(x, 2.0);
		ans2 = 2 * powf(sinf((x / 2)), 2.0) / powf(x, 2.0);
		printf("%15.0f%26.15f%26.15f\n", x, ans1, ans2);
		fprintf(datafile, "%15.0f%26.15f%26.15f\n", x, ans1, ans2);
		x = x * 10;
	}

	fprintf(datafile, " ,Double point\nx,g(x),g2(x)\n");
	printf("\n%35s\n", "double");
	printf("%15c%20s%25s\n", 'x', "g(x)", "g2(x)");
	y = 1; // initial step size
	for (i = 0; i < 10; i++) {
		answ1 = 1 - cos(y) / pow(y, 2.0);
		answ2 = 2 * pow(sin((y / 2)), 2.0) / pow(y, 2.0);
		printf("%15.0lf%26.15lf%26.15lf\n", y, answ1, answ2);
		fprintf(datafile, "%15.0lf%26.15lf%26.15lf\n", y, answ1, answ2);
		y = y * 10;
	}
	
	fclose(datafile);
	system("pause"); // this is why i dont like VS
}