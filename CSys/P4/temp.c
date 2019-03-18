// Greg Wagner
// project 4
// program that forks a child process that then execs '/usr/bin/bc'. The original proc' takes stdin from a file
// named by argv[0], following argvs are sent as command line args to the child proc'

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void main(int argc, char **argv)
{
    int i, rc;
    int stdin_pipe_fds[2], stdout_pipe_fds[2];
    char buf[100];
    FILE *fp;
    char *args[100] = {""};
    switch (argc-2){
        default :
	    strcat(args, "/usr/bin/bc", NULL);
        case 1 :
	    strcat(args, "/usr/bin/bc", argv[2], NULL};
	case 2 :
            strcat(args, "/usr/bin/bc", argv[2], argv[3], NULL};
        case 3 :
	    strcat(args, "/usr/bin/bc", argv[2], argv[3], argv[4], NULL};}

    pipe(stdin_pipe_fds);
    pipe(stdout_pipe_fds);
    
    rc = fork();
    alarm(60);    
    if (rc == -1)
    {
        printf("fork failed\n");
	exit(-1);
    }
    if (rc == 0)  /* child */
    {
        close(stdin_pipe_fds[1]);
        //close(stdout_pipe_fds[0]);
        
	dup2(stdin_pipe_fds[0],0);
	close(stdin_pipe_fds[0]);
        
	//dup2(stdout_pipe_fds[1],1);
	//close(stdout_pipe_fds[1]);
        
	rc = execve("/usr/bin/bc", args, NULL);
	exit(0);
    }
    /* parent */
    /* close ends of pipe that parent doesnt use */
    close(stdin_pipe_fds[0]);
    close(stdout_pipe_fds[1]);
    
    /* read from file */
    fp = fopen(argv[1], "r");
    if (fp == NULL) printf("no such file...\n");
    
    size_t len;
    
    while (fgets(buf,10,fp) != NULL)
    {
        len = strlen(buf);
        printf("in: %s",buf);
	i = write(stdin_pipe_fds[1],buf,len);
	//if (i < 0) printf("unsuccesful write...");
	
        /* if ((i = read(stdout_pipe_fds[0],buf,100)) > 0)
        {
	    buf[i] = '\0';		
            printf("stdout: %s\n",buf);
        }*/
    }
    close(stdin_pipe_fds[1]);
    close(stdout_pipe_fds[0]);
    close(fileno(fp));
    wait(NULL);
}
