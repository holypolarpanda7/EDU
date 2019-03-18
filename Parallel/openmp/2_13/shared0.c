

/*shared0.c*/


#include <stdio.h>
#include <omp.h>
//int x=39;
int main()
{
	int x=42;	

	#pragma omp parallel shared(x) num_threads(3)
	{
		int me = omp_get_thread_num();

		printf("x is %d\n",x);
		#pragma omp barrier

		if(me==2) x = 77;

		printf("x is %d\n",x);

		#pragma omp barrier
		printf("x is %d\n",x);
	}
	return 0;
}
