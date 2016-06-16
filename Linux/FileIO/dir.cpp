#include <dirent.h>
#include <iostream>

int main()
{
	DIR* dir = opendir("/home/yuliming/Test");
	struct dirent *de;
	while (de = readdir(dir)) {
		std::cout << de->d_ino << std::endl;
		std::cout << de->d_off << std::endl;
		std::cout << de->d_reclen << std::endl;
		std::cout << de->d_type << std::endl;
		std::cout << de->d_name << std::endl;
	}
}
