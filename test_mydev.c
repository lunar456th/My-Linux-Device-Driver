#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "mydev.h"

int main(void)
{
	int fd = 0, ret = 0;

	if(fd = open("/dev/mydev", O_RDWR) < 0)
	{
		perror("open failed\n");
		return -1;
	}

	close(fd);

	return 0;
}