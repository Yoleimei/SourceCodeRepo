#include <stdio.h>
#include <dlfcn.h>

#include "Test.h"

typedef int fniii(int, int);

int main()
{
	void *so_handler = dlopen("./libtest.so", RTLD_LAZY);

	dlerror();
	fniii *fn = (fniii*)dlsym(so_handler, "_ZN4Test3addEii");
	char *err = dlerror();
	if ( NULL != err) {
		fprintf(stderr, "%s\n", err);
		return -1;
	}

	printf("add 3 + 4 = %d\n", fn(3, 4));
	dlclose(so_handler);
	return 0;
}
