

/*simple openMP section program*/


#include <stdio.h>
#include <omp.h>
int r1=0;
int r2=0;

void do_wrap(int onetime,int anothertime)
{
	int total;
	total = onetime + anothertime;
	printf("wrap: one time %d, another time %d, total %d\n",onetime,anothertime,total);
	return;
}

int main()
{
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			int i, j, x;
			for(i=0;i<4;i++)
			{
				printf("doing one thing\n");
				for(j=0;j<10000;j++) x = x + i;
				r1++;
			}
		}
		#pragma omp section
		{
			int i, j, x;
			for(i=0;i<4;i++)
			{
				printf("doing another thing\n");
				for(j=0;j<10000;j++) x = x + i;
				r2++;
			}
		}
	}
	do_wrap(r1,r2);
	return 0;
}	
