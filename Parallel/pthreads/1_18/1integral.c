/*Sequential program to calculate the integral
  sqrt(4-x*x) from 0 to 2 using retangular integration
  Author:  Dr. Pettey
  Date:  February 4, 2016
*/
#include <stdio.h>
#include <math.h>

int main()
{
	int i,nparts;
	float mid, width, height, area, sum;

	/* Read number of partitions*/
    /*
	printf("Input number of partitions ");
	scanf("%d",&nparts);
    */
    nparts = 32751;
	
	/* Calculate the width of each partition*/
	width = 2.0/nparts;

	/* Calculate the area of each partition and add to sum */
	sum = 0.0;
	for(i=0;i<nparts;i++)
	{
		mid = width*i+width/2.0;
		height = sqrt((double)4.0 - mid*mid);
		area = width*height;
		sum += area;
	}

	printf("The area under the curve is %f\n",sum);
	return 0;
}
			
