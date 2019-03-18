#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
void main(int argc, char **argv)
{
    int i, rc;
    int stdin_pipe_fds[2], stdout_pipe_fds[2];
    char buf[100];
    char *args[argc+1];

    args[0] = "/usr/bin/bc";
    for (i = 1; i < argc; i++)
    {
    printf("arg %d: %s\n",i,argv[i]); /////////		    
    args[i] = argv[i];
    } 
    args[argc] = NULL;
	
    pipe(stdin_pipe_fds);
    pipe(stdout_pipe_fds);
    
    rc = fork();
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
    close(stdin_pipe_fds[0]);
    close(stdout_pipe_fds[1]);
    
    /* The following write is commented out because this parent
       process may write to the pipe after the child has exited
       since this child program does no reading.
       In that case, it would get a SIGPIPE and be terminated.
       I have found that some shells are better than others at
       telling you what happened in those cases.
    */
    write(stdin_pipe_fds[1],"44+55\n",6);
    if ((i = read(stdout_pipe_fds[0],buf,100)) > 0)
    {
	buf[i] = '\0';
        printf("stdout: %s\n",buf);
    }
    write(stdin_pipe_fds[1],"33*1.5\n",7); 
    if ((i = read(stdout_pipe_fds[0],buf,100)) > 0)
    {
	buf[i] = '\0';
        printf("stdout: %s\n",buf);
    }
   /* if ((i = read(stderr_pipe_fds[0],buf,100)) > 0)
    {
	buf[i] = '\0';
        printf("stderr: %s\n",buf);
    }*/
    
    close(stdin_pipe_fds[1]);
    close(stdout_pipe_fds[0]);
    //wait(NULL);
    //exit(0);
}
