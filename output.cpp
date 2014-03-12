
#include "config.h"
#include "ascii.h"
#include "output.h"
#include "variables.h"
#include "Arduino.h"
#include "Math.h"
#include "itoa.h"
#include <avr/delay.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>



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

#define output_small_letter(letter) SPDR = letters[((letter - 64) << 3) + (screen_line - 8)];
#define to_index(ch) (ch - 64) << 3;

unsigned char satellites[3] = {3, 3, 3};
unsigned char satellitesr[3] = {3, 3, 3};


extern unsigned char align_text;
extern unsigned char flight_timer[];

extern unsigned char show_plane_pos;
extern unsigned char show_mah_km;
extern unsigned char mahkmr[];
extern int mah_alarm;
extern int frame;
extern int homehead_r[];

extern long los;
extern int los_alarm;

extern long altitude_num2;
extern int alt_alarm;
extern unsigned char show_decimals;
extern int arrowd;
;
extern int volt_alarm;

extern int menuon;
extern char move_arrow_count;
extern unsigned char menupos;
extern unsigned char menu;
extern unsigned char altitude_offset_on;
extern char GPSbuffer[100];
extern char homepos;

extern char GPSfix;
extern uint8_t GPS_numSat;
extern int homeposcount;
extern unsigned char test;
extern unsigned char loadbar[];
extern unsigned char time[14];
extern unsigned char landed;
extern unsigned char max_altr[];
extern unsigned char max_speedr[];
extern unsigned char max_losr[];
extern unsigned char total_distancer[];
extern int current_num;
extern unsigned char arrowr[];
extern int altitude_negative;
extern unsigned char avg_speedr[];
extern int latitude[15];
extern unsigned char latitude_dir;
extern unsigned char longitude_dir;
extern int longitude[15];
extern unsigned char losr[];
extern unsigned char speedkmw[5];
extern unsigned char altitude2[10];
extern unsigned char altituder[10];

extern unsigned char text_buffer_bottom_mid[];
extern int success;
extern unsigned int speedkm;
extern int32_t GPS_altitude;

extern int updatedSpeed ;
extern int updatedArrow;
extern int updatedAlt;
extern int updatedDist;
extern int updatedVolt;
extern int updatedCur;
extern int updatedSats  ;
extern int updatedAtt  ;
extern int updatedAnalog;

extern int MwAngle[];
int horizon_lenght = 1;
char horizon_sprite = 1;
int horizon_repeat = 0;


unsigned char horizonBuffer[90];
unsigned char speedr[] = {1, 1, 1, 1};

extern unsigned char avg_speedr[];
int current_letter = 0;
unsigned char charcounter;

void print_large_3(int *buffer);
void print_large_5(int *buffer);
void serialMSPCheck();

void draw_arrow()
{
    SPDR = HomeArrow[buffer2[11] + 2 * screen_line];
    DimOn;
    delay13
    SPDR = HomeArrow[buffer2[11] + 2 * screen_line + 1];
    delay5;
    DimOff;

}

void write_speed()
{

    print_large_5(buffer3);
    delay15;
    DimOff
    //_delay_loop_1(25);



}

void print_altitude()
{

    _delay_loop_1(6);
    SPDR = LargeNumbers[buffer3[9] + 2 * screen_line];
    DimOn;
    delay13

    SPDR = LargeNumbers[buffer3[9] + 2 * screen_line + 1];
    delay8


    SPDR = LargeNumbers[buffer3[10] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer3[10] + 2 * screen_line + 1];
    delay8


    SPDR = LargeNumbers[buffer3[11] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer3[11] + 2 * screen_line + 1];
    delay8


    SPDR = LargeNumbers[buffer3[12] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer3[12] + 2 * screen_line + 1];
    delay8


    SPDR = LargeNumbers[buffer3[13] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer3[13] + 2 * screen_line + 1];
    delay15;

    SPDR = LargeNumbers[buffer3[14] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer3[14] + 2 * screen_line + 1];
    delay15;
    DimOff;


}

void print_large_3(int *buffer)
{

    SPDR = LargeNumbers[buffer[0] + 2 * screen_line];
    DimOn;
    delay13
    SPDR = LargeNumbers[buffer[0] + 2 * screen_line + 1];
    delay8

    SPDR = LargeNumbers[buffer[1] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[1] + 2 * screen_line + 1];
    delay8

    SPDR = LargeNumbers[buffer[2] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[2] + 2 * screen_line + 1];

}

