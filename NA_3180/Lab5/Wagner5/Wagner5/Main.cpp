// Greg Wagner
// Intro to Numerical Analysis - 3180
// Due: Feb 19, 2019
// Lab 5 - Interpolation
// This program implements a Divided Difference Table and Expression of a
// requested number of data points for Newton Interpolation based on the 
// function, f(x)=1/(x^2 +1). It then evaluates the interpolant P(x) vs the 
// f(x) values to check for correctness. 
// Input: numbers of points(p), x values x[p]
// Output: iteration number, x, f(x), p(x), error

#define _CRT_SECURE_NO_DEPRECATE // for system(pause)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

double f(double);
void divDif(std::vector<double> * xs, std::vector<double> * ys,
	double(*f)(double), int n);
double evalNewInter(std::vector<double> *a, std::vector<double> *x,
	int n, double t);

void main() {
	int i, p, t; //every program has an i, p is number of points for interpolant, t is test points
	double tmp, tmp2;
	std::vector<double> xVals;  // it is wiser to use vectors over arrays
	std::vector<double>	ddVals;	// bc of memory alloc overhead
	std::vector<double> test;

	FILE *datafile = fopen("data.csv", "w+"); // to make generating 
	if ((datafile == NULL)) {                 // a data table easy in the report
		printf("Could not open the file\n");
	}

	printf("How many data points? ");
	scanf("%d", &p);
	printf("Enter x values seperated by spaces: ");
	for (i = 0; i < p; i++) {
		scanf(" %lf", &tmp);
		xVals.push_back(tmp);
	}

	divDif(&xVals, &ddVals, f, p);

	printf("How many test values? ");
	scanf(" %d", &t);
	printf("Enter all X values seperated by spaces: ");
	for (i = 0; i < t; i++) {
		scanf(" %lf", &tmp);
		test.push_back(tmp);
	}

	printf(" i | Xi |%10s      |%10s     |%15s\n", "f(Xi)", "P(Xi)",
		"|f(Xi)-P(Xi)|");
	fprintf(datafile, "i,Xi,f(Xi),P(Xi),|f(Xi)-P(Xi)|\n");
	for (i = 0; i < 57; i++)
		printf("-");
	printf("\n");

	for (i = 0; i < t; i++) {
		tmp = f(test.at(i));
		tmp2 = evalNewInter(&ddVals, &xVals, p, test.at(i));
		printf("%2d%5.0lf%16.10lf%16.10lf%18.10lf\n", i, test.at(i), tmp, tmp2, fabs(tmp2 - tmp));
		fprintf(datafile, "%d,%5.0lf,%16.10lf,%16.10lf,%18.10lf\n",
			i, test.at(i), tmp, tmp2, fabs(tmp2 - tmp));
	}

	fclose(datafile);
	system("pause");
}

double f(double x) {
	return 1 / ((x) * (x) + 1);
}

void divDif(std::vector<double> * xs, std::vector<double> * ys,
	double (*f)(double), int n) {
	int i, j;

	printf("Divided Differences\n");

	for (double it : *xs)
		ys->push_back((*f)(it));

	for (j = 0; j < n; j++) {
		if (j > 0) {
			for (i = n-1; i >= j; i--) {
				ys->at(i) = (ys->at(i) - ys->at(i - 1)) / (xs->at(i) - xs->at(i - j));
			}
		}
		printf("\nIteration %d:\n", j);
		for (double it : *ys)
			printf("%13.10lf\n", it);
	}
}

// evaluate a newton interpolate from vectors of x and y values
// where the y vector contains
double evalNewInter(std::vector<double> *a, std::vector<double> *x,
	int n, double t) {
	double v = a->at(n-1);
	for (int i = n - 2; i >= 0; i--) {
		v = v * (t - x->at(i)) + a->at(i);
	}
	return v;
}