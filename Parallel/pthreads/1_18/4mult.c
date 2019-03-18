/*name:  Dr. Pettey
file:  multiply.c
date:  2/9/16
purpose:  To show how threads can access shared variables by doing a
		matrix multiply.  There is no possibility for 
		shared variable contention
*/
#include <stdio.h>
#include <pthread.h>


/*global variables are shared variables*/
int a[3][3],b[3][3],c[3][3];


/*Thread code for caluclating one row of the answer matrix*/
void *multiplyRow(void *mine)
{
	int myrow = *((int *)mine);  /*which row to calculate*/
	int i, j;		     /*loop variables*/
	for(i=0;i<3;i++)
	{
		c[myrow][i] = 0;
		for(j=0;j<3;j++)
			c[myrow][i] += a[myrow][j] * b[j][i];
	
	}
}

int main()
{
	pthread_t thread[3];  /*thread id array*/
	int id[3];	      /*array for thread arguments*/
	int i,j;	      /*loop variables*/

	/*read in the two arrays*/
	printf("input first 3X3 array\n");
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			scanf("%d", &a[i][j]);
	printf("input second 3X3 array\n");
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			scanf ("%d",&b[i][j]);

	/*create threads*/
	for(i=0;i<3;i++)
	{
		id[i] = i;	
		pthread_create(&thread[i],NULL, multiplyRow, (void *)&id[i]);
	}

	/*wait for threads to finish*/
	for(i=0;i<3;i++)
	{
		pthread_join(thread[i],NULL);
	}

	/*print answer created by threads*/
	printf( "the answer is\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%d  ",c[i][j]); 
		printf("\n");
	}

	return 0;
}

