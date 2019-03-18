

/*shared2.c*/


#include <stdio.h>
#include <omp.h>
int main()
{
	int A[3][3] = {1, 2, 3,
			4, 5, 6,
			7, 8, 9};
	int B[3][3] = {9, 8, 7,
			6, 5, 4,
			3, 2, 1};
	int C[3][3];
	int row,i,j;

	#pragma omp parallel private(row) num_threads(3)
	{
		omp_set_nested(1);
		row = omp_get_thread_num();
		#pragma omp parallel shared(row) num_threads(3)
		{
			int col = omp_get_thread_num();
			printf("thread %d calculating row %d col %d\n",col,row,col);
			C[row][col] = A[row][col]+B[row][col];
		}
	}

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%d ",C[i][j]);
		printf("\n");
	}
	return 0;
}		
