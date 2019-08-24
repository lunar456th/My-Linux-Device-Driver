#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <asm/current.h>
#include <asm-generic/bitsperlong.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>

#include "mydev.h"

#define DEV_MAJOR_NUM 240
#define DEV_MINOR_NUM 0
#define BUFFER_SIZE 256

static const unsigned int MINOR_BASE = 0;
static const unsigned int MINOR_NUM  = 2;

static unsigned int		my_major;
static struct cdev		my_cdev;
static struct class		*my_class = NULL;
static dev_t			my_dev;
static char				*buffer;

struct data {
	unsigned char buffer[BUFFER_SIZE];
};

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
	kfree(buffer);
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

static struct file_operations my_fops = {
	.owner		= THIS_MODULE,
	.open		= my_open,
	.release	= my_release,
	.read		= my_read,
	.write		= my_write,
};

static int __init my_init(void)
{
	int ret = 0;
	int minor = 0;
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	if ((ret = alloc_chrdev_region(&my_dev, MINOR_BASE, MINOR_NUM, "mydev")) < 0)
	{
		pr_info("[%s] %s():%d alloc_chrdev_region failed (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		return -EINVAL;
	}

	my_major = MAJOR(my_dev);
	my_dev = MKDEV(my_major, MINOR_BASE);
	cdev_init(&my_cdev, &my_fops);
	my_cdev.owner = THIS_MODULE;
	if ((ret = cdev_add(&my_cdev, my_dev, MINOR_NUM)) < 0)
	{
		pr_info("[%s] %s():%d alloc_chrdev_region failed (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		unregister_chrdev_region(my_dev, MINOR_NUM);
		return -EINVAL;
	}
	my_class = class_create(THIS_MODULE, "mydev");
	if ((ret = IS_ERR(my_class)))
	{
		pr_info("[%s] %s():%d class_create failed (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		cdev_del(&my_cdev);
		unregister_chrdev_region(my_dev, MINOR_NUM);
		return -EINVAL;
	}
	for (minor = MINOR_BASE; minor < MINOR_BASE + MINOR_NUM; minor++)
	{
		if (!device_create(my_class, NULL, MKDEV(my_major, minor), NULL, "mydev%d", minor))
		{
			pr_info("[%s] %s():%d device_create failed\n", __FILE__, __FUNCTION__, __LINE__);
			return -EINVAL;
		}
	}

	return ret;
}

void __exit my_exit(void)
{
	int minor = 0;
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	for (minor = MINOR_BASE; minor < MINOR_BASE + MINOR_NUM; minor++)
	{
		device_destroy(my_class, MKDEV(my_major, minor));
	}
	class_destroy(my_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(my_dev, MINOR_NUM);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("lunar456th@naver.com");
MODULE_DESCRIPTION("My Device Driver");
MODULE_VERSION("1.0.0");