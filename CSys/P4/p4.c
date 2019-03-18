// Greg Wagner
// project 4
// program that forks a child process that then execs '/usr/bin/bc'. The original proc' takes stdin from a file
// named by argv[0], following argvs are sent as command line args to the child proc'

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/select.h>

void main(int argc, char **argv)
{
    int i, rc;
    int stdin_pipe_fds[2], stdout_pipe_fds[2];
    char buf[100];
    FILE *fp;

    char * args[5] = {NULL};

    args[0] = "/usr/bin/bc";
    for (i=1; i<argc-1; i++){
        args[i] = argv[i+1];
    }
    args[argc-1] = 0;

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
        close(stdout_pipe_fds[0]);
        
	dup2(stdin_pipe_fds[0],0);
	close(stdin_pipe_fds[0]);
        
	dup2(stdout_pipe_fds[1],1);
	close(stdout_pipe_fds[1]);
        
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
    fd_set set;
    struct timeval timeout;
    
    while (fgets(buf,100,fp) != NULL)
    {
        len = strlen(buf);
        printf("in: %s",buf);
	i = write(stdin_pipe_fds[1],buf,len);
	
	timeout.tv_sec = 1;
        timeout.tv_usec = 0;
	FD_ZERO(&set);
        FD_SET(stdout_pipe_fds[0], &set);
        rc = select(FD_SETSIZE, &set, NULL, NULL, &timeout);

        if (rc)
	{
	    if ((i = read(stdout_pipe_fds[0],buf,100)) > 0)
            {
	        buf[i] = '\0';		
                printf("stdout: %s\n",buf);
            }
	}
    }
    close(stdin_pipe_fds[1]);
    close(stdout_pipe_fds[0]);
    close(fileno(fp));
}
