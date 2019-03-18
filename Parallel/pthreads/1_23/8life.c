/*name:  Dr. Pettey
//date:  9/28/09
//purpose:  This game plays 40 generations of John Conway's game of life
//        on a 20X20 board.  Edges are ignored.  Input is from the
//        file life.dat and is a single string of ' 's and '*'s
//        Additionally, there are four threads that compute the next
//        generation, but the main thread does all printing.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


/*Need one mutex variable and two condition variables (one for
//communicating between threads, and one for communicating with main).
*/
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t condM = PTHREAD_COND_INITIALIZER;

int num=0;        /*used to count number of threads that are done*/
int gennum=0;        /*also used to count number of done threads*/
int world[20][20];    /*the playing field*/

/*The thread routine.  Each thread is responsible for 4 or 5 rows
/*depending on the value of the argument which tells their start row.*/
void *update(void *mine)
{
    int me = *((int *)mine);    /*my start row*/
    int i,j,gen;            /*loop counters*/
    int count;            /*neighbor count for each position*/
    int myworld[20][20];        /*local array for efficiency and to*/
                    /*simplify computations*/

    /*run 40 generations*/
    for(gen = 0;gen < 40; gen++)
    {
        /*calculate my rows for this generation*/
        for(i=me;i<19;i+=4)
            for(j=1;j<19;j++)
            {
                myworld[i][j] = world[i][j];
                count = world[i-1][j-1] + world[i-1][j] + world[i-1][j+1];        
                count += (world[i][j-1] + world[i][j+1]);    
                count += (world[i+1][j-1] + world[i+1][j] + world[i+1][j+1]);        
                if(myworld[i][j])
                {
                    if((count < 2) || (count > 3)) myworld[i][j]--;
                }
                else
                    if(count == 3) myworld[i][j]++;
            }

        /*wait til all threads are finished calculating*/
        pthread_mutex_lock(&mut);
            num++;    
            if(num < 4)
                pthread_cond_wait(&cond,&mut);
            else
            {
                pthread_cond_broadcast(&cond);
                num = 0;
            }
        pthread_mutex_unlock(&mut);

        /*update the world with my new data*/
        for(i=me;i<19;i+=4)
            for(j=1;j<19;j++)
                world[i][j] = myworld[i][j];

        /*wait for the main thread to print*/
        pthread_mutex_lock(&mut);
            gennum++;    
            if(gennum < 4)
                pthread_cond_wait(&cond,&mut);
            else
            {
                pthread_cond_signal(&condM);
                pthread_cond_wait(&cond,&mut);
            }
        pthread_mutex_unlock(&mut);
    }
        
}

/*main thread*/
int main()
{
    pthread_t id[4];        /*There will be four threads*/
    int vals[4]={1,2,3,4};        /*The start rows*/
    int i,j;            /*loop variables*/
    int gen;            /*generation counter*/
    char c;                /*input character*/
    char outvals[2] = {' ','*'};    /*the two output values*/
    FILE *fp;

    /*open data file*/
    fp = fopen("life.dat", "r");

    /*Read in the datafile and create world (integer array)*/
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            world[i][j] = 0;
            fscanf(fp,"%c",&c);
            if (c == '*') world[i][j]++;
        }
        fscanf(fp,"%c",&c);
    }

    /*Print the initial data*/
    system("clear");
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
            printf("%c", outvals[world[i][j]]);
        printf("\n");
    }

    /*sleep so human eyes can see the action*/
    sleep(1);

    /*create four threads*/
    for(i=0;i<4;i++)
        pthread_create(&id[i],NULL,update,(void *)&vals[i]);

    /*play 40 generations*/
    for(gen=0;gen<40;gen++)
    {
        /*Wait til threads are done, then print, then wake them up*/
        pthread_mutex_lock(&mut);
            while(gennum < 4)
            pthread_cond_wait(&condM,&mut);    
                system("clear");
            for(i=0;i<20;i++)
            {
                for(j=0;j<20;j++)
                    printf("%c", outvals[world[i][j]]);
                printf("\n");
            }
            sleep(1);
            pthread_cond_broadcast(&cond); 
            gennum = 0;
        pthread_mutex_unlock(&mut);
    }

    /*join threads*/
    for(i=0;i<4;i++)
        pthread_join(id[i],NULL);
    return 0;
}    

