#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include "mydev.h"

#define PAGE_SIZE 4096

int main()
{
	char *memory = NULL;
	int fd = 0, ret = 0;

	// open
	if ((fd = open("/dev/mydev", O_RDWR)) < 0)
	{
		fprintf(stderr, "open failed (%d)\n", fd);
		return -1;
	}

	// mmap
	memory = (char*)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (!memory)
	{
		fprintf(stderr, "mmap null\n");
		return -1;
	}
	
	// munmap
	if ((ret = munmap(memory, PAGE_SIZE)) < 0)
	{
		fprintf(stderr, "munmap failed (%d)\n", ret);
		return -1;
	}

	// release
	if ((ret = close(fd)) < 0)
	{
		fprintf(stderr, "close failed (%d)\n", ret);
		return -1;
	}

	return 0;
}
