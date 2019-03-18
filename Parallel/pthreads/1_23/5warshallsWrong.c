/*
   name:  Dr. Pettey
   date:  2/9/16
   purpose:  To calculate the reachability matrix for a 5X5 matrix
             using Warshalls algorithm.  There will be one thread per
             row.
*/
#include <stdio.h>
#include <pthread.h>

int x[5][5] = { 0,1,0,0,0,	//hard code a matrix to work with :-)
		0,0,1,0,0,
		0,0,0,1,0,
		0,0,0,0,1,
		1,0,0,0,0};

pthread_mutex_t  mv;		//mutex variable
pthread_cond_t   cv;		//condition variable

int numthreads = 5;
int donethreads = 0;

/*A thread calculates its row for each iteration of the Warshall's process*/
void * slave (void * arg)
{
	int me = *((int *)arg);
	int i,j,k;

	for (i = 0;i<5;i++)
	{
		if( (me != i) && (x[me][i] == 1))
		{
			for(j=0;j<5;j++)
				x[me][j] = x[me][j] || x[i][j]; 
		}

	}
}

int main()
{
	pthread_t ids[5];
	int i,j,is[5];

	pthread_mutex_init(&mv,NULL);
	pthread_cond_init(&cv,NULL);

	/*create threads*/
	for(i=0;i<5;i++)
	{
		is[i] = i;
		pthread_create(&ids[i],NULL,slave,(void *) &is[i]);
	}

	/*wait for threads*/
	for(i=0;i<5;i++)
	{
		pthread_join(ids[i],NULL);
	}

	/*output answer*/
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			printf("%d ",x[i][j]);
		printf("\n");
	}
	return 0;
}
