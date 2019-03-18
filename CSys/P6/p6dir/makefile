CFLAGS = -Wall 
LDFLAGS = -g
CC = gcc

TARGETS = p6

p6:	p6.c p6.so
	gcc $(LDFLAGS) -o $@ p6.c p6.so -ldl

p6lib.o: p6lib.c
	@echo "*  Use -fPIC to build an object file for a shared library."
	gcc -fPIC $(CFLAGS) -c $<

p6.so:	p6lib.o
	gcc $(LDFLAGS) -shared -o $@ $<

clean:
	rm -f *.o p6.so p6

expand:
	@for n in *.c; do \
	    expand $$n > $$n.foo; \
	    if cmp -s $$n $$n.foo ; then \
		rm -f $$n.foo; \
	    else  \
		echo "Updating $$n"; \
		mv $$n.foo $$n; \
	    fi \
	done 
