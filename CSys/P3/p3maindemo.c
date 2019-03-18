#include <stdio.h>
#include <unistd.h>

int p3test(int);

int main(int argc, char *argv[])
{
    int i, rc;

    alarm(60);

    // we will assume 101 is enough to find the max rc in this demo
    for (i=1; i < 101; i++)
    {
        rc = p3test(i);
        printf("I %d  RC %d\n",i,rc);
    }

    return 0;
}
