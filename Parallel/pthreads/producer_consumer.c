#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>

int job;
int job_available;
pthread_mutex_t job_queue_lock = PTHREAD_MUTEX_INITIALIZER;

void * producer (void * ignored)
{
	int jobqueue[3] = {20, 8, 1};;
	int i = 0;
	int lockStatus;
	
	while (i < 3)
	{
	    lockStatus = pthread_mutex_trylock(&job_queue_lock);
	    if(lockStatus != 0)
		printf("can't get lock\n");
	    else
		if(job_available == 0)
		{
			job_available++;
			job = jobqueue[i];
			printf("producing job %d with value %d in queue\n",i,job);
/*			sleep(1);
*/
	    pthread_mutex_unlock(&job_queue_lock);
			i++;
		}
		else
		{
			printf("queue full can't produce\n");
	    pthread_mutex_unlock(&job_queue_lock);
		}
	}

	pthread_exit(0);
}

void * consumer (void * ignored)
{
	int count = 0;
	int lockStatus;
	
	while (count < 3)
	{
	    lockStatus = pthread_mutex_trylock(&job_queue_lock);
	    if (lockStatus != 0)
	      printf("consumer can't get lock\n");
	    else
	      if(job_available == 1)
   	      {
		job_available--;
		printf("consuming job %d with value %d\n",count, job);
		count++;
	    pthread_mutex_unlock(&job_queue_lock);
/*		sleep(1);
*/
	      }
	      else
	      {
		printf("queue empty can't consume\n");
	    pthread_mutex_unlock(&job_queue_lock);
	      }
	}

	pthread_exit(0);
}

int main()
{
	pthread_t produce, consume;

	job_available = 0;
	pthread_create(&produce, NULL, producer, NULL);
	pthread_create(&consume, NULL, consumer, NULL);
	pthread_join(produce,NULL);
	pthread_join(consume,NULL);

	return 0;
}