void print_large_4(int *buffer)
{

    SPDR = LargeNumbers[buffer[0] + 2 * screen_line];
    DimOn;
    delay13

    SPDR = LargeNumbers[buffer[0] + 2 * screen_line + 1];
    delay8


    SPDR = LargeNumbers[buffer[1] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[1] + 2 * screen_line + 1];
    delay8;


    SPDR = LargeNumbers[buffer[2] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[2] + 2 * screen_line + 1];
    delay8


    SPDR = LargeNumbers[buffer[3] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[3] + 2 * screen_line + 1];
    delay5;
    DimOff;
}

void print_large_5(int *buffer)
{
    SPDR = LargeNumbers[buffer[0] + 2 * screen_line];
    DimOn;
    delay13

    SPDR = LargeNumbers[buffer[0] + 2 * screen_line + 1];
    delay8

    SPDR = LargeNumbers[buffer[1] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[1] + 2 * screen_line + 1];
    delay8;


    SPDR = LargeNumbers[buffer[2] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[2] + 2 * screen_line + 1];
    delay8

    SPDR = LargeNumbers[buffer[3] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[3] + 2 * screen_line + 1];
    delay8;

    SPDR = LargeNumbers[buffer[4] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[4] + 2 * screen_line + 1];
    delay5;
    DimOff;
}


void print_small_5(unsigned char *buffer)
{
    // Updates SPDR (SPI buffer)
    SPDR = letters[(buffer[0]) + (screen_line)];
    DimOn;
    // Adds delay before the SPI buffer can be updated again.
    delay12

    SPDR = letters[(buffer[1]) + (screen_line)];
    delay12

    SPDR = letters[(buffer[2]) + (screen_line)];
    delay13

    SPDR = letters[(buffer[3]) + (screen_line)];
    delay13

    SPDR = letters[(buffer[4]) + (screen_line)];
    delay13
    DimOff;
}

void print_small_3(unsigned char *buffer)
{

    SPDR = letters[(buffer[0]) + (screen_line)];
    DimOn;
    delay12

    SPDR = letters[(buffer[1]) + (screen_line)];
    delay13

    SPDR = letters[(buffer[2]) + (screen_line)];
    delay13
    DimOff;

}


void print_top_large_numbers()
{
    _delay_loop_1(align_text - 5);
    //_delay_loop_1(1);

    screen_line = line - (toplinenumbers + 1);

    if (line == toplinenumbers + 1)
    {

    }
    else
    {

        _delay_loop_1(3);

        // Writes Speed

        write_speed();

        // Here should be time to update the buffer for the arrow
        buffer2[11] = arrowd << 5;

        // Skriver LOS tal



        _delay_loop_1(8);

        print_large_4((int *)&buffer3[5]);

        _delay_loop_1(1);



        // Let's draw the arrow.

        draw_arrow();

        // Writes ALT

        print_altitude();
    }
}

void print_bottom_large_numbers()
{
    // Used to align the text
    _delay_loop_1(align_text    );

    screen_line = line - (butlinenumbers + 1);


    if (line == butlinenumbers + 1)
    {


    }
    else
    {
        //     _delay_loop_1(3);
        if (screen_line > 8)
        {
            delay5
            output_small_letter('C');
            DimOn;
            delay12

            output_small_letter('U');
            delay13

            output_small_letter('R');
            delay2
        }
        else
        {
            _delay_loop_1(16);
            delay3
        }

        print_large_4(buffer2);
        delay15;
        DimOff;



        _delay_loop_1(6);
        //              ==================================================

        if (screen_line > 8)
        {
            delay5
            output_small_letter('V');
            DimOn;
            delay12

            output_small_letter('A');
            delay13

            output_small_letter('R');
            delay5
        }
        else
        {
            _delay_loop_1(16);
            delay8
        }

        print_large_4(&buffer2[8]);



        // ======================================================


        _delay_loop_1(2);

        if (screen_line > 7)
        {
            output_small_letter('R');
            DimOn;
            delay13

            output_small_letter('S');
            delay15;

            output_small_letter('I');
            delay11
        }
        else
        {
            _delay_loop_1(19);
            delay1
        }

        print_large_4(&buffer2[4]);
        delay15;
        DimOff;


    }
}

