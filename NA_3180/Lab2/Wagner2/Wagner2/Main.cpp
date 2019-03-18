// Greg Wagner
// Intro to Numerical Analysis - 3180
// Due: Jan 29, 2019
// Lab 2 - Differentiation
// This program implements three functions that approximate the derivative of "sin x" using three different methods representing 
// backward, foward , and centered difference formulas 
// Input: x(radians), n(numer of iterations), Analytical Solution
// Output: iteration number, value found for iteration, error

#define _CRT_SECURE_NO_DEPRECATE // for system(pause)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double forward(double *, double *);
double backward(double *, double *);
double centered(double *, double *);

void main() {
	int i,it;
	double ans, appr, h, x, err;
	
	FILE *datafile = fopen("data.csv", "w+"); // to make generating 
	if ((datafile == NULL)) {                 // a data table easy in the report
		printf("Could not open the file\n");
	}

	h = 1; // initial step size

	printf("Enter x in radians: ");
	scanf("%lf", &x);

	printf("Enter the number of iterations: ");
	scanf("%d", &it);

	// the analytical solution is found with the math lib instead of entered as input
	// the derivative of sin is cos
	printf("Analytical solutions: ");
	ans = cos(x);
	printf("%06.8f\n", ans);

	// for the number of iterations make a new approximation as h gets smaller and smaller
	// and do so for each method of approximation
	printf("\ni          h           value          error\n");
	fprintf(datafile, " ,Forward Difference\ni,h,value,error\n");
	for (i = 0; i < it; i++) {
		h = h*0.25;
		appr = forward(&x, &h);
		err = fabs(ans - appr);
		printf("%02d   %12.10f   %12.10f   %12.10f\n", i, h, appr, err);
		fprintf(datafile, "%02d,%12.10f,%12.10f,%12.10f\n", i, h, appr, err);
	}

	h = 1;
	printf("\ni          h           value          error\n");
	fprintf(datafile, " ,Backward Difference\ni,h,value,error\n");
	for (i = 0; i < it; i++) {
		h = h*0.25;
		appr = backward(&x, &h);
		err = fabs(ans - appr);
		printf("%02d   %12.10f   %12.10f   %12.10f\n", i, h, appr, err);
		fprintf(datafile, "%02d,%12.10f,%12.10f,%12.10f\n", i, h, appr, err);
	}

	h = 1;
	printf("\ni          h           value          error\n");
	fprintf(datafile, " ,Centered Difference\ni,h,value,error\n");
	for (i = 0; i < it; i++) {
		h = h*0.25;
		appr = centered(&x, &h);
		err = fabs(ans - appr);
		printf("%02d   %12.10f   %12.10f   %12.10f\n", i, h, appr, err);
		fprintf(datafile, "%02d,%12.10f,%12.10f,%12.10f\n", i, h, appr, err);
	}

	fclose(datafile);
	system("pause"); // this is why i dont like VS
}

double forward(double * point, double * ech) {
	double sol;
	
	// f(x) = sin x
	// sol = (f(x+h)-f(x))/h
	sol = (sin(*point + *ech) - sin(*point)) / *ech;

	return sol;
}

double backward(double * point, double * ech) {
	double sol;

	// f(x) = sin x
	// sol = (f(x-h)-f(x))/h
	sol = (sin(*point) - sin(*point - *ech)) / *ech;

	return sol;
}

double centered(double * point, double * ech){
	double sol;

	// f(x) = sin x
	// sol = (f(x-h)-f(x+h))/h
	sol = (sin(*point + *ech) - sin(*point - *ech)) / (2 * (*ech));

	return sol;
}