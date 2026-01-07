#include <stdint.h>
#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
  ((byte) & 0x80 ? '1' : '0'),     \
      ((byte) & 0x40 ? '1' : '0'), \
      ((byte) & 0x20 ? '1' : '0'), \
      ((byte) & 0x10 ? '1' : '0'), \
      ((byte) & 0x08 ? '1' : '0'), \
      ((byte) & 0x04 ? '1' : '0'), \
      ((byte) & 0x02 ? '1' : '0'), \
      ((byte) & 0x01 ? '1' : '0')

static inline int8_t setBit(int8_t mask, int value, int8_t byte);

int main() {
  int8_t byte = 0b11101101;

  byte = setBit(0b10011011, 1, byte);

  printf("Bin: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(byte));
};

static inline int8_t setBit(int8_t mask, int value, int8_t byte) {
  switch (value) {
  case 0:
    return byte & ~mask;
  case 1:
    return byte | mask;
  default:
    return byte;
  }
}
