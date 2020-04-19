#ifndef __LIBMYDEV_H__
#define __LIBMYDEV_H__

#include "mydev.h"

int MYDEV_read(void);
int MYDEV_write(void);
int MYDEV_ioctl_init(void);
int MYDEV_ioctl_deinit(void);
int MYDEV_ioctl_read(void);
int MYDEV_ioctl_write(void);
int MYDEV_ioctl_rdwr(void);

#endif /*__LIBMYDEV_H__*/
