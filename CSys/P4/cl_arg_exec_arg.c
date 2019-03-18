#include <stdio.h>
#include <unistd.h>
#include <string.h>

void main(int argc, char **argv){
    int i;
    char * dargs[] = {"/usr/bin/bc"};
    char * args[5] = {NULL};

    args[0] = "/bin";
    for (i=1; i<argc+1; i++){
        args[i] = argv[i];
    }
    args[argc+1] = 0;

    printf("default: %s\n", *dargs);
    //printf("added to args: %s\nargs: \n", buf);
    printf("args:\n");
    for (i=0; i<argc+1; i++){
        printf("    %s\n",args[i]);
    }
    

}
