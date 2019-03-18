// Greg Wagner
// Project 3
// program that links to p3test to perform p3test on a set of integers and return the largest return code,
// should gain linear speed up time with an increase in threads

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
//#include <time.h>

typedef struct
{
    int begin, end;
} subrange;

void* sub(void *arg);
int p3test(int);

pthread_mutex_t m;
int highArg = 0;
int highRc = 0;

int main(int argc, char *argv[])
{
    int MAXARG, i, rc, r, temp; //MAXARG is max number going in, rc is return code, r is remainder
                                                 //high Arg/Rc are the arg and rc of the highest rc
    if ((atoi(argv[1]) > 4) || (atoi(argv[1]) < 1))
    {
	printf("cannot have %d threads, must be 1 to 4...\n",atoi(argv[1]));
	exit(1);
    }

    subrange subs[atoi(argv[1])];
    //pthreads = argv[1];
    MAXARG = atoi(argv[2]);
    pthread_t thrdid[atoi(argv[1])];
    
    alarm(60);
    
    pthread_mutex_init(&m, NULL);

    // break up MAXARG into sub ranges, ideal range size is (MAXARG/argv[1])
    temp = 0;
    r = MAXARG % atoi(argv[1]);
    for (i=0; i < atoi(argv[1]); i++)
    {
	temp++;
	subs[i].begin = temp;
	temp += ((MAXARG/atoi(argv[1]))-1);
	if (r > 0)
	{
	    temp++;
	    r--;
	}
	subs[i].end = temp;
    }

//    printf("I have splt the ranges, and am ready to pass to my threads\n\n");
    
    for (i=0; i < atoi(argv[1]); i++)
    {
        rc = pthread_create(&thrdid[i],NULL,sub,(void *)&subs[i]);
    }

    for (i=0; i < atoi(argv[1]); i++)
    {
        pthread_join(thrdid[i],NULL);
    }

    printf("highest arg: %d rc: %d\n",highArg,highRc);
  
    return 0;
}

void* sub(void *arg)
{
    int i,start,finish,tmp1,tmp2,rc;
    tmp1 = 0;
    subrange tsub = *(subrange *)arg;
    start = tsub.begin;
    finish = tsub.end;

    //printf("I am thread %d in unix process %d\nstart: %d finish: %d\n",i, getpid(),start,finish);

    for (i = start; i <= finish ; i++)

    {
	rc = p3test(i);
	if (rc > tmp1) 
	{
	    tmp1 = rc;
	    tmp2 = i;
	}
    }

    pthread_mutex_lock(&m);
    if (tmp1 > highRc)
    {
	highRc = tmp1;
	highArg = tmp2;
    }
    pthread_mutex_unlock(&m);
}
