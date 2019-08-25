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

#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/mm.h>
#include <linux/kdev_t.h>
#include <asm/page.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEV_MINOR_NUM 242
#define DEV_NAME "mydev"

static int	my_open(struct inode *, struct file *);
static int	my_release(struct inode *, struct file *);
static int	my_mmap(struct file *, struct vm_area_struct *);
static void	mmap_open(struct vm_area_struct *);
static void	mmap_close(struct vm_area_struct *);

static struct file_operations my_fops = {
	.owner		= THIS_MODULE,
	.open		= my_open,
	.release	= my_release,
	.mmap 		= my_mmap,
};

static struct miscdevice my_misc = {
	.minor	= DEV_MINOR_NUM,
	.name	= DEV_NAME,
	.fops	= &my_fops,
	.mode	= 0777,
};

static struct vm_operations_struct simple_remap_vm_ops = {
	.open =  mmap_open,
	.close = mmap_close,
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

static void __exit my_exit(void)
{
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	misc_deregister(&my_misc);
}

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

static int my_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int ret = 0;
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	if ((ret = remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, vma->vm_end - vma->vm_start, vma->vm_page_prot)))
	{
		pr_info("[%s] %s():%d remap_pfn_range failed (%d)\n", __FILE__, __FUNCTION__, __LINE__, ret);
		return -EAGAIN;
	}
	vma->vm_ops = &simple_remap_vm_ops;
	mmap_open(vma);
	return 0;
}

static void mmap_open(struct vm_area_struct *vma)
{
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
	pr_info("[%s] %s()(virt_addr:%lx,phy_addr:%lx)\n", __FILE__, __FUNCTION__, vma->vm_start, vma->vm_pgoff << PAGE_SHIFT);
}

static void mmap_close(struct vm_area_struct *vma)
{
	pr_info("[%s] %s()\n", __FILE__, __FUNCTION__);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("lunar456th@naver.com");
MODULE_DESCRIPTION("My Device Driver");
MODULE_VERSION("1.0.0");