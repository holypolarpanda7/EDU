#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i, n, fd;
    unsigned char buff[1024];
   
    printf("fd of stdin %d\n", fileno(stdin));
    printf("fd of stdout %d\n", fileno(stdout));
    printf("fd of stderr %d\n", fileno(stderr));

    fd = open("tempin", O_RDONLY);
    printf("rc from open %d\n",fd);
    fprintf(stderr,"rc from open %d\n",fd);

    n = read(fd, buff, 8);
    printf("n %d\n",n);

    buff[8] = '\0';
    printf("%s\n",buff);

    for (i=0; i < strlen(buff); i++)
    {
        printf("%02x ",buff[i]);
    }
    printf("\n");
}
