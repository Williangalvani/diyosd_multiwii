
#include "Arduino.h"

#define analog_reference 1
int analogRead(uint8_t pin);
int startRead(uint8_t pin);

int read_is_done();
int read_value();