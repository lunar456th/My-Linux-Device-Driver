#include "libmydev.h"

#include <stdio.h>
#include <unistd.h>

int main()
{
    int ret = 0;

    // MYDEV_write
	if ((ret = MYDEV_write()) < 0)
	{
		fprintf(stderr, "MYDEV_write failed (%d)\n", ret);
	}
	else
	{
		printf("MYDEV_write success\n");
	}

    // MYDEV_read
	if ((ret = MYDEV_read()) < 0)
	{
		fprintf(stderr, "MYDEV_read failed (%d)\n", ret);
	}
	else
	{
		printf("MYDEV_read success\n");
	}
    usleep(1000 * 1000);

    // MYDEV_ioctl_init
	if ((ret = MYDEV_ioctl_init()) < 0)
	{
		fprintf(stderr, "MYDEV_ioctl_init failed (%d)\n", ret);
	}
	else
	{
		printf("MYDEV_ioctl_init success\n");
	}

    // MYDEV_ioctl_deinit
	if ((ret = MYDEV_ioctl_deinit()) < 0)
	{
		fprintf(stderr, "MYDEV_ioctl_deinit failed (%d)\n", ret);
	}
	else
	{
		printf("MYDEV_ioctl_deinit success\n");
	}

    // MYDEV_ioctl_read
	if ((ret = MYDEV_ioctl_read()) < 0)
	{
		fprintf(stderr, "MYDEV_ioctl_read failed (%d)\n", ret);
	}
	else
	{
		printf("MYDEV_ioctl_read success\n");
	}

    // MYDEV_ioctl_write
	if ((ret = MYDEV_ioctl_write()) < 0)
	{
		fprintf(stderr, "MYDEV_ioctl_write failed (%d)\n", ret);
	}
	else
	{
		printf("MYDEV_ioctl_write success\n");
	}

    // MYDEV_ioctl_rdwr
	if ((ret = MYDEV_ioctl_rdwr()) < 0)
	{
		fprintf(stderr, "MYDEV_ioctl_rdwr failed (%d)\n", ret);
	}
	else
	{
		printf("MYDEV_ioctl_rdwr success\n");
	}

	return 0;
}

