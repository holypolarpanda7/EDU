

/*OpenMP pi program using for and atomic*/


#include <stdio.h>
#include <omp.h>
int num_steps = 8; 
float step; 
int main () 
{ 
	int i; 
	float x, pi, sum = 0.0; 
	float mysum;
	float first,mid;

	step = 1.0/(double) num_steps; 
	#pragma omp parallel private(first,mid,mysum,x) num_threads(10) 
	{
		mysum = 0;
		#pragma omp for
			for(i=0;i<num_steps;i++)
			{
				first = i*step;
				mid = first + step/2.0;
				mysum += step*4.0/(1.0+mid*mid); 
				printf("%d %f\n",i,mysum);
			}
		#pragma omp atomic
			sum += mysum;
	}
	printf("%f\n",sum);
	return 0;
}
