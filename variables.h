
#ifndef __variables_H
#define __variables_H
#include "Arduino.h"
#include <avr/pgmspace.h>

#define MSP_STATUS               101   //out message         cycletime & errors_count & sensor present & box activation & current setting number
#define MSP_RAW_GPS              106   //out message         fix, numsat, lat, lon, alt, speed, ground course
#define MSP_COMP_GPS             107   //out message         distance home, direction home
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ANALOG               110
#define MSP_ALTITUDE             109   //out message         altitude, variometer
#define MSP_RC                   105
#define MSP_PID                  112
#define MSP_SET_PID              202

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

extern unsigned char text_buffer_bottom_mid[];
extern long los;           // home distance
extern long altitude_num2;
extern int arrowd;  // arrow direction


extern int menuon;

extern unsigned char altitude_offset_on;

extern char homepos;
extern char GPSfix;
extern uint8_t GPS_numSat;

extern const unsigned char menu_intro[];
extern int current_num;
extern int altitude_negative;
extern unsigned char avg_speedr[];

extern unsigned char text_buffer_bottom_mid[];
extern int success;
extern unsigned int GPS_speed;
extern int32_t GPS_altitude;
extern uint16_t vbat;
extern char updatedSpeed ;
//extern int updatedArrow;
extern char updatedAlt;
extern char updatedDist;
extern char updatedVolt;
extern char updatedCur;
extern char updatedSats  ;
extern char updatedAtt  ;
extern char updatedAnalog;
extern char updated_clock;
extern char pid_reloaded_flag;
extern char printing_numbers;

extern int MwAngle[];
extern unsigned char avg_speedr[];


extern uint8_t mode_armed;
extern uint8_t mode_stable;
extern uint8_t mode_horizon;
extern uint8_t mode_baro;
extern uint8_t mode_mag;
extern uint8_t mode_gpshome;
extern uint8_t mode_gpshold;
extern uint8_t mode_osd_switch;

extern uint16_t mwcurrent;
extern uint16_t rssi;
extern uint16_t percentrssi;
extern uint8_t GPS_fix;
extern int16_t vario;

extern unsigned char menuBuffer[91];
extern unsigned char menu_dim[10];

extern int16_t relativedir;
extern int16_t rcData[12];
extern char left;
extern char right;
extern char up;
extern char down;
extern char rc_updated_flag;

extern uint8_t confP[10];
extern uint8_t confI[10];
extern uint8_t confD[10];


extern unsigned char customMessage;
extern char* data ;
extern char data_length ;

extern int minutes;
extern int seconds ;
extern uint8_t frame_counter;

#endif
