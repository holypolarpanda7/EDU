// Greg Wagner
// Computer Systems
// p1 - compares the binary data of two files (as 2 sys args) and finds the location of the first different byte
// use xxd "filename" and cmp "filename" "filename" linux cammands to check work  *hacked from p1demo2.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i, n1, n2, fd1, fd2;
    unsigned char buff1[128];
    unsigned char buff2[128];

    fd1 = open(argv[1], O_RDONLY);
    //printf("rc from open %d\n",fd1);
    //fprintf(stderr,"rc from open %d\n",fd1);
   
    fd2 = open(argv[2], O_RDONLY);
    //printf("rc from open %d\n",fd2);
    //fprintf(stderr,"rc from open %d\n",fd2);

    n1 = read(fd1, buff1, 1);
    n2 = read(fd2, buff2, 1);

    i = 0;
    while ((n1 > 0) && (n2 > 0))
    {
/*	printf("%d : %02x %02x   ",i,buff1[0],buff2[0]);
	if ((i+1)%8 == 0) printf("\n");*/
	if (buff1[0] != buff2[0] && n1 == n2)
	{
	    printf("%d: 0x%02x 0x%02x\n",i,buff1[0],buff2[0]);
	    break;
	}

	n1 = read(fd1, buff1, 1);
	n2 = read(fd2, buff2, 1);
	i++;
	//printf("n1 = %d n2 = %d\n",n1,n2);

	if ((n1 == 0) && (n2 != 0)) printf("%d: EOF 0x%02x\n",i,buff2[0]);
	else if ((n2 == 0) && (n1 != 0)) printf("%d: 0x%02x EOF\n",i,buff1[0]);
	else if ((n1 == 0) && (n2 ==0)) printf("SAME\n");
  }
}
