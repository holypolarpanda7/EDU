/* example of Pthread_Exit - or How do you return a value to the parent? */
/* Note the syntax for pthread_exit vs pthread_join
	void pthread_exit(void *retval);
	int pthread_join(pthread_t thread, void **retval);
*/
#include <stdio.h>
#include <pthread.h>

void *thread(void *none)
{
	long int k=42;
	pthread_exit((void *)k);
}

int main()
{
	long int i;
	pthread_t id;
	pthread_create(&id,NULL,thread,NULL);
	pthread_join(id, (void *)&i);
	printf("The answer of course is %d\n",i);
}
