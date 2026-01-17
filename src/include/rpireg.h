#ifndef HEADER_RPIREG
#define HEADER_RPIREG

/*
 * Main module import for rpireg
 * See https://elixir.bootlin.com/linux for linux source code
 */

#include <linux/kernel.h>
#include <linux/module.h>

// Macros
#define MOD_NAME "rpireg"

// Declaration
extern int majorDev;
extern void* testmembuffer;

int chrdev_init(struct file_operations*);
void chrdev_release(void);

int fops_mmap(struct file*, struct vm_area_struct*); // File ops
int fops_release(struct inode*, struct file*);

#endif