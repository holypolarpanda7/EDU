

/*fourth go around for sections*/


#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int main()
{
	#pragma omp parallel 
	{
	   printf("%d inside parallel\n",omp_get_thread_num());
	   #pragma omp sections nowait
	   {
		#pragma omp section
		{
			sleep(2);
			printf("inside section 1 thread number %d\n",omp_get_thread_num());
		}
		#pragma omp section
		{
			sleep(2);
			printf("inside section 2 thread number %d\n",omp_get_thread_num());
		}
		#pragma omp section
		{
			sleep(2);
			printf("inside section 3 thread number %d\n",omp_get_thread_num());
		}
		#pragma omp section
		{
			sleep(2);
			printf("inside section 4 thread number %d\n",omp_get_thread_num());
		}
	   }
	   printf("%d after section\n",omp_get_thread_num());
	}
	return 0;
}	
