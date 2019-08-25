#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <asm-generic/bitsperlong.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include "mydev.h"

#define DEV_MINOR_NUM 242
#define DEV_NAME "mydev"

#define BUFFER_SIZE 256

struct data {
	unsigned char buffer[BUFFER_SIZE];
};

static int		my_open(struct inode *, struct file *);
static int		my_release(struct inode *, struct file *);
static ssize_t	my_read(struct file *, char *, size_t, loff_t *);
static ssize_t	my_write(struct file *, const char *, size_t, loff_t *);
static long		my_ioctl(struct file *, unsigned int, unsigned long);

static struct file_operations my_fops = {
	.owner			= THIS_MODULE,
	.open			= my_open,
	.release		= my_release,
	.read			= my_read,
	.write			= my_write,
	.unlocked_ioctl = my_ioctl,
};

static struct miscdevice my_misc = {
	.minor		= DEV_MINOR_NUM,
	.name		= DEV_NAME,
	.fops		= &my_fops,
	.mode		= 0777,
};

static int __init my_init(void)
{
	int ret = 0;
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	if ((ret = misc_register(&my_misc)) < 0)
	{
		pr_info("[%s] %s():%d misc_register failed (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		return -EINVAL;
	}
	return 0;
}

void __exit my_exit(void)
{
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	misc_deregister(&my_misc);
}

static int my_open(struct inode *inode, struct file *filp)
{
	char *str = "null";
	int ret = 0;
	struct data *p = kmalloc(sizeof(struct data), GFP_KERNEL);
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	if (!p)
	{
		pr_info("[%s] %s():%d kmalloc null (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		return -ENOMEM;
	}
	ret = strlcpy(p->buffer, str, sizeof(p->buffer));
	if (ret > strlen(str))
	{
		pr_info("[%s] %s():%d strlcpy too long (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
	}
	filp->private_data = p;
	return 0;
}

static int my_release(struct inode *inode, struct file *filp)
{
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	if (filp->private_data)
	{
		kfree(filp->private_data);
		filp->private_data = NULL;
	}
	return 0;
}

static ssize_t my_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	int ret = 0;
	struct data *p = filp->private_data;
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	count = (count > BUFFER_SIZE) ? BUFFER_SIZE : count;
	if ((ret = copy_to_user(buf, p->buffer, count)) < 0)
	{
		pr_info("[%s] %s():%d copy_to_user failed (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		return -EFAULT;
	}
	return count;
}

static ssize_t my_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	int ret = 0;
	struct data *p = filp->private_data;
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	pr_info("[%s] %s() copy_from_user() Before (0x%p,%s)\n", __FILE__, __FUNCTION__, p->buffer, p->buffer);
	if ((ret = copy_from_user(p->buffer, buf, count)) < 0)
	{
		pr_info("[%s] %s():%d copy_from_user failed (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		return -EFAULT;
	}
	pr_info("[%s] %s() copy_from_user() After  (0x%p,%s)\n", __FILE__, __FUNCTION__, p->buffer, p->buffer);
	return count;
}

static long my_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret = 0, size = 0;
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	pr_info("[%s] %s() cmd:%u\n", __FILE__, __FUNCTION__, cmd);
	if (_IOC_TYPE(cmd) != MYDEV_IOCTL_MAGIC)
	{
		pr_info("[%s] %s():%d invalid magic number\n", __FILE__, __FUNCTION__, __LINE__);
		return -EINVAL;
	}
	if (_IOC_NR(cmd) >= MYDEV_IOCTL_MAX_NR)
	{
		pr_info("[%s] %s():%d exceeded max value of cmd\n", __FILE__, __FUNCTION__, __LINE__);
		return -EINVAL;
	}
	if ((size = _IOC_SIZE(cmd)))
	{
		if (_IOC_DIR(cmd) & _IOC_READ)
		{
			ret = !access_ok(VERIFY_WRITE, (void __user*)arg, size);
		}
		else if (_IOC_DIR(cmd) & _IOC_WRITE)
		{
			ret = !access_ok(VERIFY_READ, (void __user*)arg, size);
		}
		if (ret)
		{
			return ret;
		}
	}
	switch (cmd)
	{
		case MYDEV_IOCTL_INIT:
			pr_info("[%s] %s() MYDEV_IOCTL_INIT\n", __FILE__, __FUNCTION__);
			break;
		case MYDEV_IOCTL_DEINIT:
			pr_info("[%s] %s() MYDEV_IOCTL_DEINIT\n", __FILE__, __FUNCTION__);
			break;
		case MYDEV_IOCTL_READ:
			pr_info("[%s] %s() MYDEV_IOCTL_READ\n", __FILE__, __FUNCTION__);
			break;
		case MYDEV_IOCTL_WRITE:
			pr_info("[%s] %s() MYDEV_IOCTL_WRITE\n", __FILE__, __FUNCTION__);
			break;
		case MYDEV_IOCTL_RDWR:
			pr_info("[%s] %s() MYDEV_IOCTL_RDWR\n", __FILE__, __FUNCTION__);
			break;
		default:
			pr_info("[%s] %s():%d unregistered cmd\n", __FILE__, __FUNCTION__, __LINE__);
			ret = -EINVAL;
			break;
	}
	return ret;
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("lunar456th@naver.com");
MODULE_DESCRIPTION("My Device Driver");
MODULE_VERSION("1.0.0");