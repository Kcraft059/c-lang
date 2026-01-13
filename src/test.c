#include <linux/kernel.h>
#include <rpireg.h>

void myPrintTest(char* str) {
  printk(MOD_NAME ": Printed \"%s\"\n", str);
}