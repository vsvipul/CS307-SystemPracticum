#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
	panic("Kernel panic\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Exiting custom kernel module.\n");
}
