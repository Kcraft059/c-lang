#include <lgpio.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define GPIO_USER "gpio-ctrl"

int gpioSetup(int, const char*);
void intHandler(int);

int main() {
  signal(SIGINT, intHandler);

  // Chip + pin setup
  int gpioChipH = gpioSetup(0, GPIO_USER);
  lgGpioClaimOutput(gpioChipH, 0, 4, 0);

  int8_t state = 0;
  while (1) {
    nanosleep(&(struct timespec){0,500000000}, NULL);

    lgGpioWrite(gpioChipH, 4, state ^= 1);
  }

  lgGpiochipClose(gpioChipH);
  exit(EXIT_SUCCESS);
}

int gpioSetup(int chipDev, const char* user) {
  int gpioChipH = lgGpiochipOpen(0);

  if (gpioChipH < 0) {
    perror("Could not open device");
    goto errh_exit;
  }

  if (lgGpioSetUser(gpioChipH, GPIO_USER) < 0) {
    perror("Could not set gpio-user");
    goto errh_closechip;
  }

  return gpioChipH;

// Err handling
errh_closechip:
  lgGpiochipClose(gpioChipH);

errh_exit:
  exit(EXIT_FAILURE);
}

void intHandler(int dummy) {
  // Can't lgchip close, var need to be in global scope
  printf("\nInterrupted by user\n");
  exit(EXIT_FAILURE);
};