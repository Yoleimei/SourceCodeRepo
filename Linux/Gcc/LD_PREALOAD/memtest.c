#include <linux/mman.h>
#include <malloc.h>
#include <stdio.h>

void *mymalloc(size_t size);
void myfree(void *ptr);

extern void *malloc(size_t size)
{
	return mymalloc(size);
}

extern void free(void *ptr)
{
	myfree(ptr);
}

void *mymalloc(size_t size)
{
	printf("mymalloc\n");
	return __libc_malloc(size);
}

void myfree(void *ptr)
{
	printf("myfree\n");
	__libc_free(ptr);
}
