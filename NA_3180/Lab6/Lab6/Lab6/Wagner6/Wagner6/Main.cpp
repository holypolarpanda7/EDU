// Greg Wagner
// Lab6
// Main.cpp : systematic procedure for implimenting natural cubic splines for
// the data points at x= (-8, -6, -4, -2, 0, 2, 4, 6, 8)
// Input: NONE
// Output: data points (t,y), tridiagonal systems(pre+post elimination), solution,
// coeffiecients, Natural Cubic Splines, table containing-x, f(x), S(x), difference
// Data Analysis - 3180
// Due: Mar 21,2019

#define _CRT_SECURE_NO_DEPRECATE // for system(pause)
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define POINTS 9

double f(double x);												// function f(x)
void PrintTri(double * u, double * l, double * h, double * v);  // print out a tridiagonal sys

int main()
{
	FILE * fout = fopen("S(x).txt", "w");
	if (fout == NULL){
		printf("Could not open file");
	}
	// initailize necessary vars
	double xVals[POINTS] = { -8,-6,-4,-2,0,2,4,6,8 }; // x values to evaluate
	double yVals[POINTS];                           // y values array
	double h = 2;			// step sizes between x (same in this case so no array)
	double vVals[POINTS - 2];						// intermitant v values
	double uVals[POINTS - 2];						// intermitant u values
	double zVals[POINTS];							// z values (i.e. S''(x))
	double hVals[POINTS - 3];						// tridiagonal h values
	double lVals[POINTS - 3];						// tridiagonal l values
	double A[POINTS - 1];
	double B[POINTS - 1];							// Coefficient Arrays 
	double C[POINTS - 1];
	double D[POINTS - 1];
	double sol, m, tmp;                                     // solution
	int i, tmp2;                                          // always an i in a program

														  // prefill z h l values
	for (i = 0; i < POINTS; i++) {
		zVals[i] = 0;
	}
	for (i = 0; i < POINTS - 3; i++) {
		hVals[i] = h;
		lVals[i] = h;
	}
	// find the y values associated with f(x) and store them in an array
	// and print the points
	printf("Data Points (ti, yi)\n");
	for (i = 0; i < POINTS; i++) {
		yVals[i] = f(xVals[i]);
		printf("(t%d, y%d) = (%g, %g)\n", i, i, xVals[i], yVals[i]);
	}

	// compute v and u values (AKA u=d, v=b as seen in handout)
	// v(i)= 6[1/h(i)[y(i+1) - y(i)]- 1/h(i-1)[y(i) - y(i-1)]]] & u(i) = 2[h(i-1) + h(i)]
	for (i = 1; i < POINTS - 1; i++) {
		vVals[i - 1] = 6 * (1 / h * (yVals[i + 1] - yVals[i]) - 1 / h * (yVals[i] - yVals[i - 1]));
		uVals[i - 1] = 2 * (h + h);
	}

	// print the "Tridiagonal system for z(1) through z(n-1)"
	printf("\nTri-diagonal system for z1 though z(n-1)\n\n");
	PrintTri(uVals, lVals, hVals, vVals);

	// forward elimination phase
	for (i = 1; i < (sizeof(vVals) / 8); i++) {
		m = lVals[i - 1] / uVals[i - 1];
		lVals[i - 1] = lVals[i - 1] - uVals[i - 1] * m;
		uVals[i] = uVals[i] - hVals[i - 1] * m;
		vVals[i] = vVals[i] - vVals[i - 1] * m;
	}

	// Print after forward elimination
	printf("\nTri-diagonal system after forward elimination\n\n");
	PrintTri(uVals, lVals, hVals, vVals);

	// back substitution phase
	zVals[POINTS - 2] = vVals[POINTS - 3] / uVals[POINTS - 3];
	for (i = POINTS - 3; i > 0; i--) {
		zVals[i] = (vVals[i - 1] - zVals[i + 1] * hVals[i - 1]) / uVals[i - 1];
	}

	// Print solutions for zi AKA S''
	printf("\nSolutions for S''(ti) = zi\n--------------------------\n");
	for (i = 0; i < POINTS; i++) {
		printf("z%d:%g\n", i, zVals[i]);
	}

	// Determine Spline coefficients
	for (i = 0; i < POINTS - 1; i++) {
		//printf("\niteration:%d\n", i);
		A[i] = yVals[i];
		//printf("zi+1 %g   zi %g yi%g\n",zVals[i+1], zVals[i], yVals[i]);
		B[i] = (-1 * (h) / 6 * zVals[i + 1]) - (h / 3 * zVals[i]) + ((yVals[i + 1] - yVals[i]) / h);
		C[i] = zVals[i] / 2;
		D[i] = (zVals[i + 1] - zVals[i]) / (6 * h);
	}

	// Print Coefficients for Natural Cubic Spline in nested form 
	printf("\nCoefficients for Natural Cubic Spline in nested form\n");
	printf("----------------------------------------------------------------\n");
	for (i = 0; i < POINTS - 1; i++) {
		printf("A%d:%11g   B%d:%11g   C%d:%11g   D%d:%11g\n", i, A[i], i, B[i], i, C[i], i, D[i]);
	}

	// Print Natural Cubic Spline in nested form
	printf("\nNatural Cubic Spline in nested form\n");
	printf("----------------------------------------------------------------\n");
	for (i = 0; i < POINTS - 1; i++) {
		printf("S%d :", i);
		fprintf(fout, "S%d :", i);
		printf("%g+(x-(%g))*(%g+(x-(%g))*(%g+(x-(%g))*(%g)))\n", A[i], xVals[i],
			B[i], xVals[i], C[i], xVals[i], D[i]);
		fprintf(fout, "%g+(x-(%g))*(%g+(x-(%g))*(%g+(x-(%g))*(%g)))\n", A[i], xVals[i],
			B[i], xVals[i], C[i], xVals[i], D[i]);
	}

	// Print Evaluation of Original and Spline functions and the absolute errors
	printf("\nEvaluation of Original and Spline functions and the absolute errors\n");
	printf("-------------------------------------------------------------------\n");
	printf(" i        xi           f(xi)          S(xi)     |f(xi) -S(xi)|\n");
	printf("-------------------------------------------------------------------\n");
	tmp = xVals[0];
	tmp2 = 0;
	for (i = 0; i < (xVals[POINTS - 1] - xVals[0] + 1); i++) {
		printf("%2d%14.6f%14.6f", i, i + xVals[0], f(double(i) + xVals[0]));
		sol = A[tmp2] + ((i + xVals[0]) - tmp) * (B[tmp2] + ((i + xVals[0]) - tmp) * (
			C[tmp2] + ((i + xVals[0]) - tmp) *(D[tmp2])));
		printf("%14.6f%14.6f\n", sol, fabs(f(double(i) + xVals[0]) - sol));
		if (i % 2 == 0 && i != 0) { tmp += 2; tmp2++; }
	}

	fclose(fout);
	system("Pause");
	return 0;
}

double f(double x) {
	// return y value of the function f(x) = 1/(x^2 + 1)
	return 1.0 / (x * x + 1.0);
}

void PrintTri(double * u, double * l, double * h, double * v) {
	int i, j;
	char zeros[] = "     0";

	for (i = 0; i < POINTS - 2; i++) {
		// print leading zeros
		for (j = 1; j < i; j++) {
			printf("%10s", zeros);
		}
		// print v l u and h values
		// first line will not have l value
		if (i != 0) { printf("%10g", l[i - 1]); }
		// all u values
		printf("%10g", u[i]);
		// last line will not have h value
		if (i != POINTS - 3) { printf("%10g", h[i]); }
		// print trailing zeros
		for (j = (POINTS - 4); j > i; j--) {
			printf("%10s", zeros);
		}
		// print all v values
		printf("%12g\n", v[i]);
	}
}