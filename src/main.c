#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define IO_BANK0_PHYS 0x00000000 // 0x400d0000, on /dev/mem
#define IO_BANK0_SIZE 0x128

int main() {
  int fd = open("/dev/gpiomem0", O_RDWR | O_SYNC);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  // Can't be done since, mem remap & access is forbidden to anything other than kernel drivers
  volatile uint32_t* gpio_base = mmap(NULL, IO_BANK0_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, IO_BANK0_PHYS);

  if (gpio_base == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  volatile int64_t* gpio_pin2 = (void*)gpio_base + 2 * 0x8;

  volatile int32_t* gpio2_status = (void*)gpio_pin2;
  volatile int32_t* gpio2_ctrl = (void*)gpio_pin2 + 0x4;

  printf("GPIO base: %p\n\
    \tGPIO2 Cluster: %p\n\
    \tGPIO2 Ctrl: %p\n\
    \tGPIO2 Status: %p\n",
         gpio_base, gpio_pin2, gpio2_ctrl, gpio2_status);

  munmap((void*)gpio_base, 0x1000);
  close(fd);
};
