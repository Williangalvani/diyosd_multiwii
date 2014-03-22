//#include "variables.h"

#ifndef gps_h
#define gps_h

#define set_home_delay 15

#include <Arduino.h>
//include "config.h"
void gps();
void do_multiwii_communication();
void serialRequest(uint8_t requestMSP, char *payload, char payloadsize);
void send_msp_set_pid();


#endif