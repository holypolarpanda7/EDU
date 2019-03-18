

/*second go around for sections*/


#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int main()
{
	#pragma omp parallel sections num_threads(2)
	{
		#pragma omp section
		{
			printf("inside section 1 thread number %d\n",omp_get_thread_num());
			sleep(1);
		}
		#pragma omp section
		{
			printf("inside section 2 thread number %d\n",omp_get_thread_num());
			sleep(1);
		}
		#pragma omp section
		{
			printf("inside section 3 thread number %d\n",omp_get_thread_num());
		}
		#pragma omp section
		{
			printf("inside section 4 thread number %d\n",omp_get_thread_num());
		}
		#pragma omp section
		{
			printf("inside section 5 thread number %d\n",omp_get_thread_num());
		}
	}
	return 0;
}	
