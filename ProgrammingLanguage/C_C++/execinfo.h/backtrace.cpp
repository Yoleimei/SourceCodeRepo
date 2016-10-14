#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 100

void dump(void)
{
	int nptrs;
	void *buffer[SIZE];
	char **strings;

	nptrs = backtrace(buffer, SIZE);
	printf("backtrace() returned %d addresses\n", nptrs);

	// backtrace_symbols parce buffer to strings
	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < nptrs; i++)
		printf("%s\n", strings[i]);

	free(strings);

	// backtrace_symbols_fd parce buffer to fd
	int fd = open("backtrace.txt", O_CREAT | O_WRONLY);
	backtrace_symbols_fd(buffer, nptrs, fd);
	close(fd);
}

static void staticfunc(void) // "static" means don't export the symbol...
{
	dump();
}

void myfunc()
{
	staticfunc();
}

int main(int argc, char *argv[])
{
	myfunc();
}

/*
g++ backtrace.cpp -rdynamic -> so it will show function info
g++ backtace.cpp -rdynamic ; addr2line addr -e filename -f -> so it will show lineno
./a.out(_Z4dumpv+0x1f)[0x400a03]: _Z4 means length of function is 4; v means params is void
*/