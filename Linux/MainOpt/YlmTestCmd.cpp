#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define HELP_STR ("--help")

void ShowHelp()
{
	fputs("========== Help ==========\n", stdout);
	fputs("options include:\n", stdout);
	fputs("  -a          Show default name\n", stdout);
	fputs("  -b [name]   Show name\n", stdout);
	fputs("==========================\n", stdout);
}

int main(int argc, char *argv[])
{
	int ch;
	char *opt_arg;

	if (argc == 1 || (argc == 2 && 0 == strncmp(argv[1], HELP_STR, sizeof(HELP_STR)))) {
		ShowHelp();
		return 0;
	}

	if (argc > 1) {
		printf("argv[1] = %s\n", argv[1]);
	}

	while ((ch = getopt(argc, argv, "ab:")) != -1) {
		printf("optind: %d\n", optind);
		switch(ch) {
			case 'a': 
				{
					printf("Hello Yoleimei\n");
				}
				break;
			case 'b':
				{
					opt_arg = optarg;
					printf("Hello %s\n", opt_arg);
				}
				break;
			case '?':
				{
					printf("?\n");
				}
				break;
			case ':':
				{
					printf(":\n");
				}
				break;
			default:
				break;
		}
	}
}

