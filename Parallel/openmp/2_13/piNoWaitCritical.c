

/*OpenMP pi program with nowait and critical*/


#include <stdio.h>
#include <omp.h>
int num_steps = 16; 
float step; 
int main () 
{ 
	int i; 
	float x, pi, sum = 0.0; 
	float mysum;
	float first,mid;

	step = 1.0/(double) num_steps; 
	#pragma omp parallel private(first,mid,mysum,x) 
	{

		#pragma omp for nowait 
			for(i=0;i<num_steps;i++)
			{
				first = i*step;
				mid = first + step/2.0;
				if(mid > num_steps)
					mid = (first + num_steps)/2.0;

				mysum = step*4.0/(1.0+mid*mid); 
				printf("%d %f\n",i,mysum);
			}
		#pragma omp critical
		{
			printf("inside critical %d\n",omp_get_thread_num());
			sum += mysum;
		}
	}
	printf("%f\n",sum);
	return 0;
}
