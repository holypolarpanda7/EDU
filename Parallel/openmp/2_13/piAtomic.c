

/*openmp pi program with atomic operation*/


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
	#pragma omp parallel private(first,mid,mysum,x) shared (num_steps,step) num_threads (num_steps)
	{
		int id = omp_get_thread_num();
		first = id*step;
		mid = first + step/2.0;
		mysum = step*4.0/(1.0+mid*mid); 

		#pragma omp atomic
			sum += mysum;
	}
	printf("%f\n",sum);
	return 0;
}
