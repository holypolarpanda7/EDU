#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct block
{
    struct mem_blk *next;
    int sz;         //size of block (bytes)
    bool free;      //true if mem is allocatable 
    void *inRegion; //points to begining of mem block region
} mem_blk;

mem_blk *myHeapHead;  //i think this is dangerous but cannot think of a better way

void heap_init(int num_pages_for_heap)
{
    int pgsz;
    myHeapHead = NULL;
    myHeapHead = malloc(sizeof(mem_blk));  //myHeapHead is now a node ptr to some initial node in a Llist 
    if (myHeapHead == NULL)                // (alloc'd somewhare in mem)
    {
        return;
    }

    myHeapHead->next = NULL;  // all point to NULL

    pgsz = getpagesize();  // get page size from os
    //printf("PGSZ %d pages %d total %d\n",pgsz,num_pages_for_heap,(num_pages_for_heap*pgsz));
    myHeapHead->sz = num_pages_for_heap*pgsz;
    
    myHeapHead->inRegion = mmap(NULL, (num_pages_for_heap*pgsz), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    if (myHeapHead->inRegion == ((void *) -1)) 
    {
        perror("mmap");                // the myHeapHead node now points to the begining byte of requested pages
        return;
    }
    //printf("region %p mod16 %d\n",myHeapHead->inRegion,((long int)myHeapHead->inRegion % 16));
   
    myHeapHead->free = 1;
    return;
}

void *heap_alloc(int num_bytes_to_allocate)
{
    mem_blk *block; //new block
    void *ptr = NULL;

    int r = num_bytes_to_allocate%16;
    int actual_bs_alloc = num_bytes_to_allocate + r;  // give a few more bytes just in case and for ease

    mem_blk *current = myHeapHead;
       
    while((current->next != NULL) && (current->free == 0) || (current->sz < actual_bs_alloc))
    {
        if (current->next != NULL) current = (mem_blk *) current->next;	//iterate to first available block with enough space
	else return ptr;	
    }
    //printf("found a spot...    ");    
        // splitting block off of end if current next == NULL
    if ((current->next == NULL) && (current->sz > actual_bs_alloc))
    {
        block = (mem_blk *) malloc(sizeof(mem_blk));
        block->next = NULL;
        block->sz = (current->sz - actual_bs_alloc);
        block->free = 1;
        block->inRegion = (current->inRegion + actual_bs_alloc);
        current->next = (void *)block;
        current->sz = actual_bs_alloc;
        current->free = 0;
        ptr = current->inRegion;
    }
	// first available is perfect size
    	// splitting or using middle block if current next != NULL
    else if ((current->next != NULL) && (current->sz > actual_bs_alloc))
    {
        block = (mem_blk *) malloc(sizeof(mem_blk));
        block->next = current->next;
        block->sz = (current->sz - actual_bs_alloc);
        block->free = 1;
        block->inRegion = (current->inRegion + actual_bs_alloc);
        current->next = (void *)block;
        current->sz = actual_bs_alloc;
        current->free = 0;
        ptr = current->inRegion;
    }
    else 
    {
        current->free = 0;
        ptr = current->inRegion;
    }

    //printf("allocating...\n");
    //if (ptr != NULL) printf("new ptr to %p\n", ptr);
    return ptr;
}

void heap_free(void *pointer_to_area_to_free)
{
    mem_blk *cur,*prev;

    cur = myHeapHead;
    while ((cur->next != NULL) && (cur->inRegion != pointer_to_area_to_free))
    {                                // if possible find the pointer and space to free
        cur = (mem_blk *) cur->next;
	if ((cur == NULL) && (cur->inRegion != pointer_to_area_to_free)) return;
    }

    cur->free = 1;

    cur = myHeapHead;
    while (cur->next != NULL)
    {                                // move thru and coalesce free space
	prev = cur;
	cur = (mem_blk *) cur->next;
	if ((prev->free == 1) && (cur->free == 1))
	{
            prev->next = cur->next;
	    prev->sz += cur->sz;
	    free(cur);
	}
    }

    return;
}


