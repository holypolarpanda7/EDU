/*example of simple threads doing matrix multiply*/
#include <stdio.h>
#include <omp.h>

int a[3][3],b[3][3],c[3][3];
int main()
{
	int i,j,row;
	printf("input a\n");
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			scanf("%d",&a[i][j]);
	printf("input b\n");
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			scanf("%d",&b[i][j]);

	#pragma omp parallel private (i,j,row)  num_threads (3)
	{
		row = omp_get_thread_num();
		for (i=0;i<3;i++)
		{
			c[row][i]=0;
	   		for(j=0;j<3;j++)
				c[row][i] += a[row][j]*b[j][i];
		}
	}
	printf("The answer is\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%d ",c[i][j]);
		printf("\n");
	}
	return 0;
}
