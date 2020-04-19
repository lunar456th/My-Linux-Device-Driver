#include "libmydev.h"
#include "mydev.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>

#define TEXT_LEN 14

const static char *dev_name = "/dev/mydev0";
unsigned char bInitialized = 0;
int mydev_fd = 0;
static char buff[256];

static int _MYDEV_initialize(void)
{
	if ((mydev_fd = open(dev_name, O_RDWR)) < 0)
	{
        syslog(LOG_INFO, "[%s:%d] open failed", __func__, __LINE__);
		return -1;
	}
    bInitialized = 1;
    syslog(LOG_INFO, "[%s:%d] open success", __func__, __LINE__);
    return 0;
}

int MYDEV_read(void)
{
    int ret = 0;
    if (!bInitialized)
    {
        if (_MYDEV_initialize() < 0)
        {
            syslog(LOG_INFO, "[%s:%d] _MYDEV_initialize failed", __func__, __LINE__);
            return -1;
        }
    }
	if ((ret = read(mydev_fd, buff, TEXT_LEN)) < 0)
	{
        syslog(LOG_INFO, "[%s:%d] read failed", __func__, __LINE__);
		return -1;
	}
    syslog(LOG_INFO, "[%s:%d] read success -> (ret: %d, buff: %s)", __func__, __LINE__, ret, buff);
    return 0;
}

int MYDEV_write(void)
{
    int ret = 0;
    if (!bInitialized)
    {
        if (_MYDEV_initialize() < 0)
        {
            syslog(LOG_INFO, "[%s:%d] _MYDEV_initialize failed", __func__, __LINE__);
            return -1;
        }
    }
	if ((ret = write(mydev_fd, "Hello World!", TEXT_LEN)) < 0)
	{
        syslog(LOG_INFO, "[%s:%d] write failed", __func__, __LINE__);
		return -1;
	}
    syslog(LOG_INFO, "[%s:%d] write success", __func__, __LINE__);
    return 0;
}

int MYDEV_ioctl_init(void)
{
    int ret = 0;
    if (!bInitialized)
    {
        if (_MYDEV_initialize() < 0)
        {
            syslog(LOG_INFO, "[%s:%d] _MYDEV_initialize failed", __func__, __LINE__);
            return -1;
        }
    }
	if ((ret = ioctl(mydev_fd, MYDEV_IOCTL_INIT)) < 0)
	{
        syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_INIT failed", __func__, __LINE__);
        return -1;
    }
    syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_INIT success", __func__, __LINE__);
    return 0;
}

int MYDEV_ioctl_deinit(void)
{
    int ret = 0;
    if (!bInitialized)
    {
        if (_MYDEV_initialize() < 0)
        {
            syslog(LOG_INFO, "[%s:%d] _MYDEV_initialize failed", __func__, __LINE__);
            return -1;
        }
    }
	if ((ret = ioctl(mydev_fd, MYDEV_IOCTL_DEINIT)) < 0)
	{
        syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_DEINIT failed", __func__, __LINE__);
        return -1;
    }
    syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_DEINIT success", __func__, __LINE__);
    return 0;
}

int MYDEV_ioctl_read(void)
{
    int ret = 0;
    if (!bInitialized)
    {
        if (_MYDEV_initialize() < 0)
        {
            syslog(LOG_INFO, "[%s:%d] _MYDEV_initialize failed", __func__, __LINE__);
            return -1;
        }
    }
	if ((ret = ioctl(mydev_fd, MYDEV_IOCTL_READ)) < 0)
	{
        syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_READ failed", __func__, __LINE__);
        return -1;
    }
    syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_READ failed", __func__, __LINE__);
    return 0;
}

int MYDEV_ioctl_write(void)
{
    int ret = 0;
    if (!bInitialized)
    {
        if (_MYDEV_initialize() < 0)
        {
            syslog(LOG_INFO, "[%s:%d] _MYDEV_initialize failed", __func__, __LINE__);
            return -1;
        }
    }
	if ((ret = ioctl(mydev_fd, MYDEV_IOCTL_WRITE)) < 0)
	{
        syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_WRITE failed", __func__, __LINE__);
        return -1;
    }
    syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_WRITE success", __func__, __LINE__);
    return 0;
}

int MYDEV_ioctl_rdwr(void)
{
    int ret = 0;
    if (!bInitialized)
    {
        if (_MYDEV_initialize() < 0)
        {
            syslog(LOG_INFO, "[%s:%d] _MYDEV_initialize failed", __func__, __LINE__);
            return -1;
        }
    }
	if ((ret = ioctl(mydev_fd, MYDEV_IOCTL_RDWR)) < 0)
	{
        syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_RDWR failed", __func__, __LINE__);
        return -1;
    }
    syslog(LOG_INFO, "[%s:%d] ioctl MYDEV_IOCTL_RDWR success", __func__, __LINE__);
    return 0;
}