void print_top_text()
{
    // Used to align the text
    _delay_loop_1(align_text - 8);

    screen_line = line - (toplinetext + 1);

    //_delay_loop_1(13);


    // Writes SPEED, which is the first 5 characters in the toptext array
    buffer[0] = (toptext[0]) << 3;
    buffer[1] = (toptext[1]) << 3;
    buffer[2] = (toptext[2]) << 3;
    buffer[3] = (toptext[3]) << 3;
    buffer[4] = (toptext[4]) << 3;


    print_small_5(buffer);


    // Writes LOS (The delay loop is used to place the LOS in the middle)
    _delay_loop_1(55);

    buffer[0] = (toptext[5]) << 3;
    buffer[1] = (toptext[6]) << 3;
    buffer[2] = (toptext[7]) << 3;

    print_small_3(buffer);

    // Writes ALT;
    _delay_loop_1(70);

    buffer[0] = (toptext[8]) << 3;
    buffer[1] = (toptext[9]) << 3;
    buffer[2] = (toptext[10]) << 3;

    print_small_3(buffer);
}

void detectframe()
{
    line = 0;
    //      frame++;
}
/*
void print_version()
{
    screen_line = line - (summaryline + 82);
    _delay_loop_1(20);

    buffer[0] = ('V' - 64) << 3;
    buffer[1] = ('E' - 64) << 3;
    buffer[2] = ('R' - 64) << 3;
    buffer[3] = ('S' - 64) << 3;
    buffer[4] = ('I' - 64) << 3;
    buffer[5] = ('O' - 64) << 3;
    buffer[6] = ('N' - 64) << 3;

    buffer[7] = (0 + 3) << 3;
    buffer[8] = (1 + 3) << 3;
    buffer[9] = (8 + 3) << 3;

    DimOn;
    for (unsigned char ij = 0; ij < 7; ij++)
    {
        SPDR = letters[buffer[ij] + (screen_line)];
        _delay_loop_1(2);
    }
    _delay_loop_1(6);


    SPDR = numbers[(buffer[7]) + (screen_line)];
    delay15;
    SPDR = numbers[8 + (screen_line)];
    delay15;
    SPDR = numbers[(buffer[8]) + (screen_line)];
    delay15;
    SPDR = numbers[(buffer[9]) + (screen_line)];
    delay15;
    DimOff
}


*/
void print_summary()
{

    // Used to align the text
    _delay_loop_1(align_text);


    if (menuon == 1)
    {
        //  print_menu();
    }
    else if (homepos == 0)
    {

        screen_line = line - (summaryline + 1);
        _delay_loop_1(17);
        if (screen_line < 8)
        {

            _delay_loop_1(65);

            buffer[0] = ('S' - 64) << 3;
            buffer[1] = ('A' - 64) << 3;
            buffer[2] = ('T' - 64) << 3;

            buffer[3] = satellitesr[0] << 3;
            buffer[4] = satellitesr[1] << 3;

            DimOn;
            for (unsigned char ij = 0; ij < 3; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(5);
            }

            // Writes ':'
            SPDR = numbers[104 + screen_line];
            _delay_loop_1(10);

            for (unsigned char ij = 3; ij < 5; ij++)
            {
                SPDR = numbers[buffer[ij] + (screen_line)];
                _delay_loop_1(5);
            }
            _delay_loop_1(2);
            DimOff;

        }


        if (screen_line > 10 && screen_line < 19)
        {
            screen_line = line - (summaryline + 12);
            _delay_loop_1(45);

            buffer[0] = ('G' - 64) << 3;
            buffer[1] = ('P' - 64) << 3;
            buffer[2] = ('S' - 64) << 3;
            buffer[3] = (0) << 3;
            buffer[4] = ('F' - 64) << 3;
            buffer[5] = ('I' - 64) << 3;
            buffer[6] = ('X' - 64) << 3;

            DimOn;
            for (unsigned char ij = 0; ij < 7; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(2);
            }

            SPDR = numbers[104 + screen_line];
            _delay_loop_1(6);

            if (GPSfix > '0')
            {
                buffer[0] = ('Y' - 64) << 3;
                buffer[1] = ('E' - 64) << 3;
                buffer[2] = ('S' - 64) << 3;

            }
            else
            {
                buffer[0] = ('N' - 64) << 3;
                buffer[1] = ('O' - 64) << 3;
                buffer[2] = ('@' - 64) << 3;


            }

            for (unsigned char ij = 0; ij < 3; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(4);
            }
            _delay_loop_1(3);
            DimOff;

        }


        if (screen_line == 19)
        {

            test = (homeposcount * 10) / set_home_delay;
            for (i = 0; i < test; i++)
            {
                loadbar[i] = 26;
            }
            // SPDR=0b11111110;

        }

        if (screen_line == 20)
        {


            for (unsigned char ij = 0; ij < 9; ij++)
            {
                buffer[ij] = (loadbar[ij]) << 3;
            }

            buffer[9] = (28) << 3;


            buffer[10] = ('D' - 64) << 3;
            buffer[11] = ('E' - 64) << 3;
            buffer[12] = ('L' - 64) << 3;
            buffer[13] = ('A' - 64) << 3;
            buffer[14] = ('Y' - 64) << 3;
        }



        if (screen_line > 31 && screen_line < 40)
        {
            screen_line = line - (summaryline + 33);
            _delay_loop_1(60);

            DimOn;
            for (unsigned char ij = 10; ij < 15; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(2);

            }
            _delay_loop_1(3);


            // Writes ':'
            SPDR = numbers[104 + screen_line];
            _delay_loop_1(9);

            DimOff;



        }

        if (screen_line > 42 && screen_line < 51)
        {

            _delay_loop_1(37);
            screen_line = line - (summaryline + 44);


            for (unsigned char ij = 0; ij < 10; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                DimOn;
                _delay_loop_1(3);
            }
            _delay_loop_1(1);
            DimOff;

        }

    }

}


