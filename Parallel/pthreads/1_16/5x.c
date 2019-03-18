/*Simple threaded program with five threads that
  change the value of every fifth location in an
  shared array.  The parent prints the array
  BUT there is a huge problem here.
*/
#include <pthread.h>
#include <stdio.h>
int arr[10]={2,2,2,2,2,2,2,2,2,2};
int howmany = 5;
void * fillArray(void *x)
{
	int mystart = *(int *)x;
	int i;
	for(i=0;i<10;i++)
		arr[i] = mystart;
}

int main()
{
	pthread_t id[howmany];
	int args[howmany];
	int i;
	printf("arr before threads\n");
	for(i=0;i<10;i++)
		printf("%d ", arr[i]);
	printf("\n");

	for(i=0;i<howmany;i++)
	{
		args[i] = i;
		pthread_create(&id[i],NULL,fillArray,(void *)&args[i]);
	}

	for(i=0;i<howmany;i++)
		pthread_join(id[i],NULL);

	printf("arr after threads\n");
	for(i=0;i<10;i++)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}	
