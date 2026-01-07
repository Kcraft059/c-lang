#include "time.h"
#include <lgpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GPIOCHIP 0

int main(int argc, char** argv) {
  int gpioH;
  if ((gpioH = lgGpiochipOpen(GPIOCHIP)) < 0) {
    perror("Can't open device. (You must be priviledged)");
    goto err_exit;
  }

  int rgbPins[3] = {4, 13, 19};
  lgGroupClaimOutput(gpioH, 0, 3, rgbPins, 0);
  
  if (lgTxPwm(gpioH, rgbPins[0], 10000, 10, 0, 0) < 0) {
    perror("Couldn't start PWM");
    goto err_free;
  }

  while (1);

  /* for (int i = 0; i < 100; i++) {
    if (lgTxPwm(gpioH, rgbPins[0], i * 10, 50, 0, 0) < 0) {
      perror("Couldn't start PWM");
      goto err_free;
    }

    nanosleep(&(struct timespec){0, 50000000}, NULL);
  } */

  return 0;

// Error handling
err_free:
  lgGroupFree(gpioH, rgbPins[0]);
  lgGpiochipClose(gpioH);

err_exit:
  return EXIT_FAILURE;
}