void convert_to_big_numbers(unsigned char *chars, int *buffer_, char min_zeros, char digits)
{

    int i = 0;
    for (i = 0; i < (digits - min_zeros); i++)
    {
        if (chars[i] == 3)
        {
            buffer_[i] = 14 << 5;
        }
        else
        {
            break;
        }
    }
    for (; i < digits; i++)
    {
        buffer_[i] = chars[i] << 5;
    }

}


void render_top_numbers()
{
    convert_to_big_numbers(speedr, buffer3, 3, 5);

    convert_to_big_numbers(losr, &buffer3[5], 3, 5);

    convert_to_big_numbers(altituder, &buffer3[9], 1, 6);
}

void draw_horizon_point_at_line(int line)
{
    if (line == 1 || line == 89)
    {
        SPDR = 0b10101010;
        _delay_loop_1(align_text);
        int i;
        for (i = 0; i < 80 + 1; i++)
        {
            SPDR = 0b10101010;
            delay5;
        }

    }
    else if (line <= 5 || line >= 85)
    {
        _delay_loop_1(HORIZON_X_CENTER + 9);
        SPDR = 0b11111110;
    }
    else if (horizonBuffer[line] != 0)
    {

        _delay_loop_1(horizonBuffer[line] - horizon_repeat);
        
        int i = 0;
        if (horizon_repeat > 1)
        {
            horizon_sprite = 0b11111111;
        }

        for (i = 0; i < horizon_repeat + 2; i++)
        {
            SPDR = horizon_sprite;
            delay5;
        }
        DimOn;
        delay5;
        DimOff;
    }

    if (line == 43)
    {
        DimOn;
    }
    else if (line == 47)
    {
        DimOff;
    }
}

