// Greg Wagner
// Wagner1.cpp : Horner's Algorithm applied to higher degree polynomials.
// Input: polynomial attributes
// Output: polynomial evaluation
// Data Analysis - 3180
// Due: Jan 17,2019

#include <iostream>
using namespace std;

double horner(double a[], int n, double x);

int main()
{
	// initailize necessary vars
	int highDeg = 0; // highest degree of the polynomial
	double point = 0; // point around which to evaluate
	double eval; //final answer

				 // request polynomial degree
	cout << "Enter the degree of your polynomial? ";
	cin >> highDeg;

	// dynamically create coefficient array and load it with values
	double* coef = new double[highDeg + 1];
	for (int i = highDeg; i >= 0; i--) {
		if (i != 0) { cout << "\nCoefficient of x^" << i << "? "; }
		else { cout << "\nConstant Term? "; }
		cin >> coef[i];
	}

	// enter points to evaluate the polynomial at, 
	// entry of 1000 exits requests
	while (point != 1000) {
		cout << "\nEnter x at which to evaluate or 1000 to quit:   ";
		cin >> point;
		eval = horner(coef, highDeg, point);
		cout << "\np(" << point << ") = " << eval << '\n';
	}

	// prevent mem leak
	delete coef;
	return 0;
}

double horner(double a[], int n, double x) {
	// use horners scheme to evaluate
	// p(x)=a[n]+a[n-1]*x+a[n-2]*x^2+...+a[0]*x^n
	// return the value of p(x)
	double ans = 0;
	for (int i = n; i > 0; i--) {
		ans = (ans + a[i]) * x;
	}
	ans += a[0];
	return ans;
}