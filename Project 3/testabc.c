#include "testabc.h"
#define BIGGEST 25000

struct block //each block of memory is a node in this struct
{
	struct block *prev, *next;
        int size;
	int isfree;     //boolean: 1 for yes free, 0 for not free
};


static void *diffBlocks[BIGGEST/sizeof(struct block)+1] = {0}; //different blocks of space
static const int blockSize = BIGGEST/sizeof(struct block)+1; //size of diffBlocks
static char bigblock[BIGGEST]; //big block of memory space

static int findFree() {
        //returns the first free block
	int i;
	for (i = 0; i <= blockSize-1; i++)
		if (diffBlocks[i] == 0) 
			return i;
	return 1; //shouln't ever hit here
}

void *my_firstfit_malloc(unsigned int size)
{
	static int init = 0; //boolean checks if needs to be initialized
	struct block *cur; //current node
        static struct block *head; //head of LL
	struct block *next; //node after cur

	if(!init)	// only happens first time
	{
		// initializes the LL with head
                init = 1;
		head = (struct block*) bigblock;
                head->isfree = 1;
		head->size = BIGGEST - sizeof(struct block);
                head->prev = head->next = 0;
                int i = findFree();
		diffBlocks[i] = bigblock;
	}
	cur = head;
	do {
		if(!cur->isfree || cur->size < size) {
			// goes to next in LL if cur node is either not free or too small
			cur = cur->next;
		}
		else if((size + sizeof(struct block)) > cur->size) {
			// node is free and big enough but not enough space for another after it
			cur->isfree = 0;
			return (char*)cur + sizeof(struct block);
		}
		else {
			// changes next to cur, and changes cur to new taken memory
			next = (struct block*)((char*)cur + sizeof(struct block) + size);
                        next->isfree = 1;
                        next->size = cur->size - sizeof(struct block) - size;
                        next->next = cur->next;
			next->prev = cur;
                        int i = findFree();
			diffBlocks[i] = next;
                        cur->isfree = 0;
			cur->size = size;
			cur->next = next;
			return (char*)cur + sizeof(struct block);
		}
	} while (cur != 0);
	return 0;
}

void my_free(void *cur)
{
        struct block *next;
	struct block *prev;
        struct block *ptr;

	ptr = (struct block*)((char*)cur - sizeof(struct block));
	void *a = sbrk(0);
	int i;
	for (i = 0; i <= blockSize-1; i++) {
                //loops until it finds the requested block to free, saved at i
		if (ptr == diffBlocks[i] && !ptr->isfree) {
			break;
		}
	}
	if(prev->isfree && (prev = ptr->prev) != 0)
	{
		//prev chunk is able to be merged
		prev->size += sizeof(struct block) + ptr->size;
		diffBlocks[i] = 0;
	}
	else
	{ //else set this block to free
		ptr->isfree = 1;
		prev = ptr;	// used below for checking if can merge with next
	}
	if((next = ptr->next) != 0 && next->isfree)
	{
		//merge with next chunk
		prev->size += sizeof(struct block) + next->size;
		prev->next = next->next;
		for (i = 0; i <= blockSize-1; i++) {
			if (next == diffBlocks[i]) {
				diffBlocks[i] = 0;
				break;
			}
		}
	}
}
