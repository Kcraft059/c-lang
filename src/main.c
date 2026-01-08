#include <lgpio.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  char* endPtr = argv[0];
  double chipNum = strtod(argv[0], &endPtr);

  int gpioH = lgGpiochipOpen(chipNum);

  if (gpioH < 0) {
    perror("Bruh (no dev)");
    exit(EXIT_FAILURE);
  }

}