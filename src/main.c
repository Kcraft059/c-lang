#include "include/rpireg.h"
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <rpireg.h>
#include <stdio.h>

// See https://elixir.bootlin.com/linux for source code

/* ---- Meta ---- */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Camille Therey");
MODULE_DESCRIPTION("RPI register interaction module");
MODULE_VERSION("0.01");
/* ---- END Meta ---- */

/// Declarations
static int chr_dev_init(struct file_operations*);
static int chr_dev_release();
static int __init mod_init(void);
static void __exit mod_exit(void);

/// Config
module_init(mod_init);
module_exit(mod_exit);

/// Func definitions
static int __init mod_init(void) {
  // Loads kernel module
  chr_dev_init(&(struct file_operations){});
  
  return 0;
}

static void __exit mod_exit(void) {
  // Unloads kernel module
  pr_info(MOD_NAME ": Exited.\n");
}

static int chr_dev_init(struct file_operations* fops) {
  // Inits a char device and stores major
  majorDev = register_chrdev(0, MOD_NAME, fops);

  if (majorDev < 0) {
    char errstr*;
    char baserr* = "An error happened registering chrdev: ";

    switch (majorDev) {
    case -EINVAL:
      errstr = "Invalid Major Number.";
      break;
    case -EBUSY:
      errstr = "Major Number already used.";
      break;
    default:
      char errstr[32];
      snprintf(errstr, 32, "Unknown error: %d.", majorDev);
      break;
    }

    int str_size = strlen(errstr) + strlen(baserr);
    char str[str_size];

    snprintf(str, str_size, "Err chrdev: %s", errstr);
  }

  return majorDev
}

static void chr_dev_release() {
  unregister_chrdev(majorDev);
}