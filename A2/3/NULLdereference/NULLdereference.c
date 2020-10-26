#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
	int * ptr = NULL;
	printk(KERN_INFO "Loading custom kernel module.\n");
	printk(KERN_INFO "value = %d\n", *ptr);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Exiting custom kernel module.\n");
}
