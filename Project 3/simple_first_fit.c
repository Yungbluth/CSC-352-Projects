#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mymalloc.h"
/*
 * Testing node creation functionality.
 */
int main(int argc, char **argv)
{
   //Test first fit:
    void *before = sbrk(0);
    void *a = my_firstfit_malloc(100);
    void *b = my_firstfit_malloc(200);
    void *c = my_firstfit_malloc(300);
    void *d = my_firstfit_malloc(100);
    void *e = my_firstfit_malloc(200);
    my_free(d);
    my_free(b);
    void *f = my_firstfit_malloc(100);
    return 0;
}

