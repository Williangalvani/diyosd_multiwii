
#ifndef __variables_H
#define __variables_H
extern unsigned char text_buffer_bottom_mid[];
extern long los;           // home distance
extern long altitude_num2;
extern int arrowd;  // arrow direction


extern int menuon;

extern unsigned char altitude_offset_on;

extern char homepos;
extern char GPSfix;
extern uint8_t GPS_numSat;

extern int current_num;
extern int altitude_negative;
extern unsigned char avg_speedr[];

extern unsigned char text_buffer_bottom_mid[];
extern int success;
extern unsigned int GPS_speed;
extern int32_t GPS_altitude;

extern char updatedSpeed ;
//extern int updatedArrow;
extern char updatedAlt;
extern char updatedDist;
extern char updatedVolt;
extern char updatedCur;
extern char updatedSats  ;
extern char updatedAtt  ;
extern char updatedAnalog;

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
extern uint8_t GPS_fix;
extern int16_t vario;

extern int16_t relativedir;
extern int16_t rcData[12];


#endif
