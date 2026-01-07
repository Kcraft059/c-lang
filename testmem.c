#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define IO_BANK0_ADDR 0x400d0000

int main() {
  int fd = open("/dev/mem", O_RDWR | O_SYNC);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  // map 4KB (enough for IO_BANK0)
  volatile uint32_t* gpio_base = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, IO_BANK0_ADDR);
  if (gpio_base == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  volatile int64_t* gpio_pin2 = (void*)gpio_base + 2 * 8;

  volatile int32_t* gpio2_ctrl = (void*)gpio_pin2;
  volatile int32_t* gpio2_status = (void*)gpio_pin2 + 4;

  printf("GPIO base: %p\n\
    \tGPIO2 Cluster: %p\n\
    \tGPIO2 Ctrl: %p\n\
    \tGPIO2 Status: %p\n",
         gpio_base, gpio_pin2, gpio2_ctrl, gpio2_status);

  munmap((void*)gpio_base, 0x1000);
  close(fd);
};