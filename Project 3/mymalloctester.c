#include <stdio.h>
#include "mymalloc.h"

int main() {
	printf("Original Address: %p\n", sbrk(0));
	void *a = my_firstfit_malloc(100);
	my_free(a);
	printf("Address after 1st malloc: %p\n", sbrk(0));
	void *b = my_firstfit_malloc(500);
	my_free(b);
	printf("Address after 2nd malloc: %p\n", sbrk(0));
	void *c = my_firstfit_malloc(200);
	void *d = my_firstfit_malloc(200);
	my_free(c);
	my_free(d);
	printf("Address after 2 mallocs at once: %p\n", sbrk(0));
	return 0;
}
