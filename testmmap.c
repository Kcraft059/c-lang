#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define IO_BANK0_PHYS 0x400d0000 // - wrong 0x400d0000, on /dev/mem
                                // Might need to take a look at /proc/device-tree

int main(int argc, char** argv) {
  int fd = open("./rpireg", O_RDWR | O_SYNC);

  if (fd < 0) {
    perror("open");
    return 1;
  }

  volatile void* gpio_base = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE,
                                  MAP_SHARED, fd,0x0);

  if (gpio_base == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  volatile int64_t* gpiopin = gpio_base + 0 * 0x8;

  volatile int32_t* gpiopin_status = (void*)gpiopin;
  volatile int32_t* gpiopin_control = (void*)gpiopin + 0x4;

  printf("Val of Funsel for 13: %08x\n", *gpiopin_control);
}