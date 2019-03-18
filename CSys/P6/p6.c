// Greg Wagner
// P6.c - program that dynamically loads libraries taken as the second argument and can call a
// function() passed as the third from the lib, the fourth & fifth arguments may be parameters for function()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

typedef double (*no_arg_func)(void);
typedef double (*one_arg_func)(double a);
typedef double (*two_arg_func)(double a, double b);

void main(int argc,char *argv[])
{
    void *library;
    no_arg_func foo;
    one_arg_func bar;
    two_arg_func foobar;
    const char *error;
    double value;

    library = dlopen(argv[1], RTLD_LAZY);
    if (library == NULL)
    {
         fprintf(stderr, "Could not open %s: %s\n", argv[1], dlerror());
         exit(1);
    }
 
    dlerror();    /* clear errors */
    			
    /* double atof(string) */
    if (argc == 3)
    {
        foo = dlsym(library, argv[2]);
        error = dlerror();
        if (error)
        {
            fprintf(stderr, "Could not find %s: %s\n",argv[2], error);
            exit(1);
        }
 
        value = (double) (*foo)();
    }
    else if (argc == 4)  
    {
        bar = dlsym(library, argv[2]);
        error = dlerror();
        if (error)
        {
            fprintf(stderr, "Could not find %s: %s\n",argv[2], error);
            exit(1);
        }
 
        value = (double) (*bar)(atof(argv[3]));
    }
    else
    {
	foobar = dlsym(library, argv[2]);
        error = dlerror();
        if (error)
        {
            fprintf(stderr, "Could not find %s: %s\n",argv[2], error);
            exit(1);
        }
 
        value = (double) (*foobar)(atof(argv[3]), atof(argv[4]));
    }
   
    printf("%.2f\n", value);
    dlclose(library);
    return;
}

