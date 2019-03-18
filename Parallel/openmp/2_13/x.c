

/*OpenMP pi program with for and critical*/


#include <stdio.h>
int num_steps = 32; 
float step; 
int main () 
{ 
	int i; 
	float x, pi, sum = 0.0; 
	float mysum;
	float first,mid;

	step = 1.0/(double) num_steps; 
			for(i=0;i<num_steps;i++)
			{
				first = i*step;
				mid = first + step/2.0;
				if(mid > num_steps)
					mid = (first + num_steps)/2.0;

				mysum = step*4.0/(1.0+mid*mid); 
				printf("%d %f\n",i,mysum);
			sum += mysum;
		}
	}
	printf("%f\n",sum);
	return 0;
}
