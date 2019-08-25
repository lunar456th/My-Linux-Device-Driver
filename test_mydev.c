#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "mydev.h"

#define TEXT_LEN 14

int main()
{
	static char buff[256];
	int fd = 0, ret = 0;

	// open
	if ((fd = open("/dev/mydev", O_RDWR)) < 0)
	{
		fprintf(stderr, "open failed (%d)\n", fd);
		return -1;
	}

	// write
	if ((ret = write(fd, "Hello World!", TEXT_LEN)) < 0)
	{
		fprintf(stderr, "write failed (%d)\n", ret);
	}

	// read
	if ((ret = read(fd, buff, TEXT_LEN)) < 0)
	{
		fprintf(stderr, "read failed (%d)\n", ret);
	}
	else
	{
		printf("read -> (ret:%d,buff:%s)\n", ret, buff);
	}

	// ioctl
	if ((ret = ioctl(fd, MYDEV_IOCTL_INIT)) < 0)
	{
		fprintf(stderr, "ioctl MYDEV_IOCTL_INIT failed (%d)\n", ret);
	}
	if ((ret = ioctl(fd, MYDEV_IOCTL_DEINIT)) < 0)
	{
		fprintf(stderr, "ioctl MYDEV_IOCTL_DEINIT failed (%d)\n", ret);
	}
	if ((ret = ioctl(fd, MYDEV_IOCTL_READ)) < 0)
	{
		fprintf(stderr, "ioctl MYDEV_IOCTL_READ failed (%d)\n", ret);
	}
	if ((ret = ioctl(fd, MYDEV_IOCTL_WRITE)) < 0)
	{
		fprintf(stderr, "ioctl MYDEV_IOCTL_WRITE failed (%d)\n", ret);
	}
	if ((ret = ioctl(fd, MYDEV_IOCTL_RDWR)) < 0)
	{
		fprintf(stderr, "ioctl MYDEV_IOCTL_RDWR failed (%d)\n", ret);
	}

	// release
	if ((ret = close(fd)) < 0)
	{
		fprintf(stderr, "close failed (%d)\n", ret);
	}

	return 0;
}