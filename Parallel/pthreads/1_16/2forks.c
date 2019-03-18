/*Modified O'Reilly's Pthreads Programming by Nichols, Buttlar and Farrell  
  heavy-weight concurrent program that does the same as simple.c */

/*example of unix fork */
#include <stdlib.h>  /*needed for exit(0)*/
#include <stdio.h>   /*needed for printf and scanf*/
#include <sys/shm.h>   /*includes definitions of all symbols from <sys/ipc.h>*/
		       /*also includes some type defs from <sys/types.h>*/

int shared_mem_id;
int *shared_mem_ptr;
int *r1;
int *r2;
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
	pid_t child1_pid, child2_pid; /*process ID type*/
	int status;

	/*get a shared memory segment big enough for two integers*/
	/*set permissions to read/write for user and group*/
	/*returns non-negative shared mem id initialize space to all 0's*/
	shared_mem_id = shmget(IPC_PRIVATE, 2*sizeof(int), 0660);

	/*attach the shared memory segment to address space of calling proc*/
	/*and return the start address of the location in memory*/
	shared_mem_ptr = (int *)shmat(shared_mem_id, (void *)0, 0);

	/*r1 is first location in shared mem, r2 is second location*/
	r1 = shared_mem_ptr;
	r2 = (shared_mem_ptr + 1);

	*r1 = 0;
	*r2 = 0;

	/*create a child proc that does do_one, then quits*/
	/*remember fork returns 0 to the child and positive num to parent*/
	/*child gets an exact copy of parent address space - sort of*/
	if((child1_pid = fork()) == 0)
	{
		do_one(r1);
		exit(0);
	}

	/*create a child proc that does do_another, then quits*/
	if((child2_pid = fork()) == 0)
	{
		do_another(r2);
		exit(0);
	}

	/*do not go on until the children finish*/
	waitpid(child1_pid,&status,0);
	waitpid(child2_pid,&status,0);

	/*once the children are done wrap up*/
	do_wrap(*r1,*r2);
	
	return 0;
}	
