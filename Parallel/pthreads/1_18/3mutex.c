/* Sample thread program to add the numbers in an array */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define array_size 1000
#define no_processes 10

int a[array_size];
int global_index = 0;
int sum = 0;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void *slave(void *ignored)
{
	int local_index, partial_sum = 0;
	do{
		pthread_mutex_lock(&mutex1);
			local_index = global_index;
			global_index++;
		pthread_mutex_unlock(&mutex1);
		if(local_index < array_size)
			partial_sum += *(a + local_index);
	} while (local_index < array_size);

	pthread_mutex_lock(&mutex2);
		sum += partial_sum;
	pthread_mutex_unlock(&mutex2);

	/*return();*/
}

main()
{
	int i;
	pthread_t thread[10];
	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);

	for(i=0;i<array_size;i++)
		a[i] = i+1;

	for(i=0;i<no_processes;i++)
		if(pthread_create(&thread[i],NULL,slave,NULL) != 0)
		{
			printf( "Pthread_create fails\n");
			exit(0);

		}
	for(i=0;i<no_processes; i++)
		if (pthread_join(thread[i],NULL) != 0)
		{
			printf("Pthread_join fails\n");
			exit(0);
		}

	printf("The sum of 1 to %d is %d\n",array_size, sum);
	return 0;
}
