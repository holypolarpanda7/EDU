/*barrier.c*/


#include <stdio.h>
#include <omp.h>
int main()
{
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int i,j;
		int x=0;
		for(i=0;i<3;i++)
		{
			printf("first %d %d\n",id,i);
			for(j=0;j<1000;j++)
				x++;
		}
		#pragma omp barrier
		for(i=0;i<3;i++)
		{
			printf("second %d %d\n",id,i);
			for(j=0;j<1000;j++)
				x++;
		}
	}
	return 0;
}	
