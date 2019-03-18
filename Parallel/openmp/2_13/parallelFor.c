

/*parallelFor.c*/


#include <stdio.h>
#include <omp.h>
int main()
{

	#pragma omp parallel num_threads(16)
	{
		int i;
		int me = omp_get_thread_num();
		#pragma omp for
		for(i=0;i<10;i++)
			printf("loop var %d from thread %d\n",i,me);
	}
	return 0;
}	
