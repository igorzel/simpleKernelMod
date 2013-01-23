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
#include <linux/proc_fs.h>


/******************************************************************************/
/*                                                                            */
/******************************************************************************/
#define PROC_FILE_NAME ("algo_kernel_mod")

/******************************************************************************/
/*                                                                            */
/* Викликається при читанні з /proc файла пристрою                            */
/*                                                                            */
/******************************************************************************/
static int
algo_kernel_mod_read_proc(char *buffer, char **start, off_t offset, int size, int *eof,
                void *data)
{
    const char* defaultData = "Data from algo_kernel_mod\n";
	const int dataSize = strlen(defaultData);

	// дозволяємо читатати лише з початку файлу
	if (offset != 0)
	{
		return 0;
	}

	// перевіряємо чи достатнього розміру буфер нам передали
	if (size < dataSize)
	{
		return EINVAL;
	}

	// копіюємо дані у буфер
	strcpy(buffer, defaultData);

	// виставляємо ознаку кінця файлу
	*eof = 1;

	return dataSize;
}

/******************************************************************************/
/*                                                                            */
/* Функція викликається при початковій ініціалізації модуля                   */
/*                                                                            */
/******************************************************************************/
static int __init algo_kernel_mod_init(void)
{
	printk(KERN_DEBUG "Hello from algo_kernel_mod!\n");

	if (create_proc_read_entry(PROC_FILE_NAME, 0, NULL, algo_kernel_mod_read_proc, NULL) == 0)
	{
		printk(KERN_ERR "Unable to register \"%s\" proc file\n", PROC_FILE_NAME);

		return ENOMEM;
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Функція викликається при закінченні роботи модуля                          */
/*                                                                            */
/******************************************************************************/
static void __exit algo_kernel_mod_exit(void)
{
	printk(KERN_DEBUG "Good bye to algo_kernel_mod!\n");

	remove_proc_entry(PROC_FILE_NAME, NULL);
}

/******************************************************************************/

module_init(algo_kernel_mod_init);
module_exit(algo_kernel_mod_exit);

/******************************************************************************/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("svarozhych");
MODULE_DESCRIPTION("A sample, linux kernel module.");
MODULE_VERSION("1.0");

