#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "mydev.h"

#define PAGE_SIZE 4096

#define GPIO_BASE 0x3F200000
#define GPFSEL1 0x04
#define GPSET0 0x1C
#define GPCLR0 0x28

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
	memory = (char*)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
	if (!memory)
	{
		fprintf(stderr, "mmap null\n");
		return -1;
	}

	// gpio 18 LED blink 5 times
	volatile unsigned int *gpio = (volatile unsigned int *)memory;
	gpio[GPFSEL1/4] = (1 << 24);
	for (int i = 0; i < 5; i++)
	{
		gpio[GPSET0/4] |= (1 << 18);
		sleep(1);
		gpio[GPCLR0/4] |= (1 << 18);
		sleep(1);
	}

	// munmap
	if ((ret = mnumap(memory)) < 0)
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