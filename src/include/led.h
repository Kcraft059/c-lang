// Data types
typedef struct{
  int gpioH;
  int pin;
} led;

typedef struct {
  int gpioH;
  int rPin;
  int gPin;
  int bPin;
} ledrgb;

// Functions

int initGpio();