#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main()
{
	int fd = open("text.txt", O_RDWR | O_APPEND);
	if (fd < 0)
		std::cout << "error" << std::endl;
	lseek(fd, 0, SEEK_CUR);
	int nbytes = write(fd, "Hello World!\n", 13);
	close(fd);
	std::cout << nbytes << std::endl;
}
