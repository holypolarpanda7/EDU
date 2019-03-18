/*
    This program is a trivial demo of using select on exactly one
    descriptor, stdin.  You should probably run it twice, once where
    stdin is from a pipe or redirection, i.e.:
        select_demo < some_text_file
    The second run should be with stdin from the keyboard:
	select_demo
    Note that this second run will occasionally timeout and loop back
    to the select if you do not enter anything from the keyboard.
*/

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

void main(int argc, char **argv)
{
    int rc, n, done;
    fd_set readfds;
    char buf[200];
    struct timeval tv;

    if (isatty(0))
        printf("stdin is either a tty or a pseudo-tty\n");
    else
        printf("stdin is either a pipe or redirected file\n");
    done = 0;
    while ( !done ) 
    {
        FD_ZERO( &readfds );
	FD_SET( 0, &readfds );  /* set stdin */
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        rc = select( FD_SETSIZE, &readfds, NULL, NULL, &tv );

        if (rc == 0)
	{
            printf("select timed out\n");
            continue;
        } 
        if (rc == -1  &&  errno == EINTR)
	{
            printf("select interrupted; continuing\n");
            continue;
        }
        if ( rc < 0 )
	{
            done = 1;
            printf("select failed\n");
        }

	if (FD_ISSET(0,&readfds))  /* if something on stdin */
	{
	    n = read(0,buf,100);
	    if (n == -1)
	    {
	        printf("read failed\n");
		done = 1;
	    }
	    else if (n == 0)
	        done = 1;
	    else
	    {
		write(1,"from stdin: ",13);
		write(1,buf,n);
	    }
	}
    }
}
