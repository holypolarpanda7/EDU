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

double f1(double, double);
double f2(double, double);
double f3(double, double);
double f4(double, double);
double Euler(int n, double h, double xi, double ti, int c, FILE *p);
double Heun(int n, double h, double xi, double ti, int c, FILE *p);
double RKutta(int n, double h, double xi, double ti, int c, FILE *p);

void main() {
	int c;
	double sol, lb, ub, iv, n, h, err, appr;
	
	FILE *fp = fopen("data.csv", "w+"); // to make generating 
	if ((fp == NULL)) {                 // a data table easy in the report
		printf("Could not open the file\n");
	}

	// request all information about the ODE to be numerically analyzed
	printf("Which ODE would you like to use?\n");
	printf("1. x' = x / (1 + t)\n2. x = t + x\n3. x = t - x\n4. x = (t - x) / (t + x)\n");
	printf("Choice: ");
	scanf(" %d", &c);

	printf("Enter the analytical solution: ");
	scanf(" %lf", &sol);

	printf("Enter the lower bound of the interval (a): ");
	scanf(" %lf", &lb);

	printf("Enter the upper bound of the interval (b): ");
	scanf(" %lf", &ub);

	printf("Enter the initial value: ");
	scanf(" %lf", &iv);

	printf("Enter the number of sub intervals: ");
	scanf(" %lf", &n);

	h = (ub - lb) / n;

	appr = Euler(n, h, iv, lb, c,fp);
	err = fabs((sol - appr)/sol);
	printf("Relative Error:%15.10lf\n", err);
	fprintf(fp, "Relative Error,%15.10lf\n", err);

	appr = Heun(n, h, iv, lb, c,fp);
	err = fabs((sol - appr) / sol);
	printf("Relative Error:%15.10lf\n", err);
	fprintf(fp, "Relative Error,%15.10lf\n", err);

	appr = RKutta(n, h, iv, lb, c,fp);
	err = fabs((sol - appr) / sol);
	printf("Relative Error:%15.10lf\n", err);
	fprintf(fp, "Relative Error,%15.10lf\n", err);
	

	fclose(fp);
	system("pause"); // this is why i dont like VS
}

double f1(double x, double t) {
	return (x / (1 + t));
}

double f2(double x, double t) {
	return (t + x);
}

double f3(double x, double t) {
	return (t - x);
}

double f4(double x, double t) {
	return ((t - x) / (t + x));
}

double Euler(int n, double h, double xi, double ti, int c, FILE *p) {
	double x = xi, t = ti;
	int j;
	printf("\n    Euler's Method\n");
	fprintf(p, "\n ,Euler's Method\n");
	if (c == 1) {
		for (j = 0; j < n; j++) {
			x = x + (h * f1(x, t));
			t = t + h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x); 
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else if (c == 2) {
		for (j = 0; j < n; j++) {
			x = x + (h * f2(x, t));
			t = t + h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x); 
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else if (c == 3) {
		for (j = 0; j < n; j++) {
			x = x + (h * f3(x, t));
			t = t + h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else {
		for (j = 0; j < n; j++) {
			x = x + (h * f4(x, t));
			t = t + h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}

	printf("%-18.10lf%-15.10lf\n", t, x);
	fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
	return x;
}

double Heun(int n, double h, double xi, double ti, int c, FILE *p) {
	double x = xi, t = ti, xp;  // x and t initial and a value for 
	int j;							// intermediate x
	printf("\n    Heun's Method\n");
	fprintf(p, "\n ,Heun's Method\n");
	if (c == 1) {
		for (j = 0; j < n; j++) {
			xp = x + (h * f1(x, t));
			x = x + ((h / 2) * (f1(x, t) + f1(xp, (t + h))));
			t = t + h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x); 
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else if (c == 2) {
		for (j = 0; j < n; j++) {
			xp = x + (h * f2(x, t));
			x = x + ((h / 2) * (f2(x, t) + f2(xp, (t + h))));
			t = t + h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else if (c == 3) {
		for (j = 0; j < n; j++) {
			xp = x + (h * f3(x, t));
			x = x + ((h / 2) * (f3(x, t) + f3(xp, (t + h))));
			t = t + h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else {
		for (j = 0; j < n; j++) {
			xp = x + (h * f4(x, t));
			x = x + ((h / 2) * (f4(x, t) + f4(xp, (t + h))));
			t = t + h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}

	printf("%-18.10lf%-15.10lf\n", t, x);
	fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
	return x;
}

double RKutta(int n, double h, double xi, double ti, int c, FILE *p) {
	double x = xi, t = ti, ta = ti, k1,k2,k3,k4; // inital x and t
	int j;								// k1-4 for rkutta methode 
	printf("\n    Runge-Kutta Method\n");
	fprintf(p, "\n ,Runge-Kutta Method\n");
	if (c == 1) {
		for (j = 1; j <= n; j++) {
			k1 = h * f1(x, t);
			k2 = h * f1((x + 0.5*k1), (t + 0.5*h));
			k3 = h * f1((x + 0.5*k2), (t + 0.5*h));
			k4 = h * f1((x + k3), (t + h));
			x = x + ((k1 + 2 * k2 + 2 * k3 + k4)/6);
			t = ta + j*h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else if (c == 2) {
		for (j = 1; j <= n; j++) {
			k1 = h * f2(x, t);
			k2 = h * f2((x + 0.5*k1), (t + 0.5*h));
			k3 = h * f2((x + 0.5*k2), (t + 0.5*h));
			k4 = h * f2((x + k3), (t + h));
			x = x + ((k1 + 2 * k2 + 2 * k3 + k4) / 6);
			t = ta + j*h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else if (c == 3) {
		for (j = 1; j <= n; j++) {
			k1 = h * f3(x, t);
			k2 = h * f3((x + 0.5*k1), (t + 0.5*h));
			k3 = h * f3((x + 0.5*k2), (t + 0.5*h));
			k4 = h * f3((x + k3), (t + h));
			x = x + ((k1 + 2 * k2 + 2 * k3 + k4) / 6);
			t = ta + j*h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}
	else {
		for (j = 1; j <= n; j++) {
			k1 = h * f4(x, t);
			k2 = h * f4((x + 0.5*k1), (t + 0.5*h));
			k3 = h * f4((x + 0.5*k2), (t + 0.5*h));
			k4 = h * f4((x + k3), (t + h));
			x = x + ((k1 + 2 * k2 + 2 * k3 + k4) / 6);
			t = ta + j*h;
			if (j < 9) { 
				printf("%-18.10lf%-15.10lf\n", t, x);
				fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
			}
		}
	}

	printf("%-18.10lf%-15.10lf\n", t, x);
	fprintf(p, "%-18.10lf,%-15.10lf\n", t, x);
	return x;
}