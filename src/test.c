#include <linux/kernel.h>
#include "include/test.h"

void myPrintTest(char* str) {
  printk(MOD_NAME ": Printed \"%s\"\n", str);
}