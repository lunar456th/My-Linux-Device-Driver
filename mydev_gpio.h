#ifndef __MYDEV_GPIO_H__
#define __MYDEV_GPIO_H__

#define BCM2835_IO_BASE	(0x3F000000)
#define GPIO_BASE	(BCM2835_IO_BASE + 0x200000)
#define GPIO_SIZE	(256)

#define GPIO_IN(x)	(*(gpio+((x)/10)) &= ~(7<<(((x)%10)*3)))
#define GPIO_OUT(x)	(*(gpio+((x)/10)) |= (1<<(((x)%10)*3)))

#define GPIO_SET(x)	(*(gpio+7) = 1<<x)
#define GPIO_CLR(x)	(*(gpio+10) = 1<<x)
#define GPIO_GET(x)	(*(gpio+13)&(1<<x))

volatile unsigned int *gpio;

#endif /*__MYDEV_GPIO_H__*/