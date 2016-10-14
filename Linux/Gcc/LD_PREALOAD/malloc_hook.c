#include <malloc.h>
#include <stdio.h>

static void my_init_hook(void);
static void *my_malloc_hook(size_t, const void *);
static void my_free_hook(void *, const void *);

void (*__malloc_initialize_hook)(void) = my_init_hook;

static void my_init_hook(void)
{
	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;
	__malloc_hook = my_alloc_hook;
	__free_hook = my_free_hook;
}

static void *my_alloc_hook(size_t size, const void *caller)
{
	void *result;
	__malloc_hook = old_malloc_hook;
	__free_hook = old_free_hook;
	result = malloc(size);
	printf("malloc(%u) returns %p\n", size, result);
	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;
	__malloc_hook = my_alloc_hook;
	__free_hook = my_free_hook;
	return result;
}

static void *my_free_hook(void *ptr, const void *caller)
{
	void *result;
	__malloc_hook = old_malloc_hook;
	__free_hook = old_free_hook;
	free(ptr);
	printf("free(%p)\n", ptr);
	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;
	__malloc_hook = my_alloc_hook;
	__free_hook = my_free_hook;
	return result;
}

int main()
{
	int *p = malloc(1024);
	free(p);
}
