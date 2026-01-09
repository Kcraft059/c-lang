#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                    \
  ((byte) & 0x80 ? '1' : '0'), ((byte) & 0x40 ? '1' : '0'),     \
      ((byte) & 0x20 ? '1' : '0'), ((byte) & 0x10 ? '1' : '0'), \
      ((byte) & 0x08 ? '1' : '0'), ((byte) & 0x04 ? '1' : '0'), \
      ((byte) & 0x02 ? '1' : '0'), ((byte) & 0x01 ? '1' : '0')

#define IO_BANK0_PHYS 0x00000000  // 0x400d0000, on /dev/mem
#define IO_BANK0_SIZE 0x30000

void gpioPrint(volatile void* gpio_base, int gpioIdx) {
  volatile int64_t* gpio_pin = gpio_base + gpioIdx * 0x8;

  volatile int32_t* gpio_status = (void*)gpio_pin;
  volatile int32_t* gpio_ctrl = (void*)gpio_pin + 0x4;

  printf(
      "GPIO%d base: %p\n\
    \tGPIOx Cluster: %p\n\
    \tGPIOx Ctrl: %p\n\
    \tGPIOx Status: %p\n",
      gpioIdx, gpio_base, gpio_pin, gpio_ctrl, gpio_status);

  printf("GPIO_STATUS:" BYTE_TO_BINARY_PATTERN
         "\n"
         "GPIO_CTRL:" BYTE_TO_BINARY_PATTERN "\n",
         BYTE_TO_BINARY(*(int8_t*)gpio_status),
         BYTE_TO_BINARY(*(int8_t*)gpio_ctrl));
};

int main(int argc, char** argv) {
  int fd = open("/dev/gpiomem0", O_RDWR | O_SYNC);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  volatile void* gpio_base = mmap(NULL, IO_BANK0_SIZE, PROT_READ | PROT_WRITE,
                                  MAP_SHARED, fd, IO_BANK0_PHYS);

  if (gpio_base == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  char* str = argv[1];
  int gpioIdx = strtod(str, &str);

  volatile int64_t* gpio_pin = gpio_base + gpioIdx * 0x8;

  volatile int32_t* gpio_ctrl = (void*)gpio_pin + 0x4;

  *gpio_ctrl &= ~(0b11111 << 0);  // sets funcsel to 0
  *gpio_ctrl |= 3 << 0;           // sets funsel to 3

  // Once set to pwm

  /*
  for i in $(seq 1 3); do echo $i | sudo tee /sys/class/pwm/pwmchip0/export;
  done

  echo "5000000" | sudo tee /sys/class/pwm/pwmchip0/pwm{1..3}/period
  echo "$(( 5000000 * 1/100 ))" | sudo tee /sys/class/pwm/pwmchip0/pwm{1..3}/duty_cycle
  echo "1" | sudo tee /sys/class/pwm/pwmchip0/pwm{1..3}/enable
  */

  gpioPrint(gpio_base, gpioIdx);

  munmap((void*)gpio_base, 0x1000);
  close(fd);
};
