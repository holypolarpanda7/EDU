// Greg Wagner
// Lab 8: Numerical Integration Methods
// In this program three methods of numerical integration are used to find the integration of three seperate functions over specified intervals....
// f1(x) = (x^2 + 2)^-1 x:[0,1], f2(x) = x^-1 x:[1,2], f3(x) = 2^x x:[0,2]
// the three methods used are the trapezoidal rule, Simpson's Rule, and Richardson's Extrapolation
// Due: 4/12/2019
// Numerical Analysis CSCI ------

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <math.h>

double f1(double x);
double f2(double x);
double f3(double x);
double trap(double(*f)(double), int n, double a, double b);
double simpson(double(*f)(double), int n, double a, double b);
void Richardson(double * R, int n);

int main() {
	int i, j, c, n, subint;
	double l, u, ans, appr;
	double(*f)(double);
	double * R;
	FILE * fil = fopen("data.csv", "a");

	printf("Functions:\n 1: 1 / (x*x +2)\n 2: 1 / x\n 3: 2^x\n");
	printf("\nSelect a fun(Choose 1, 2, or 3...): ");
	scanf(" %d", &c);
	if (c == 1) {
		ans = 0.435209875683554;
		f = &f1;
	}
	else if (c == 2) {
		ans = 0.69314780559945;
		f = &f2;
	}
	else if (c == 3) {
		ans = 4.32808512266689;
		f = &f3;
	}
	else {
		printf("Not a valid choice!\n");
		system("Pause");
		return 0;
	}
	printf("Lower limit of integration: ");
	scanf(" %lf", &l);
	printf("Upper limit of integration: ");
	scanf(" %lf", &u);
	printf("Enter n, where 2^n is the number of subintervals: ");
	scanf(" %d", &n);
	printf("Exact value: %.15lf\n\n", ans);

	// dynamically allocate R[] according to n
	R = new double[n+1];
	if (!R)
	{
		printf("Memory allocation failed\n");
	}

	// run trapezoidal rule over the number of spec iterations
	printf("i%14s%20s\n", "T[i]", "ET[i]");
	fprintf(fil, "i,%14s,%20s\n", "T[i]", "ET[i]");
	for (i = 0; i <= n; i++) {
		subint = (int)pow(2, i);
		appr = trap(f, subint, l, u);
		R[i] = appr;
		printf("%d%20.15lf%20.15lf\n", i, appr, fabs(ans - appr));
		fprintf(fil, "%d,%20.15lf,%20.15lf\n", i, appr, fabs(ans - appr));
	}

	// run Richardson extrapolation over results from trapezoid rule
	Richardson(R, n);
	printf("\ni%14s%20s\n", "R[i]", "ER[i]");
	fprintf(fil, "\ni,%14s,%20s\n", "R[i]", "ER[i]");
	for (i = 1; i <= n; i++) {
		printf("%d%20.15lf%20.15lf\n", i, R[i], fabs(ans - R[i]));
		fprintf(fil, "%d,%20.15lf,%20.15lf\n", i, R[i], fabs(ans - R[i]));
	}

	// run simpson rule over number of specified iterations
	printf("\ni%14s%20s\n", "S[i]", "ES[i]");
	fprintf(fil, "\ni,%14s,%20s\n", "S[i]", "ES[i]");
	for (i = 1; i <= n; i++) {
		subint = (int)pow(2, i);
		appr = simpson(f, subint, l, u);
		R[i] = appr;
		printf("%d%20.15lf%20.15lf\n", i, appr, fabs(ans - appr));
		fprintf(fil, "%d,%20.15lf,%20.15lf\n", i, appr, fabs(ans - appr));
	}

	delete(R);
	system("Pause");
	return 0;
}

double f1(double x) {
	return 1 / (x * x + 2);
}

double f2(double x) {
	return 1 / x;
}

double f3(double x) {
	return powf(2, x);
}

// simple trapezoidal rule that uses math function, interval, and iterations
double trap(double(*f)(double), int n, double a, double b) {
	double sum = 0;
	double h = (b - a) / n;
	double x;
	int i;
	sum = (f(a) + f(b)) / 2;
	for (i = 1; i < n; i++) {
		x = a + i * h;
		sum = sum + f(x);
	}
	sum = sum * h;
	return sum;
}

// simple simpsions rule function that uses math function, interval, and iterations
double simpson(double(*f)(double), int n, double a, double b) {
	int i;
	double h = (b - a) / n;
	int sec = n / 2;
	double x0, x1, x2, appr = 0;

	for (i = 1; i <= sec; i++) {
		x0 = a + 2 * (i - 1) *h;
		x1 = x0 + h;
		x2 = x1 + h;
		appr = appr + f(x0) + 4 * f(x1) + f(x2);
	}

	appr = appr *h / 3;
	return appr;
}

// using The approximations made by our Trapezoidal Function we will use
// richardson extrapolation to find better approximations
void Richardson(double * R, int n) {
	int i, j;
	double * temp = new double[n+1];

	// now use previous trapezoidal appr to create better appr	
	for (j = 1; j <=n;j++){
		// for each iteration make the appr more accurate
		for (i = j; i <= n; i++) {
			temp[i] = R[i] + (R[i] - R[i - 1]) / (powf(4, j) - 1);
		}
		// avoiding 2d matrix so using temp to store temp solutions
		// then squish them back into original to be processed by next iter
		for (i = j; i < n + 1; i++) R[i] = temp[i];
	}
	delete(temp);
}