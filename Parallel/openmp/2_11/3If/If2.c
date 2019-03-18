#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int main()
{
	//int is_parallel=1;
	int is_parallel = 0;
	int c=1;
	int b=7;
	int a=3;

	#pragma omp parallel if (is_parallel == 1) num_threads(8) \
				private (a) shared(b) firstprivate(c)
	{
		int me = omp_get_thread_num();
		sleep(1);
		printf("before assignments thread %d has %d %d %d\n",me,a,b,c);
		if(me == 1) b = 42;
		a = me;
		c = c + me;
		printf("after assignments thread %d has %d %d %d\n",me,a,b,c);
	}				
	return 0;
}
