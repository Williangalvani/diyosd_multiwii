//#include "variables.h"

#ifndef output_h
#define output_h

void detectframe();
void detectline();
void serialMSPreceive();
void update_data();
void clear_menu();
void copy_to_buffer(int var, unsigned char *buffera, int digits, int is_decimal);
void copy_to_buffer2(int var, unsigned char *buffera, int digits, int is_decimal);

#define True 1
#define False 0

#define MSP_STATUS               101   //out message         cycletime & errors_count & sensor present & box activation & current setting number
#define MSP_RAW_GPS              106   //out message         fix, numsat, lat, lon, alt, speed, ground course
#define MSP_COMP_GPS             107   //out message         distance home, direction home
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ALTITUDE             109   //out message         altitude, variometer
#define MSP_ANALOG               110   //out message         vbat, powermetersum, rssi if available on RX

#define AS_DECIMAL 1
#define AS_INTEGER 0

#define THREE_CHARS 3
#define FOUR_CHARS 4
#define FIVE_CHARS 5

//#define output_small_letter(letter) SPDR = letters[((letter - 64) << 3) + (screen_line - 8)];
//#define output_small_byte(byte) SPDR = letters[byte + (screen_line)];
#define output_small_letter(letter) SPDR = pgm_read_byte_near(&letters[((letter - 64) << 3) + (screen_line - 8)]);
#define output_small_byte(byte) SPDR = pgm_read_byte_near(&letters[byte + (screen_line)]);
#define output_small_byte_line(byte, aline) SPDR = pgm_read_byte_near(&letters[byte + (aline)]);

#define to_index(ch) (ch - 64) << 3;

//#define output_big_number_left_part(buffer) SPDR = LargeNumbers[buffer + 2 * screen_line];
//#define output_big_number_right_part(buffer) SPDR = LargeNumbers[buffer + 2 * screen_line + 1];

#define output_big_number_left_part(buffer) SPDR = pgm_read_byte_near(&LargeNumbers[buffer + 2 * screen_line]);
#define output_big_number_right_part(buffer) SPDR = pgm_read_byte_near(&LargeNumbers[buffer + 2 * screen_line + 1]);


#define delaybetweenchars 1
#define delaybetweenwords 2

#define small_arrow_left  ('a' - 64) << 3;

#endif
