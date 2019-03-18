

/*parallelNotfor.c*/


#include <stdio.h>
#include <omp.h>
int main()
{

	#pragma omp parallel num_threads(4)
	{
		int i;
		int me = omp_get_thread_num();
		for(i=0;i<10;i++)
			printf("loop var %d from thread %d\n",i,me);
	}
	return 0;
}	
