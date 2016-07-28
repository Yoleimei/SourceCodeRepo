#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <pthread.h>

static int uinp_fd = -1;
static uinput_user_dev uinp;
static input_event event;

int setup_uinput_device()
{
	int i = 0;
	uinp_fd = open("/dev/uinput", O_WRONLY | O_NDELAY);
	if (0 >= uinp_fd) {
		printf("unable to open /dev/uinput: %s\n", strerror(errno));
		return -1;
	}
	memset(&uinp, 0, sizeof(uinp));
	strncpy(uinp.name, "Ylm Virtual Input Device", UINPUT_MAX_NAME_SIZE);
	uinp.id.version = 4;
	uinp.id.bustype = BUS_USB;

	ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
	ioctl(uinp_fd, UI_SET_EVBIT, EV_SYN);
	for (i = 0; i < 256; ++i) {
		ioctl(uinp_fd, UI_SET_KEYBIT, i);
	}
	write(uinp_fd, &uinp, sizeof(uinp));
	//if (ioctl(uinp_fd, UI_DEV_CREATE)) {
		//printf("unable to create UINPUT device: %s.\n", strerror(errno));
		//return -1;
	//}
	return 1;
}

void press_a_key() 
{
	memset(&event, 0, sizeof(event));
	gettimeofday(&event.time, NULL);
	event.type = EV_KEY;
	event.code = KEY_B;
	event.value = 1;
	write(uinp_fd, &event, sizeof(event));
	
	event.type = EV_KEY;
	event.code = KEY_B;
	event.value = 0;
	write(uinp_fd, &event, sizeof(event));
	
	event.type = EV_SYN;
	event.code = SYN_REPORT;
	event.value = 0;
	write(uinp_fd, &event, sizeof(event));
}

void* read_input_event(void* arg)
{
	int i, iRet;
	int fd = -1;
	char name[64];
	char buf[64];
	for (i = 0; i < 32; ++i) {
		sprintf(name, "/dev/input/event%d", i);;
		if ((fd = open(name, O_RDONLY) >= 0)) {
			printf("find virtual device.\n");
			ioctl(fd, EVIOCGNAME(sizeof(buf)), buf);
			if(!strcmp(buf, "Ylm Virtual Input Device")) {
				iRet = read(fd, &event, sizeof(event));
				if (0 < iRet) {
					printf("type:%d, code:%d, value:%d\n", event.type, event.code, event.value);
				} 	
			}
			close(fd);
		}
	}
	return NULL;
}

int main()
{
	pthread_t pid;
	if (setup_uinput_device() < 0) {
		printf("unable to find uinput device\n");
		return -1;
	}	
	
	//pthread_create(&pid, NULL, read_input_event, NULL);

	press_a_key();

	printf("press any key to continue\n");
	scanf("*");
	
	//pthread_join(pid, NULL);

	ioctl(uinp_fd, UI_DEV_DESTROY);

	close(uinp_fd);
}
