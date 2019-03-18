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
   
    fd = open("tempin", O_RDONLY);
    printf("rc from open %d\n",fd);

    n = read(fd, buff, 8);

    for (i=0; i < 8; i++)
    {
        printf("%02x ",buff[i]);
    }
    printf("\n");
}
