#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define TEXT_LEN 14

int main()
{
	static char buff[256];
	int fd = 0, ret = 0;

	if ((fd = open("/dev/mydev0", O_RDWR)) < 0)
	{
		fprintf(stderr, "open failed (%d)\n", fd);
		return -1;
	}

	if ((ret = write(fd, "Hello World!", TEXT_LEN)) < 0)
	{
		fprintf(stderr, "write failed (%d)\n", ret);
	}

	if ((ret = read(fd, buff, TEXT_LEN)) < 0)
	{
		fprintf(stderr, "read failed (%d)\n", ret);
	}
	else
	{
		printf("read -> (ret:%d,buff:%s)\n", ret, buff);
	}

	if ((ret = close(fd)) < 0)
	{
		fprintf(stderr, "close failed (%d)\n", ret);
	}

	return 0;
}