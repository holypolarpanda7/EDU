

/*single1.c*/


#include <stdio.h>
#include <omp.h>
int main()
{
	int i,j;
	#pragma omp parallel private (i,j) num_threads (3)
	{
		int id=omp_get_thread_num();
		#pragma omp single
		{
			for(i=0;i<1000;i++)
				if(i%500 == 0) printf("****inside single %d %d\n",id,i);
		}
		for(j=0;j<1000;j++)
			if(j%500 == 0) printf("!!!!after single %d %d\n",id,j);
	}
	return 0;
}
		
