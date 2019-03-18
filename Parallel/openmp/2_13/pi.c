

/*openmp pi program*/


#include <stdio.h>
#include <omp.h>
int num_steps = 100; 
float step; 
int main () 
{ 
	int i; 
	float x, pi, sum = 0.0; 
	float mysum[num_steps];
	float first,mid;

	step = 1.0/(double)num_steps; 
	printf("step is %f\n",step);
	#pragma omp parallel private(first,mid,i,x) shared (num_steps,step,mysum) num_threads (num_steps)
	{
		int id = omp_get_thread_num();
		first = id*step;
		mid = first + step/2.0;
		mysum[id] = step*4.0/(1.0+mid*mid); 
		printf("%d %f\n",id,mysum[id]);
	}
	for(i=0;i<num_steps;i++)
		sum += mysum[i];
	printf("%f\n",sum);
	return 0;
}
