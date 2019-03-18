/*O'Reilly's Pthreads Programming by Nichols, Buttlar and Farrell  
  threaded program that does the same as simple.c*/

/*simple pthread program*/
#include <stdio.h>
#include <pthread.h>

int r1=0;
int r2=0;
void *do_one(void *pnum)
{
	int *test = (int *)pnum;
	int i, j, x;
	for(i=0;i<4;i++)
	{
		printf("doing one thing\n");
		for(j=0;j<10000;j++) x = x + i;
		(*test)++;
	}
}

void *do_another(void *pnum)
{
	int *test = (int *)pnum;
	int i,j,x;
	for(i=0;i<4;i++)
	{
		printf("doing another thing\n");
		for(j=0;j<10000;j++) x = x + i;
		(*test)++;
	}
}

void do_wrap(int onetime,int anothertime)
{
	int total;
	total = onetime + anothertime;
	printf("wrap: one time %d, another time %d, total %d\n",onetime,anothertime,total);
	return;
}

int main()
{
	pthread_t id1,id2;

	pthread_create(&id1,NULL,do_one,(void *)&r1);
	pthread_create(&id2,NULL,do_another,(void *)&r2);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	do_wrap(r1,r2);
	return 0;
}	
