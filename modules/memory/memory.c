#include <linux/init.h>  /* module_init and module_exit macros */
#include <linux/module.h>  /* links to kernel version */
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/fs.h> /* everything... */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/uaccess.h> /* copy_from/to_user */

MODULE_LICENSE("Dual BSD/GPL");

/* Global variables of the driver */

/* Major number */
int memory_major = 60;

/* Buffer to store data */
char *memory_buffer;

/* Declaration of memory.c functions */

int memory_open(struct inode *inode, struct file *filp);
int memory_release(struct inode *inode, struct file *filp);
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t memory_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
void memory_exit(void);
int memory_init(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations memory_fops = {
  .owner = THIS_MODULE,
  .read = memory_read,
  .write= memory_write,
  .open = memory_open,
  .release= memory_release
};

/* Declaration of the init and exit functions */
module_init(memory_init);
module_exit(memory_exit);

// --- Below contains all of the function definitions of memory.c ---

//*******************************************
// LOADING THE MODULE IN THE KERNEL
// memory_init() function
//*******************************************
int memory_init(void) {
    /* Registering device */
    int result = register_chrdev(memory_major, 
                                "memory", 
                                &memory_fops);
    if (result < 0) {
        printk("<1>memory: cannot obtain major number %d\n", memory_major);
        return result;
    }

    /* Allocating memory for the buffer */
    memory_buffer = kmalloc(1, GFP_KERNEL); 
    if (!memory_buffer) { 
        result = -ENOMEM;
        goto fail;
    } 

    // Set the memory buffer to all zeros
    memset(memory_buffer, 0, 1);

    // Log completion of memory module insertion into the kernel
    printk("<1>Inserting memory module\n"); 

    return 0;

    // Fail tag
    fail: 
        memory_exit(); 
        return result;
}

//*******************************************
// UNLOADING THE MODULE IN THE KERNEL
// memory_exit() function
//*******************************************
void memory_exit(void) {
    /* Freeing the major number */
    unregister_chrdev(memory_major, 
                    "memory");

    /* Freeing buffer memory */
    if (memory_buffer) {
        kfree(memory_buffer);
    }

    printk("<1>Removing memory module\n");
}

//***************************
// OPENING THE DEVICE DRIVER
//***************************
int memory_open(struct inode *inode, struct file *filp) {
  /* Success */
  return 0;
}

//**********************************
// CLOSING THE DEVICE DRIVER 
//**********************************
int memory_release(struct inode *inode, struct file *filp) {
  /* Success */
  return 0;
}

//*****************************************************
//  DEVICE READ
//  COPY THE DATA INTO THE USER BUFFER
//   ADDRESS TO THE USER BUFFER IS PROVIDED IN PARAMETERS
//*******************************************************
ssize_t memory_read(struct file *filp, 
                    char *buf, 
                    size_t count, 
                    loff_t *f_pos) { 

    /* Transfering data to user space */ 
    copy_to_user(buf, memory_buffer, 1);

    /* Changing reading position as best suits */ 
    if (*f_pos == 0) { 
        *f_pos += 1; 
        return 1; 
    } else { 
        return 0; 
    }
}

//*****************************************************
//  DEVICE WRITE
//  COPY THE DATA FROM THE USER BUFFER
//   ADDRESS TO THE USER BUFFER IS PROVIDED IN PARAMETERS
//*******************************************************
ssize_t memory_write(struct file *filp, 
                    const char *buf,
                    size_t count, 
                    loff_t *f_pos) {
    char *tmp;
    tmp = (char*)(buf + count - 1);
    copy_from_user(memory_buffer,tmp,1);
    return 1;
}