

/*OpenMP pi program with reduction*/


#include <stdio.h>
#include <omp.h>
int num_steps = 32; 
float step; 
int main () 
{ 
	int i; 
	float x, pi, sum; 
	float mysum;
	float first,mid;

	step = 1.0/(double) num_steps; 
	#pragma omp parallel num_threads(4) private(first,mid,i) shared(step, num_steps) reduction(+:sum)
	{
		sum = 0;
		#pragma omp for
			for(i=0;i<num_steps;i++)
			{
				first = i*step;
				mid = first + step/2.0;
				sum += step*4.0/(1.0+mid*mid); 
				printf("%d %f\n",i,sum);
			}
	}
	printf("%f\n",sum);
	return 0;
}
