#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

const unsigned long MAX_PATH = 128;
const char FRAMEBUFFER_DEVICE[] = "/dev/fb";

void Help()
{
	printf("testScreenInfoTool\n");
	printf("testScreenInfoTool n     // get info of /dev/fbn\n");
}

void ShowFixScreenInfo(struct fb_fix_screeninfo finfo)
{
	printf("======== Fix Screen Info ========\n");
	printf("id          : %s\n", finfo.id);
	printf("smem_start  : 0x%lx\n", finfo.smem_start);
	printf("smem_len    : 0x%lx\n", finfo.smem_len);
	printf("type        : %u\n", finfo.type);
	printf("type_aux    : %u\n", finfo.type_aux);
	printf("visual      : %u\n", finfo.visual);
	printf("xpanstep    : %hu\n", finfo.xpanstep);
	printf("ypanstep    : %hu\n", finfo.ypanstep);
	printf("ywrapstep   : %hu\n", finfo.ywrapstep);
	printf("line_length : %u\n", finfo.line_length);
	printf("mmio_start  : %lu\n", finfo.mmio_start);
	printf("mmio_len    : %u\n", finfo.mmio_len);
	printf("accel       : %u\n", finfo.accel);
}

void ShowVarScreenInfo(struct fb_var_screeninfo vinfo)
{
	printf("======== Var Screen Info ========\n");
	printf("xres             : %u\n", vinfo.xres);
	printf("yres             : %u\n", vinfo.yres);
	printf("xres_virtual     : %u\n", vinfo.xres_virtual);
	printf("yres_virtual     : %u\n", vinfo.yres_virtual);
	printf("xoffset          : %u\n", vinfo.xoffset);
	printf("yoffset          : %u\n", vinfo.yoffset);
	printf("bits_per_pixel   : %u\n", vinfo.bits_per_pixel);
	printf("grayscale        : %u\n", vinfo.grayscale);
	printf("red_offset       : %u\n", vinfo.red.offset);
	printf("red_length       : %u\n", vinfo.red.length);
	printf("red_msb_right    : %u\n", vinfo.red.msb_right);
	printf("green_offset     : %u\n", vinfo.green.offset);
	printf("green_length     : %u\n", vinfo.green.length);
	printf("green_msb_right  : %u\n", vinfo.green.msb_right);
	printf("blue_offset      : %u\n", vinfo.blue.offset);
	printf("blue_length      : %u\n", vinfo.blue.length);
	printf("blue_msb_right   : %u\n", vinfo.blue.msb_right);
	printf("transp_offset    : %u\n", vinfo.transp.offset);
	printf("transp_length    : %u\n", vinfo.transp.length);
	printf("transp_msb_right : %u\n", vinfo.transp.msb_right);
	printf("nonstd           : %u\n", vinfo.nonstd);
	printf("activate         : %u\n", vinfo.activate);
	printf("height           : %u\n", vinfo.height);
	printf("width            : %u\n", vinfo.width);
	printf("pixclock         : %u\n", vinfo.pixclock);
	printf("left_margin      : %u\n", vinfo.left_margin);
	printf("right_margin     : %u\n", vinfo.right_margin);
	printf("upper_margin     : %u\n", vinfo.upper_margin);
	printf("lower_margin     : %u\n", vinfo.lower_margin);
	printf("hsync_len        : %u\n", vinfo.hsync_len);
	printf("vsync_len        : %u\n", vinfo.vsync_len);
	printf("sync             : %u\n", vinfo.sync);
	printf("vmode            : %u\n", vinfo.vmode);
	printf("rotate           : %u\n", vinfo.rotate);
	printf("colorspace       : %u\n", vinfo.colorspace);
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

	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;

	char strFilePath[MAX_PATH];
	strncpy(strFilePath, FRAMEBUFFER_DEVICE, sizeof(FRAMEBUFFER_DEVICE));
	strncat(strFilePath, argv[1], sizeof(strFilePath)-strlen(strFilePath)-1);
	int fd = open(strFilePath, O_RDWR);
	if (fd < 0) {
		printf("open %s error: %s\n", strFilePath, strerror(errno));
		return -1;
	}

	int ret = ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
	if (ret < 0) {
		printf("FBIOGET_FSCREENINFO error: %s\n", strerror(errno));
		return -1;
	}

	ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
	if (ret < 0) {
		printf("FBIOGET_VSCREENINFO error: %s\n", strerror(errno));
		return -1;
	}

	printf("screen info of %s:\n", strFilePath);
	ShowFixScreenInfo(finfo);
	ShowVarScreenInfo(vinfo);
}