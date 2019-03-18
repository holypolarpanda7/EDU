/* Example:  Integration using the rectangular rule
   Author:  Dr. Pettey
   Date:  February 4, 2016
   Purpose:  To calculate the area under the curve
              sqrt(4-x*x)
             from 0 to 2
             Using the rectangular rule
             There are no more than 50 partitions.
*/     

/*need the thread library for threads and the math
  library for the sin function */
#include <stdio.h>
#include <pthread.h>
#include <math.h>

/*const int NUM = 100000;*/
const int NUM = 32751;
//const int NUM = 32752;
float width;                /* the width of a segment*/
float rsum = 0.0;           /* the trapezoidal result*/
pthread_mutex_t mutex1;     /* mutual exclusion variable for simpsons*/

/*Calculate one segment of the area using the rectangular rule*/
void *rectangular(void *mine)
{
	float partial_sum = 0.0;      /*area under my segment*/
	int me = *((int *)mine);      /*which segment is mine */
	double height;		      /*height of rectangle */
	double mid;		      /* midpoint of my segment */
	
	/* find my mid point */
	mid = me*width + width/2.0;

	/*calculate the height of the curve at each x value*/
	height = sqrt(4.0 - mid*mid);
	
	/*calculate the area in my segment*/
	partial_sum = height*width;
		
        /*increment the global area*/
	pthread_mutex_lock(&mutex1);
		rsum += partial_sum;
	pthread_mutex_unlock(&mutex1);

}


/************************begin main***********************/
int main()
{
	int no_processes;                    /*number of threads/segments*/
	int i;                               /*loop variable*/
	int is[NUM];                          /*array for designating segment numbers*/
	pthread_t threadr[NUM];               /*thread id array */

	/*initialize mutual exclusion variables*/
	pthread_mutex_init(&mutex1,NULL);

	/*determine the number of partitions...which is the number of threads*/
    /*
	printf("input the number of partitions\n");
	scanf("%d",&no_processes);
	if(no_processes > 50)
	{
		printf("number must be <= %d\n",NUM);
		return(0);
	}
    */
    no_processes = NUM;

	/*the width is the same for each segment so make it global*/
	width = 2.0/no_processes;

	/*create threads*/
	for(i=0;i<no_processes;i++)
	{
		is[i]=i;
		if(pthread_create(&threadr[i],NULL,rectangular,(void *)&is[i]) != 0)
			perror("Pthread_create fails");
	}

	/*wait for all threads*/
	for(i=0;i<no_processes; i++)
		if (pthread_join(threadr[i],NULL) != 0)
			perror("Pthread_join fails");


	/*print the area for each*/
	printf("The area under the curve is %f\n",rsum);

	return(0);
}
