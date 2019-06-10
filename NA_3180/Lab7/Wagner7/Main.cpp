// Greg Wagner
// Lab7
// Main.cpp : Numerical methods for root finding, specifically: bisection and secant
// for the function: f(x) = x^3 - 2x^2 - 5x + 6
// Input: x0,x1,maxIterations,xTolerance, yTolerance
// Output: per iteration (a,b,c,ydiff, errBound)
// Data Analysis - 3180
// Due: Apr 4,2019

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <iostream>
using namespace std;

// function f(x)
double f(double x);
// secant method
void secant(FILE * f, double l, double u, int maxIt, double xT, double yT);
// bisection method
void bisection(FILE * f, double l, double u, int maxIt, double xT, double yT);

int main()
{
	FILE * fil;
	char choice;
	// 5 parameters to test each method with (interval(a,b), max iterations, x&y tolerance)
	double x0, x1, xTolerance, yTolerance;
	int maxIterations;
	xTolerance = 0.001;
	yTolerance = 0.00001;

	while (1) {
		printf("\nFind roots/continue?: (y/n)");
		scanf(" %c", &choice);
		if (choice != 'y') return 0;

		// append to fil
		fil = fopen("rootdata.csv", "a");
		// read in 5 parameters to test with each method
		printf("\ndouble x0: ");
		scanf("%lf", &x0);
		printf("double x1: ");
		scanf("%lf", &x1);
		printf("int maxIterations: ");
		scanf("%d", &maxIterations);
		printf("x_Tolerance: %.6lf\ny_Tolerance: %.6lf\n", xTolerance, yTolerance);
		fprintf(fil, "\ninterval,[%.2lf - %.2lf]\n", x0, x1);

		//call to secant method
		secant(fil, x0, x1, maxIterations, xTolerance, yTolerance);
		//call to bisection method
		bisection(fil, x0, x1, maxIterations, xTolerance, yTolerance);
		fclose(fil);
	}

	system("Pause");
	return 0;
}

double f(double x) {
	return (x * x * x) - 2 * (x * x) - 5 * x + 6;
}

void secant(FILE * fil, double a, double b, int maxIt, double xT, double yT) {
	double fa, fb, d, tmp;
	int i;

	printf("\n    Secant Method\n");
	fprintf(fil, "\nSecant Method\n");
	printf("--------------------------------------------------\n");
	fa = f(a);
	fb = f(b);
	//printf("fa %g    fb %g\n", fa, fb);
	// check initial guesses for roots
	if (fa == 0.000000) {
		printf("exact root found at %8.6lf\n", a);
		fprintf(fil, "exact root found at %8.6lf\n", a);
		return;
	}
	if (fb == 0.000000) {
		printf("exact root found at %8.6lf\n", b);
		fprintf(fil, "exact root found at %8.6lf\n", b);
		return;
	}
	// check abs val of fa and fb and swap if nec
	if (fabs(fa) > fabs(fb)) {
		tmp = a;
		a = b;
		b = tmp;
		tmp = fa;
		fa = fb;
		fb = tmp;
	}
	// begin iteration through bisection method
	printf("Iteration        Approx. root      x_tolerance     y_tolerance\n");
	fprintf(fil, "Iteration,Approx. root,x_tolerance,y_tolerance\n");
	for (i = 1; i < maxIt + 1; i++) {
		if (fabs(fa) > fabs(fb)) {
			tmp = a;
			a = b;
			b = tmp;
			tmp = fa;
			fa = fb;
			fb = tmp;
		}
		d = (b -a) / (fb -fa);
		b = a;
		fb = fa;
		d = d * fa;
		printf("%9d%18.6lf%18.6lf%18.6lf\n", i, a, b, d);
		fprintf(fil, "%9d,%18.6lf,%18.6lf,%18.6lf\n", i, a, b, d);
		if (fabs(d) < yT) {
			printf("Approximate root: %8.6lf\n", a);
			printf("Number of iterations: %d\n", i);
			printf("x_tolerance: %8.6lf\n", b);
			printf("y_tolerance: %8.6lf\n", d);
			return;
		}
		a = a - d;
		fa = f(a);
	}
	printf("Exceeded max iterations...\nApproximate root: %8.6lf\n", a);
}

void bisection(FILE * fil, double a, double b, int maxIt, double xT, double yT) {
	double c, fa, fb, fc, err;
	int i;

	printf("\n    Bisection Method\n");
	fprintf(fil, "\nBisection Method\n");
	printf("--------------------------------------------------\n");
	fa = f(a);
	fb = f(b);
	//printf("fa %g    fb %g\n", fa, fb);
	// check initial guesses for roots
	if (fa == 0.000000) {
		printf("exact root found at %8.6lf\n", a);
		fprintf(fil, "exact root found at %8.6lf\n", a);
		return;
	}
	if (fb == 0.000000) {
		printf("exact root found at %8.6lf\n", b);
		fprintf(fil, "exact root found at %8.6lf\n", b);
		return;
	}
	// check weather initial guesses yield promise for bisection method
	if (fa * fb > 0) {
		printf("Not able to find roots on interval: bad guesses...\n");
		fprintf(fil, "Not able to find roots on interval: bad guesses...\n");
		return;
	}
	// calc initial error
	err = b - a;
	// begin iteration through bisection method
	printf("Iteration        Approx. root      x_tolerance     y_tolerance\n");
	fprintf(fil, "Iteration,Approx. root,x_tolerance,y_tolerance\n");
	for (i = 1; i < maxIt+1; i++) {
		err = err / 2;
		c = a + err;
		fc = f(c);
		printf("%9d%18.6lf%18.6lf%18.6lf\n", i, c, err, fc);
		fprintf(fil, "%9d,%18.6lf,%18.6lf,%18.6lf\n", i, c, err, fc);
		if (fabs(fc) < yT) {
			printf("Approximate root: %8.6lf\n", c);
			printf("Number of iterations: %d\n", i);
			printf("x_tolerance: %8.6lf\n", err);
			printf("y_tolerance: %8.6lf\n", fc);
			return;
		}
		if (fa * fc < 0) {
			b = c;
			fb = fc;
		}
		else {
			a = c;
			fa = fc;
		}
	}
	printf("Exceeded max iterations...\nApproximate root: %8.6lf\n", c);
}