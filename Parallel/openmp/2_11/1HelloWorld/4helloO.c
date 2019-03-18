#include <stdio.h>
#include <omp.h>

int main()
{
	#pragma omp parallel num_threads (10)
		printf("Hello World from thread %d\n",omp_get_thread_num());
		
	return 0;
}
