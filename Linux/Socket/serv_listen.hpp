#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <unistd.h>

int serv_listen(const char *name)
{
	int fd, len, err, rval;
	struct sockaddr_un un;

	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		return -1;
	}

	unlink(name);

	memset(&un, 0, sizeof(un));
	un.sun_family = AF_UNIX;
	strncpy(un.sun_path, name, sizeof(name));
	len = offsetof(struct sockaddr_un, sun_path) + strlen(name);

	if (bind(fd, (struct sockaddr *)&un, len) < 0 ) {
		return -2;
	}

	if (listen(fd, 10) < 0) {
		return -3;
	}
}
