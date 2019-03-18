/*O'Reilly's Pthreads Programming by Nichols, Buttlar and Farrell
  sequential program that does two things four times each.*/
#include <stdio.h>
int r1=0;
int r2=0;
void do_one(int *pnum)
{
	int i, j, x;
	for(i=0;i<4;i++)
	{
		printf("doing one thing\n");
		for(j=0;j<10000;j++) x = x + i;
		(*pnum)++;
	}
	return;
}

void do_another(int *pnum)
{
	int i,j,x;
	for(i=0;i<4;i++)
	{
		printf("doing another thing\n");
		for(j=0;j<10000;j++) x = x + i;
		(*pnum)++;
	}
	return;
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
	do_one(&r1);
	do_another(&r2);
	do_wrap(r1,r2);
	return 0;
}	
