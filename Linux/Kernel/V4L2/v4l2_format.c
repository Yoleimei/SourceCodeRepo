#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

const unsigned long MAX_PATH = 128;
const char FRAMEBUFFER_DEVICE[] = "/dev/video";

void Help()
{
	printf("testV4L2FormatTool\n");
	printf("testV4L2FormatTool n     // get format of /dev/videon\n");
}

void ShowV4L2Format(struct v4l2_format fmt)
{
	printf("======== V4L2 Format ========\n");
	printf("type              : %u\n", fmt.type);
	printf("width             : %u\n", fmt.fmt.pix.width);
	printf("height            : %u\n", fmt.fmt.pix.height);
	printf("pixelformat       : %u\n", fmt.fmt.pix.pixelformat);
	printf("field             : %u\n", fmt.fmt.pix.field);
	printf("bytesperline      : %u\n", fmt.fmt.pix.bytesperline);
	printf("sizeimage         : %u\n", fmt.fmt.pix.sizeimage);
	printf("colorspace        : %u\n", fmt.fmt.pix.colorspace);
	printf("priv              : %u\n", fmt.fmt.pix.priv);
	printf("flags             : %u\n", fmt.fmt.pix.flags);
	printf("ycbcr_enc         : %u\n", fmt.fmt.pix.ycbcr_enc);
	printf("quantization      : %u\n", fmt.fmt.pix.quantization);
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		Help();
		return -1;
	}

	if (!strcmp(argv[1], "-help")) {
		Help();
		return 0;
	}

	struct v4l2_format fmt;

	char strFilePath[MAX_PATH];
	strncpy(strFilePath, FRAMEBUFFER_DEVICE, sizeof(FRAMEBUFFER_DEVICE));
	strncat(strFilePath, argv[1], sizeof(strFilePath)-strlen(strFilePath)-1);
	int fd = open(strFilePath, O_RDWR);
	if (fd < 0) {
		printf("open %s error: %s\n", strFilePath, strerror(errno));
		return -1;
	}

	int ret = ioctl(fd, VIDIOC_G_FMT, &fmt);
	if (ret < 0) {
		printf("VIDIOC_G_FMT error: %s\n", strerror(errno));
		return -1;
	}

	printf("format of %s:\n", strFilePath);
	ShowV4L2Format(fmt);
}