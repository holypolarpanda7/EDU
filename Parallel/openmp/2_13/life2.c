
/*life2.c*/


#include <stdio.h>
#include <omp.h>
int num=0;
int gennum=0;
int world[20][20];
int myworld[20][20];

int main()
{
	int i,j;
	int gen;
	char c;
	int me, count;
	char outvals[2] = {' ','*'};
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			world[i][j] = 0;
			c = getchar();
			if (c == '*') world[i][j]++;
		}
		c = getchar();
	}
	system("clear");
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
			printf("%c",outvals[world[i][j]]);
		printf("\n");
	}
	sleep(1);
	for(gen=0;gen<40;gen++)
	{
		#pragma omp parallel private (i,j,me,count) shared (world,myworld) num_threads (4)
		{
		    me = omp_get_thread_num();
		    me++;
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
		}
		#pragma omp parallel private (i,j,me) num_threads (4)
		{
			me = omp_get_thread_num();
			me++;
			for(i=me;i<19;i+=4)
				for(j=1;j<19;j++)
					world[i][j] = myworld[i][j];
		}
	    	system("clear");
		for(i=0;i<20;i++)
		{
			for(j=0;j<20;j++)
				printf("%c",outvals[world[i][j]]);
			printf("\n");
		}
		sleep(1);
	}

	return 0;
}	
