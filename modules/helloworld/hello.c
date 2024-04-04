#include <linux/init.h>  /* module_init and module_exit macros */
#include <linux/module.h>  /* links to kernel version */
#include <linux/kernel.h> /* printk() */

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Marguerite Doman"); /* This had weird quote symbols from the instruction document */

static int hello_init(void) {
  printk("<1> Hello world!\n");
  return 0;
}

static void hello_exit(void) {
  printk("<1> Bye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);