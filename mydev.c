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

#define DEV_MAJOR_NUM 240
#define DEV_MINOR_NUM 0
#define DEV_NAME "mydev"

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

static struct file_operations my_fops = {
	.owner		= THIS_MODULE,
	.open		= my_open,
	.release	= my_release,
};

static int __init my_init(void)
{
	int ret = 0;
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	if ((ret = register_chrdev(DEV_MAJOR_NUM, DEV_NAME, &my_fops)) < 0)
	{
		pr_info("[%s] %s():%d register_chrdev failed (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	return ret;
}

void __exit my_exit(void)
{
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	unregister_chrdev(DEV_MAJOR_NUM, DEV_NAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("lunar456th@naver.com");
MODULE_DESCRIPTION("My Device Driver");
MODULE_VERSION("1.0.0");