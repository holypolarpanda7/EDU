
/*shared1a.c*/


#include <stdio.h>
#include <omp.h>
int main()
{
	int i,me;
	#pragma omp parallel private (i,me) default(none) num_threads(2)
	{
	    omp_set_nested(1);
	    i = omp_get_thread_num();
	    me = omp_get_thread_num();
	    printf("1:  i is %d my id is %d\n",i,me);
	    #pragma omp barrier
	    #pragma omp parallel num_threads(2)
	    {
		int me2;
		me2 = omp_get_thread_num();
		if(me == 0) i = 42;
		else i=7;
		printf("2:  i is %d me %d me2 %d\n",i,me,me2);
	    }
	    #pragma omp barrier
/*	    i = me;
*/
	    printf("3:  i is %d my id is %d\n",i,me);
	
	}

	return 0;
}	
			
