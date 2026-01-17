#include <linux/fs.h>
#include <linux/slab.h>
#include <rpireg.h>

/* ---- Meta ---- */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Camille Therey");
MODULE_DESCRIPTION("RPI register interaction module");
MODULE_VERSION("0.01");
/* ---- END Meta ---- */

/// Declarations
static int __init mod_init(void);
static void __exit mod_exit(void);

int majorDev = -1;
void* testmembuffer = NULL;

/// Config
module_init(mod_init);
module_exit(mod_exit);

static struct file_operations fops = {
    .mmap = fops_mmap};

/// Func definitions
static int __init mod_init(void) {
  // Loads kernel module
  pr_info(MOD_NAME ": loading.");

  chrdev_init(&fops);

  pr_info(MOD_NAME ": allocating %ldb of testing mem space.", PAGE_SIZE);
  testmembuffer = kmalloc(PAGE_SIZE, GFP_DMA); // GFP_DMA to prevent defragmentation in phys

  ((int*)testmembuffer)[0] = 3105;

  return 0;
}

static void __exit mod_exit(void) {
  // Unloads kernel module
  chrdev_release();

  pr_info(MOD_NAME ": exited.");
}