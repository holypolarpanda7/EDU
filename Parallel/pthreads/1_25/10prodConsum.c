/*Author:  Chrisila Pettey
//Date:  2/9/16
//Purpose:  Small demonstration of how not to do Pthreads mutex 
//		using producer-consumer
//		concept.  Producer puts 3 items to the job queue.
//		Consumer consumes them.  Queue only holds one item at a time.
//		This program locks too much of the code, making it
//		close to sequential.
//Note:  Strange indentation to show locations of locks and matching
//		unlocks
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int jobqueue;
int job_available;
pthread_mutex_t job_queue_lock = PTHREAD_MUTEX_INITIALIZER;

void * producer (void * ignored)
{
	int myjobs[3] = {20, 8, 1};;
	int i = 0;
	
	while (i < 3)
	{
	    pthread_mutex_lock(&job_queue_lock);
		if(job_available == 0)
		{
			job_available++;
			jobqueue = myjobs[i];
			printf("producing job %d with value %d\n",i, jobqueue);
			sleep(1);
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
	
	while (count < 3)
	{
	    pthread_mutex_lock(&job_queue_lock);
	      if(job_available == 1)
   	      {
		job_available--;
		printf("consuming job %d with value %d\n", count, jobqueue);
		count++;
	    pthread_mutex_unlock(&job_queue_lock);
		sleep(1);
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