void print_gps_sats()
{
    screen_line = line - (gpsline + 1);
    _delay_loop_1(17);
    //_delay_loop_1(65);

    if (screen_line == 0)
    {
        buffer[0] = ('S' - 64) << 3;
        buffer[1] = ('A' - 64) << 3;
        buffer[2] = ('T' - 64) << 3;

        buffer[3] = satellitesr[0] << 3;
        buffer[4] = satellitesr[1] << 3;


        buffer[5] = ('G' - 64) << 3;
        buffer[6] = ('P' - 64) << 3;
        buffer[7] = ('S' - 64) << 3;
        buffer[8] = (0) << 3;
        buffer[9] = ('F' - 64) << 3;
        buffer[10] = ('I' - 64) << 3;
        buffer[11] = ('X' - 64) << 3;


        if (GPSfix > '0')
        {
            buffer[12] = ('Y' - 64) << 3;
            buffer[13] = ('E' - 64) << 3;
            buffer[14] = ('S' - 64) << 3;

        }
        else
        {
            buffer[12] = ('N' - 64) << 3;
            buffer[13] = ('O' - 64) << 3;
            buffer[14] = ('@' - 64) << 3;


        }

    }
    else
    {


        DimOn;
        for (unsigned char ij = 0; ij < 3; ij++)
        {
            SPDR = letters[buffer[ij] + (screen_line)];
            _delay_loop_1(5);
        }

        // Writes ':'
        SPDR = numbers[104 + screen_line];
        _delay_loop_1(10);

        for (unsigned char ij = 3; ij < 5; ij++)
        {
            SPDR = numbers[buffer[ij] + (screen_line)];
            _delay_loop_1(5);
        }
        _delay_loop_1(2);
        DimOff;

        /////////////now the fix///////////////
        _delay_loop_1(10);


        DimOn;
        for (unsigned char ij = 5; ij < 12; ij++)
        {
            SPDR = letters[buffer[ij] + (screen_line)];
            _delay_loop_1(2);
        }

        SPDR = numbers[104 + screen_line];
        _delay_loop_1(6);


        for (unsigned char ij = 12; ij < 15; ij++)
        {
            SPDR = letters[buffer[ij] + (screen_line)];
            _delay_loop_1(4);
        }
        _delay_loop_1(3);
        DimOff;
    }
}

extern uint8_t mode_armed;
extern uint8_t mode_stable;
extern uint8_t mode_horizon;
extern uint8_t mode_baro;
extern uint8_t mode_mag;
extern uint8_t mode_gpshome;
extern uint8_t mode_gpshold;
extern uint8_t mode_osd_switch;

