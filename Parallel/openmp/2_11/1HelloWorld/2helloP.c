#include <stdio.h>
#include <pthread.h>

void * hello (void * mine)
{
	int me = *((int *)mine);

	printf("Hello World from thread %d\n",me);
	return;
}

int main()
{
	pthread_t id[7];
	int val[7] = {1,2,3,4,5,6,7};
	int i;

	for(i=0;i<7;i++)
		pthread_create(&id[i],NULL,hello,(void *) &val[i]);
	i=0;
	hello((void *)&i);
	for(i=0;i<7;i++)
		pthread_join(id[i],NULL);
	return 0;
}
