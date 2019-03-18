


/*master.c*/
#include <omp.h>

#include <stdio.h>
int main()
{
	int i,j;
	#pragma omp parallel private (i,j) num_threads (3)
	{
		int id=omp_get_thread_num();
		for(j=0;j<1000;j++)
			if(j%500 == 0) printf("before master %d %d\n",id,j);
		#pragma omp master 
		{
			for(i=0;i<1000;i++)
				if(i%500 == 0) printf("****inside master %d %d\n",id,i);
		}
		for(j=0;j<1000;j++)
			if(j%500 == 0) printf("!!!!after master %d %d\n",id,j);
	}
	return 0;
}
		
