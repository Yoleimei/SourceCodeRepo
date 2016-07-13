#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	DIR *dirp = NULL;
	struct dirent *dp = NULL;
	
	dirp = opendir(".");
	while (true) {
		dp = readdir(dirp);
		if (NULL == dp) 
			break;
		printf("filename: %s\n", dp->d_name);
	}
	closedir(dirp);
}
