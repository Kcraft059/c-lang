#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/init.h>

#define IO_BANK0_PHYS  0x400d0000
#define IO_BANK0_SIZE  0x1000

static void __iomem *gpio_base;

static int __init rp1_gpio_init(void)
{
    pr_info("rp1_gpio: loading\n");

    gpio_base = ioremap(IO_BANK0_PHYS, IO_BANK0_SIZE);
    if (!gpio_base) {
        pr_err("rp1_gpio: ioremap failed\n");
        return -ENOMEM;
    }

    pr_info("rp1_gpio: IO_BANK0 mapped at %p\n", gpio_base);
    return 0;
}

static void __exit rp1_gpio_exit(void)
{
    if (gpio_base)
        iounmap(gpio_base);

    pr_info("rp1_gpio: unloaded\n");
}

module_init(rp1_gpio_init);
module_exit(rp1_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("RP1 GPIO control module");