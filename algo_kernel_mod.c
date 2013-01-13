/*
 * A sample, linux kernel module.
 *
 * (C) 2013 svarozhych
 *
 * Redistributable under the terms of the GNU GPL.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int algo_kernel_mod_init(void)
{
	printk(KERN_DEBUG "Hello from algo_kernel_mod!\n");
	return 0;
}

static void algo_kernel_mod_exit(void)
{
	printk(KERN_DEBUG "Good bye to algo_kernel_mod!\n");
}

module_init(algo_kernel_mod_init);
module_exit(algo_kernel_mod_exit);

