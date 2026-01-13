#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <rpireg.h>

// See https://elixir.bootlin.com/linux for source code

/*---- Meta ----*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Camille Therey");
MODULE_DESCRIPTION("RPI register interaction module");
MODULE_VERSION("0.01");

static int __init mod_init(void) {
  pr_info(MOD_NAME ": Loaded.\n");
  myPrintTest("GLOUP");
  return 0;
}

static void __exit mod_exit(void) {
  pr_info(MOD_NAME ": Exited.\n");
}

module_init(mod_init);
module_exit(mod_exit);