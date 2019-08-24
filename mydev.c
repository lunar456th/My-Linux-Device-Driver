#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include "mydev.h"

char dev_name[] = "mydev";

static int __init my_init(void)
{
	pr_info("[%s] %s()\n", dev_name, __FUNCTION__);
	return 0;
}

void __exit my_exit(void)
{
	pr_info("[%s] %s()\n", dev_name, __FUNCTION__);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("lunar456th@naver.com");
MODULE_DESCRIPTION("My Device Driver");
MODULE_VERSION("1.0.0");