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

#define BUFF_SIZE 1024

static int	my_open(struct inode *, struct file *);
static int	my_release(struct inode *, struct file *);

static struct file_operations my_fops = {
	.owner		= THIS_MODULE,
	.open		= my_open,
	.release	= my_release,
};

static struct miscdevice my_misc = {
	.minor		= DEV_MINOR_NUM,
	.name		= DEV_NAME,
	.fops		= &my_fops,
	.mode		= 0777,
};

static int my_open(struct inode *inode, struct file *filp)
{
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	return 0;
}

static int my_release(struct inode *inode, struct file *filp)
{
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	return 0;
}

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

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("lunar456th@naver.com");
MODULE_DESCRIPTION("My Device Driver");
MODULE_VERSION("1.0.0");