void print_modes_sats()
{
    screen_line = line - (modesline + 1);
    _delay_loop_1(10);
    //_delay_loop_1(65);
    if (screen_line == 0)
    {
        buffer[0] = to_index('A');
        buffer[1] = to_index('R');
        buffer[2] = to_index('M');
        buffer[3] = to_index('E');
        buffer[4] = to_index('D');
        buffer[5] = to_index(' ');
        buffer[6] = to_index('L');
        buffer[7] = to_index('E');
        buffer[8] = to_index('V');
        buffer[9] = to_index('E');
        buffer[10] = to_index('L');
        buffer[11] = to_index(' ');
        buffer[12] = to_index('H');
        buffer[13] = to_index('O');
        buffer[14] = to_index('R');
        buffer[15] = to_index('I');
        buffer[16] = to_index('Z');
        buffer[17] = to_index('O');
        buffer[18] = to_index('N');
        buffer[19] = to_index(' ');
        buffer[20] = to_index('B');
        buffer[21] = to_index('A');
        buffer[22] = to_index('R');
        buffer[23] = to_index('O');
        buffer[24] = to_index(' ');
        buffer[25] = to_index('M');
        buffer[26] = to_index('A');
        buffer[27] = to_index('G');
        buffer[28] = to_index(' ');
        buffer[29] = to_index('R');
        buffer[30] = to_index('T');
        buffer[31] = to_index('H');
        buffer[32] = to_index(' ');
        buffer[33] = to_index('G');
        buffer[34] = to_index('P');
        buffer[35] = to_index('S');
        buffer[36] = to_index('H');
        buffer[37] = to_index('O');
        buffer[38] = to_index('L');
        buffer[39] = to_index('D');

    }
    else
    {

#define delaybetweenchars 2
#define delaybetweenwords 3
        DimOn;
        unsigned char ij;
        if (mode_armed)
        {
            for (ij = 0; ij <= 4; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(delaybetweenchars);
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_stable)
        {
            for (ij = 6; ij <= 10; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(delaybetweenchars);
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_horizon)
        {
            for (ij = 12; ij <= 18; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(delaybetweenchars);
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_baro)
        {
            for (ij = 20; ij <= 23; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(delaybetweenchars);
                delay3;
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_mag)
        {
            for (ij = 25; ij <= 27; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(delaybetweenchars);
                delay5;
            }
            _delay_loop_1(delaybetweenwords);

        }        
        if (mode_gpshome)
        {
            for (ij = 29; ij <= 31; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(delaybetweenchars);
                delay5;
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_gpshold)
        {
            for (ij = 33; ij <= 39; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(delaybetweenchars);
            }
            _delay_loop_1(delaybetweenwords);

        }



        DimOff;

    }

}




void render_bottom_numbers()
{

    _delay_loop_1(align_text);
    convert_to_big_numbers(currentr, buffer2, 3, 4);
    convert_to_big_numbers(mahr, &buffer2[4], 1, 4);
    convert_to_big_numbers(text_buffer_bottom_mid, &buffer2[8], 1, 4);



    screen_line = (arrowr[0] - 3) * 100 + (arrowr[1] - 3) * 10 + (arrowr[0] - 3);
    _delay_loop_1(align_text);

}

unsigned char extracted_digits[] = {0, 0, 0, 0, 0, 0};
int last_converted;


char extract_digit(int number, char char_number)
{
    int i = 0;

    if (number == last_converted)
    {
        return extracted_digits[char_number];
    }
    else
    {
        extracted_digits[0] = 0;
        extracted_digits[1] = 0;
        extracted_digits[2] = 0;
        extracted_digits[3] = 0;
        extracted_digits[4] = 0;
        extracted_digits[5] = 0;
        last_converted = number;

        while (number > 10)
        {
            extracted_digits[i] = number % 10;
            i++;
            number /= 10;
        }
    }
    extracted_digits[i] = number;

    return extracted_digits[char_number];


    //return char_number;
}

void copy_to_buffer(int var, unsigned char *buffera, int digits, int is_decimal)
{
    // converts a decimal number to ascii indexes and injects to buffer
    //
    digits--;
    int index = 0;
    int is_negative = 0;
    if (var < 0)
    {
        buffera[0] = 0;
        index++;
        var = abs(var);
        is_negative = 1;
    }

    int chars = digits - index;
    int gotdec = 0;
    for (; chars >= 0; chars--)
    {
        int currentchar = digits - chars;
        if ((is_decimal) && (chars == 1))
        {
            buffera[currentchar] = 1;
            gotdec = 1;
        }
        else
        {
            buffera[currentchar] = extract_digit(var, chars + gotdec + !is_decimal - 1) + 3;
        }
    }
}

void print_horizon()
{
    draw_horizon_point_at_line(line - summaryline);

}
int update_counter = 0;

extern uint16_t mwcurrent;
extern uint16_t rssi;
extern uint8_t GPS_fix;
extern int16_t vario;
uint16_t totalmsg = 0;
void update_data()
{
    if (updatedAnalog)
    {
        int curvar = totalmsg;
        /*currentr[3] = (curvar % 10 + 3);
        currentr[2] = (curvar % 100) / 10 + 3;
        currentr[1] = (((curvar % 1000) / 100) + 3);
        currentr[0] = (curvar / 1000 + 3);
        */copy_to_buffer(curvar, currentr, 4, AS_DECIMAL);


        copy_to_buffer(rssi, mahr, 4, AS_INTEGER);
        updatedAnalog = 0;

    }
    if (updatedVolt)
    {
        int voltvar = vario;
        /*if (voltvar < 0)
        {
            text_buffer_bottom_mid[0] = 0;
        }
        else
        {
            text_buffer_bottom_mid[0] = 3;
        }
        voltvar = abs(voltvar);
        text_buffer_bottom_mid[3] =  (voltvar % 10 + 3);
        text_buffer_bottom_mid[2] = (voltvar % 100) / 10 + 3;
        text_buffer_bottom_mid[1] = (((voltvar % 1000) / 100) + 3);*/
        copy_to_buffer(voltvar, text_buffer_bottom_mid, 4, AS_INTEGER);
        //text_buffer_bottom_mid[0] = (voltvar / 1000 + 3);


        updatedVolt = 0;
    }
    if (updatedSats)
    {
        satellitesr[0] = (GPS_numSat / 10) + 3 ;
        satellitesr[1] = (GPS_numSat % 10) + 3;
        updatedSats = 0;
    }

    ///convert los, one piece at a time
    if (updatedDist)
    {
        copy_to_buffer(los, losr, 4, AS_INTEGER);
        updatedDist = 0;
    }
    ///convert speed, one piece at a time
    if (updatedSpeed)
    {
        copy_to_buffer(speedkm, speedr, 5, AS_DECIMAL);
        updatedSpeed = 0;
    }
    if (updatedAlt)
    {
        copy_to_buffer(GPS_altitude, altituder, 6 , AS_INTEGER);
        /*
        altituder[4] =  (GPS_altitude % 10 + 3);
        altituder[3] = (GPS_altitude % 100) / 10 + 3;
        altituder[2] = (((GPS_altitude % 1000) / 100) + 3);
        altituder[1] = (GPS_altitude / 1000 + 3);
        updatedAlt = 0;*/
    }
    if (updatedAtt)
    {
        /*
           we are working with inverted axes here, to fuck up my brain
           */
        // pixel =offset + angular_coef * line
        //offset = pixel -angular_coef*line;

        //int reducedPitchAngle = MwAngle[1]/1.5;
        double radians = radians(-MwAngle[0] + 180);
        double cossine = cos(radians);
        float angular_coef = 1 / tan(radians);
        float linear_coef = 45 - (45 - MwAngle[1]) * angular_coef;
        int j;

        //x = y*a + b
        //y*a = -b
        //y = -b/a

        int first = abs(-linear_coef / angular_coef);
        horizon_lenght = (abs((int)angular_coef)) * 2;
        for (j = 4; j < 86; j++)
        {
            float temp = linear_coef + j * angular_coef + HORIZON_X_CENTER - 45;
            if (temp > 0 && temp + horizon_lenght < 250)
            {
                horizonBuffer[j] = temp;
            }
            else
            {
                horizonBuffer[j] = 0;
            }
        }
        int roll = MwAngle[0];
        int pitch = MwAngle[1];
        if ( roll == 0 && pitch < 43 && pitch > -43  )
        {
            horizon_lenght = 350;
            horizonBuffer[45 - pitch] = 70;
            horizonBuffer[45 - pitch + 1] = 70;
        }
        if (horizon_lenght > 350)
        {
            horizon_lenght = 350;
        }
        horizon_repeat = horizon_lenght / 8;
        horizon_lenght = horizon_lenght % 8;
        if (horizon_lenght < 3)
        {
            horizon_lenght = 3;
        }
        horizon_sprite = (1 << horizon_lenght) - 2;

        updatedAtt = 0;
    }

}


extern int should_process_now;
int msgcounter = 0;
void blankserialRequest(uint8_t requestMSP);

void send_serial_request()
{
    totalmsg++;
    msgcounter++;
    if (msgcounter >= 6)
    {
        blankserialRequest(MSP_COMP_GPS);
        msgcounter = 0;
    }
    else if (msgcounter == 1)
    {
        blankserialRequest(MSP_ATTITUDE);
    }
    else if (msgcounter == 2 )
    {
        blankserialRequest(MSP_RAW_GPS);
    }
    else if (msgcounter == 3 )
    {
        blankserialRequest(MSP_ANALOG);
    }
    else if (msgcounter == 4 )
    {
        blankserialRequest(MSP_ALTITUDE);
    }
    else if (msgcounter == 5 )
    {
        blankserialRequest(MSP_STATUS);
    }

}

void detectline()
{
    //UCSR0B &= ~(1 << RXCIE0);
    little_delay // This is used to adjust to timing when using SimpleOSD instead of Arduino



    if (line == serial_line)
    {
        //UCSR0B |= (1 << RXCIE0);
        send_serial_request();

    }
    if (line > toplinenumbers && line < (toplinenumbers + 17))
    {
        print_top_large_numbers();
    }
    else if (line > gpsline && line < (gpsline + 9 ))
    {
        print_gps_sats();
    }
    else if (line > modesline && line < (modesline + 9 ))
    {
        print_modes_sats();
    }

    else if (line > butlinenumbers && line < (butlinenumbers + 17))
    {
        print_bottom_large_numbers();
    }
    else if (line > toplinetext && line < (toplinetext + 9))
    {
        print_top_text();
    }
    else if (line > summaryline && line < (summaryline + 90))
    {

        print_horizon();

        //print_summary();
    }
    /*else if (line > gps_nmea_line && line < (gps_nmea_line + 9))
    {
        print_gps();
    }*/
    else if (line == toplinenumbers)
    {
        render_top_numbers();
    }    // ============================================================
    // Buttom line text
    // ============================================================

    else if (line == butlinenumbers)
    {
        render_bottom_numbers();
    }

    //else if (line >= current_calc_line && line <= current_calc_line+20)

    line++;


    // Let's make sure SPI is not idling high.
    SPDR = 0b00000000;
    // UCSR0B |= (1 << RXCIE0);

}


