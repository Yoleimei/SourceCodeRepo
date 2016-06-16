#include <sys/socket.h>
#include <sys/un.h>
#include <io.h>

#define CLI_PATH "/var/tmp/"
#define CLI_PERM S_IRWXU

int cli_conn(const char *name)
{
	int fd, len, err, rval;
	struct sockaddr_un un, sun;
	int do_unlink = 0;

	if (strlen(name) >= sizeof(un.sun_path)) {
		return -1;
	}

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		return -1;

	memset(&un, 0, sizeof(un));
	un.sun_family = AF_UNIX;
	sprintf(un.sun_path, "%s%05ld", CLI_PATH, (long)getpid());
	len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

	unlink(un.sun_path);
	if (bind(fd, (struct sockaddr *)&un, len) < 0) {
		return -2;
	}
	if (chmod(un.sun_path, CLI_PERM) < 0) {
		return -3;
	}

	memset(&sun, 0, sizeof(sun));
	sun.sun_family = AF_UNIX;
	strncpy(sun.sun_path, name, sizeof(name));
	len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
	if (connect(fd, (struct sockaddr *)&sun, len) < 0) {
		return -4;
	}
	return fd;
}
