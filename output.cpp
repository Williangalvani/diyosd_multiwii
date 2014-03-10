
#include "config.h"
#include "ascii.h"
#include "output.h"
#include "variables.h"
#include "Arduino.h"
#include "Math.h"
#include <avr/delay.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

#define True 1
#define False 0

#define MSP_RAW_GPS              106   //out message         fix, numsat, lat, lon, alt, speed, ground course
#define MSP_COMP_GPS             107   //out message         distance home, direction home
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ALTITUDE             109   //out message         altitude, variometer
#define MSP_ANALOG               110   //out message         vbat, powermetersum, rssi if available on RX


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

extern unsigned char voltager[];
extern int success;
extern unsigned int speedkm;
extern int16_t GPS_altitude;

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
extern int temp1;

void print_large_3(unsigned int *buffer);
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

    if (show_decimals == 1)
    {
        print_large_3(buffer3);


        if (buffer3[3] != 448)
        {
            delay2
            SPDR = LargeNumbers[buffer3[3] + 2 * screen_line];
            delay15;

            SPDR = LargeNumbers[buffer3[3] + 2 * screen_line + 1];
            delay4
        }
        else
        {
            DimOff;
            _delay_loop_1(10);
            delay1
        }

        if (buffer3[4] != 448)
        {
            SPDR = LargeNumbers[buffer3[4] + 2 * screen_line];
            delay15;

            SPDR = LargeNumbers[buffer3[4] + 2 * screen_line + 1];
            delay15;
            DimOff;
        }
        else
        {
            DimOff;
            _delay_loop_1(13);
        }



    }
    else
    {
        print_large_3(buffer3);
        delay15;

        _delay_loop_1(25);


    }
}

void print_altitude()
{
    if (show_decimals == 1)
    {
        //              _delay_loop_1(13);

        if (buffer3[9] != 448)
        {
            SPDR = LargeNumbers[buffer3[9] + 2 * screen_line];
            DimOn;
            delay13

            SPDR = LargeNumbers[buffer3[9] + 2 * screen_line + 1];
            //               delay4
        }
        else
        {
            _delay_loop_1(10);
        }

        if (buffer3[10] != 448)
        {
            SPDR = LargeNumbers[buffer3[10] + 2 * screen_line];
            DimOn;
            delay13

            SPDR = LargeNumbers[buffer3[10] + 2 * screen_line + 1];
            //               delay4
        }
        else
        {
            _delay_loop_1(10);
        }

        if (buffer3[11] != 448)
        {
            SPDR = LargeNumbers[buffer3[11] + 2 * screen_line];
            DimOn;
            delay13

            SPDR = LargeNumbers[buffer3[11] + 2 * screen_line + 1];
            delay8
        }
        else
        {
            _delay_loop_1(10);
            delay4
        }

        SPDR = LargeNumbers[buffer3[12] + 2 * screen_line];
        DimOn;
        delay13

        SPDR = LargeNumbers[buffer3[12] + 2 * screen_line + 1];
        delay8


        SPDR = LargeNumbers[buffer3[13] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer3[13] + 2 * screen_line + 1];
        delay8


        SPDR = LargeNumbers[buffer3[14] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer3[14] + 2 * screen_line + 1];
        delay15;
        DimOff;
    }
    else
    {
        _delay_loop_1(37);
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
        delay15;
        DimOff;
    }

}

void print_large_3(unsigned int *buffer)
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
    delay15;

    SPDR = LargeNumbers[64 + 2 * screen_line];
    delay8


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

void print_large_4u(unsigned int *buffer)
{
    SPDR = LargeNumbers[buffer[0] + 2 * screen_line];
    DimOn;
    delay13

    SPDR = LargeNumbers[buffer[0] + 2 * screen_line + 1];
    delay8

    SPDR = LargeNumbers[buffer[1] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[1] + 2 * screen_line + 1];
    delay15;

    SPDR = LargeNumbers[64 + 2 * screen_line];
    delay8


    SPDR = LargeNumbers[buffer[2] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[2] + 2 * screen_line + 1];
    delay8

    SPDR = LargeNumbers[buffer[3] + 2 * screen_line];
    delay15;

    SPDR = LargeNumbers[buffer[3] + 2 * screen_line + 1];
    delay10;
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


void print_timer()
{
    if (line > timer_line && line < (timer_line + 17))
    {
        //
        //      PRINTING TOP TEXT
        // Used to align the text
        _delay_loop_1(align_text);
        screen_line = line - (timer_line + 1);
        // On first line we update the buffer
        if (line == timer_line + 1)
        {
            // first line, isolating numbers
            /*
            buffer2[0] = (flight_timer[0]) << 5;
            buffer2[1] = (flight_timer[1]) << 5;
            buffer2[2] = (flight_timer[2]) << 5;
            buffer2[3] = (flight_timer[3]) << 5;
            */
            if (show_mah_km == 1 || show_rssi == 1)
            {
                /*               if (show_rssi == 1)
                               {
                                   mahkmr[0] = 3;
                                   mahkmr[1] = rssir[0];
                                   mahkmr[2] = rssir[1];
                                   mahkmr[3] = rssir[2];
                               }
                               if (mahkmr[0] == 3 && mahkmr[1] == 3 && mahkmr[2] == 3)
                               {
                                   mahkm_buf[0] = 14 << 5;
                                   mahkm_buf[1] = 14 << 5;
                                   mahkm_buf[2] = 14 << 5;
                                   mahkm_buf[3] = (mahkmr[3]) << 5;
                               }
                               else if (mahkmr[0] == 3 && mahkmr[1] == 3)
                               {
                                   mahkm_buf[0] = 14 << 5;
                                   mahkm_buf[1] = 14 << 5;
                                   mahkm_buf[2] = (mahkmr[2]) << 5;
                                   mahkm_buf[3] = (mahkmr[3]) << 5;
                               }
                               else if (mahkmr[0] == 3)
                               {
                                   mahkm_buf[0] = 14 << 5;
                                   mahkm_buf[1] = (mahkmr[1]) << 5;
                                   mahkm_buf[2] = (mahkmr[2]) << 5;
                                   mahkm_buf[3] = (mahkmr[3]) << 5;
                               }
                               else
                               {
                                   mahkm_buf[0] = (mahkmr[0]) << 5;
                                   mahkm_buf[1] = (mahkmr[1]) << 5;
                                   mahkm_buf[2] = (mahkmr[2]) << 5;
                                   mahkm_buf[3] = (mahkmr[3]) << 5;
                               }

                               if (rssi_negative == 1 && show_rssi == 1)
                               {
                                   mahkm_buf[0] = 13 << 5;
                               }*/
            }
            //SPDR = 0b11111110;
        }
        else
        {
            _delay_loop_1(6);
            print_large_4(buffer2);

            _delay_loop_1(84);
            delay1

            if (show_mah_km == 1 || show_rssi == 1)
            {

                _delay_loop_1(41); // 126
                delay1
                print_large_4u(mahkm_buf);
            }
            if (show_rssi == 1)
            {
            }
        }

    }
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


        if (buffer3[5] != 448)
        {
            SPDR = LargeNumbers[buffer3[5] + 2 * screen_line];
            DimOn;
            delay13

            SPDR = LargeNumbers[buffer3[5] + 2 * screen_line + 1];
            delay4
        }
        else
        {
            _delay_loop_1(12);
        }

        SPDR = LargeNumbers[buffer3[6] + 2 * screen_line];
        DimOn;
        delay13

        SPDR = LargeNumbers[buffer3[6] + 2 * screen_line + 1];
        delay8


        SPDR = LargeNumbers[buffer3[7] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer3[7] + 2 * screen_line + 1];
        delay8

        if (buffer3[8] != 448)
        {
            SPDR = LargeNumbers[buffer3[8] + 2 * screen_line];
            delay15;

            SPDR = LargeNumbers[buffer3[8] + 2 * screen_line + 1];
            delay15;
            DimOff;
        }
        else
        {
            DimOff;
            _delay_loop_1(14);
        }


        // Let's draw the arrow.

        draw_arrow();

        // Writes ALT

        print_altitude();
    }
}

void print_bottom_large_numbers()
{
    // Used to align the text
    _delay_loop_1(align_text + 5);

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
            SPDR = letters[(('C' - 64) << 3) + (screen_line - 8)];
            DimOn;
            delay12

            SPDR = letters[(('U' - 64) << 3) + (screen_line - 8)];
            delay13

            SPDR = letters[(('R' - 64) << 3) + (screen_line - 8)];
            delay2
        }
        else
        {
            _delay_loop_1(16);
            delay3
        }

        SPDR = LargeNumbers[buffer2[0] + 2 * screen_line];
        DimOn;
        delay13

        SPDR = LargeNumbers[buffer2[0] + 2 * screen_line + 1];
        delay8

        SPDR = LargeNumbers[buffer2[1] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer2[1] + 2 * screen_line + 1];
        delay15;

        SPDR = LargeNumbers[480 + 2 * screen_line];
        delay8
        //               SPDR = LargeNumbers[32+2*temp+1];
        //               delay13

        SPDR = LargeNumbers[buffer2[2] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer2[2] + 2 * screen_line + 1];
        delay15;
        DimOff;



        _delay_loop_1(14);
        //              ==================================================

        if (screen_line > 8)
        {
            delay5
            SPDR = letters[(22 << 3) + (screen_line - 8)];
            DimOn;
            delay12

            SPDR = letters[(12 << 3) + (screen_line - 8)];
            delay13

            SPDR = letters[(20 << 3) + (screen_line - 8)];
            delay5
        }
        else
        {
            _delay_loop_1(16);
            delay8
        }

        SPDR = LargeNumbers[buffer2[8] + 2 * screen_line];
        DimOn;
        delay13

        SPDR = LargeNumbers[buffer2[8] + 2 * screen_line + 1];
        delay8

        SPDR = LargeNumbers[buffer2[9] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer2[9] + 2 * screen_line + 1];
        delay15;
        delay2

        SPDR = LargeNumbers[480 + 2 * screen_line];
        delay8

        SPDR = LargeNumbers[buffer2[10] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer2[10] + 2 * screen_line + 1];
        delay15;
        DimOff;



        // ======================================================


        _delay_loop_1(20);

        if (screen_line > 7)
        {
            SPDR = letters[(('R' - 64) << 3) + (screen_line - 8)];
            DimOn;
            delay13

            SPDR = letters[(('S' - 64) << 3) + (screen_line - 8)];
            delay15;

            SPDR = letters[(('I' - 64) << 3) + (screen_line - 8)];
            delay11
        }
        else
        {
            _delay_loop_1(19);
            delay1
        }


        SPDR = LargeNumbers[buffer2[4] + 2 * screen_line];
        DimOn;
        delay15;

        SPDR = LargeNumbers[buffer2[4] + 2 * screen_line + 1];
        delay8


        SPDR = LargeNumbers[buffer2[5] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer2[5] + 2 * screen_line + 1];
        delay8


        SPDR = LargeNumbers[buffer2[6] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer2[6] + 2 * screen_line + 1];
        delay8


        SPDR = LargeNumbers[buffer2[7] + 2 * screen_line];
        delay15;

        SPDR = LargeNumbers[buffer2[7] + 2 * screen_line + 1];
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
void print_menu()
{

    if (line == summaryline + 1)
    {
        move_arrow_count++;
        if (move_arrow_count == 30)
        {
            move_arrow_count = 0;

            menupos++;
            if (menupos > 7)
            {
                menupos = 1;
            }
        }
    }

    if (menu == 1)
    {

        screen_line = line - (summaryline + 1);
        _delay_loop_1(13);

        if (screen_line < 8)
        {


            if (screen_line == 0)
            {
                buffer[0] = ('M' - 64) << 3;
                buffer[1] = ('A' - 64) << 3;
                buffer[2] = ('H' - 64) << 3;
                buffer[3] = (0) << 3;
                buffer[4] = ('K' - 64) << 3;
                buffer[5] = ('M' - 64) << 3;
                buffer[6] = (0) << 3;
            }
            else
            {
                _delay_loop_1(40);
                if (menupos == 1)
                {
                    SPDR = 0b11111100;
                    numbers[0 + (screen_line)];
                    _delay_loop_1(3);
                }
                else
                {
                    SPDR = 0b00000000;
                    _delay_loop_1(3);
                }

                DimOn;
                for (unsigned char ij = 0; ij < 6; ij++)
                {
                    SPDR = letters[buffer[ij] + (screen_line)];
                    _delay_loop_1(2);
                }

                _delay_loop_1(45);
                buffer[8] = (show_mah_km + 3) << 3;
                SPDR = numbers[buffer[8] + (screen_line)];
                _delay_loop_1(3);

                DimOff;
            }

        }
        else if (screen_line > 10 && screen_line < 19)
        {
            screen_line = line - (summaryline + 12);
            _delay_loop_1(27);


            buffer[0] = ('D' - 64) << 3;
            buffer[1] = ('E' - 64) << 3;
            buffer[2] = ('C' - 64) << 3;
            buffer[3] = ('I' - 64) << 3;
            buffer[4] = ('M' - 64) << 3;
            buffer[5] = ('A' - 64) << 3;
            buffer[6] = ('L' - 64) << 3;
            buffer[7] = ('S' - 64) << 3;
            buffer[8] = (0) << 3;
            buffer[9] = (0) << 3;

            if (menupos == 2)
            {
                SPDR = 0b11111100; //numbers[0+(temp)];
                _delay_loop_1(3);
            }
            else
            {
                SPDR = 0b00000000;
                _delay_loop_1(3);
            }

            DimOn;
            for (unsigned char ij = 0; ij < 8; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(2);
            }

            _delay_loop_1(31);
            buffer[8] = (show_decimals + 3) << 3;
            SPDR = numbers[buffer[8] + (screen_line)];
            delay14

            DimOff;



        }
        else if (screen_line > 20 && screen_line < 29)
        {
            screen_line = line - (summaryline + 22);
            _delay_loop_1(24);


            buffer[0] = ('A' - 64) << 3;
            buffer[1] = ('L' - 64) << 3;
            buffer[2] = ('T' - 64) << 3;
            buffer[3] = (0) << 3;
            buffer[4] = ('O' - 64) << 3;
            buffer[5] = ('F' - 64) << 3;
            buffer[6] = ('F' - 64) << 3;
            buffer[7] = ('S' - 64) << 3;
            buffer[8] = ('E' - 64) << 3;
            buffer[9] = ('T' - 64) << 3;

            if (menupos == 3)
            {
                SPDR = 0b11111100; //numbers[0+(temp)];
                _delay_loop_1(3);
            }
            else
            {
                SPDR = 0b00000000;
                _delay_loop_1(3);
            }

            DimOn;
            for (unsigned char ij = 0; ij < 10; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(2);
            }

            _delay_loop_1(19);
            buffer[8] = (altitude_offset_on + 3) << 3;
            SPDR = numbers[buffer[8] + (screen_line)];
            delay14

            DimOff;




        }


        else if (screen_line > 30 && screen_line < 39)
        {
            screen_line = line - (summaryline + 32);

            if (screen_line == 0)
            {
                buffer[10] = ((align_text / 10) + 3) << 3;
                buffer[11] = ((align_text % 10) + 3) << 3;
            }
            else
            {
                _delay_loop_1(19);

                buffer[0] = ('T' - 64) << 3;
                buffer[1] = ('E' - 64) << 3;
                buffer[2] = ('X' - 64) << 3;
                buffer[3] = ('T' - 64) << 3;
                buffer[4] = (0) << 3;
                buffer[5] = ('A' - 64) << 3;
                buffer[6] = ('L' - 64) << 3;
                buffer[7] = ('I' - 64) << 3;
                buffer[8] = ('G' - 64) << 3;
                buffer[9] = ('N' - 64) << 3;

                if (menupos == 4)
                {
                    SPDR = 0b11111100; //numbers[0+(temp)];
                    _delay_loop_1(3);
                }
                else
                {
                    SPDR = 0b00000000;
                    _delay_loop_1(3);
                }

                DimOn;
                for (unsigned char ij = 0; ij < 10; ij++)
                {
                    SPDR = letters[buffer[ij] + (screen_line)];
                    _delay_loop_1(2);
                }


                _delay_loop_1(15);
                SPDR = numbers[buffer[10] + (screen_line)];
                delay15;
                SPDR = numbers[buffer[11] + (screen_line)];
                delay14

                DimOff;

            }

        }
        else if (screen_line > 40 && screen_line < 49)
        {
            screen_line = line - (summaryline + 42);
            _delay_loop_1(18);

            buffer[0] = ('P' - 64) << 3;
            buffer[1] = ('L' - 64) << 3;
            buffer[2] = ('A' - 64) << 3;
            buffer[3] = ('N' - 64) << 3;
            buffer[4] = ('E' - 64) << 3;
            buffer[5] = ('P' - 64) << 3;
            buffer[6] = ('O' - 64) << 3;
            buffer[7] = ('S' - 64) << 3;
            buffer[8] = (0) << 3;
            buffer[9] = (0) << 3;

            if (menupos == 5)
            {
                SPDR = 0b11111100; //numbers[0+(temp)];
                _delay_loop_1(3);
            }
            else
            {
                SPDR = 0b00000000;
                _delay_loop_1(3);
            }

            DimOn;
            for (unsigned char ij = 0; ij < 8; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(2);
            }

            _delay_loop_1(32);
            buffer[8] = (show_plane_pos + 3) << 3;
            SPDR = numbers[buffer[8] + (screen_line)];
            delay14
            DimOff



        }

        else if (screen_line > 50 && screen_line < 59)
        {
            screen_line = line - (summaryline + 52);
            _delay_loop_1(16);

            buffer[0] = ('S' - 64) << 3;
            buffer[1] = ('E' - 64) << 3;
            buffer[2] = ('T' - 64) << 3;
            buffer[3] = (0) << 3;
            buffer[4] = ('A' - 64) << 3;
            buffer[5] = ('L' - 64) << 3;
            buffer[6] = ('A' - 64) << 3;
            buffer[7] = ('R' - 64) << 3;
            buffer[8] = ('M' - 64) << 3;
            buffer[9] = ('S' - 64) << 3;

            if (menupos == 6)
            {
                SPDR = 0b11111100; //numbers[0+(temp)];
                _delay_loop_1(3);
            }
            else
            {
                SPDR = 0b00000000;
                _delay_loop_1(3);
            }

            DimOn;
            for (unsigned char ij = 0; ij < 10; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(2);
            }
            _delay_loop_1(2);
            DimOff


        }
        else if (screen_line > 60 && screen_line < 69)
        {
            screen_line = line - (summaryline + 62);
            _delay_loop_1(18);


            buffer[0] = ('E' - 64) << 3;
            buffer[1] = ('X' - 64) << 3;
            buffer[2] = ('I' - 64) << 3;
            buffer[3] = ('T' - 64) << 3;
            buffer[4] = (0) << 3;


            if (menupos == 7)
            {
                SPDR = 0b11111100; //numbers[0+(temp)];
                _delay_loop_1(3);
            }
            else
            {
                SPDR = 0b00000000;
                _delay_loop_1(3);
            }

            DimOn;
            for (unsigned char ij = 0; ij < 4; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(5);
            }
            DimOff;



        }


    }

    if (menu == 2)
    {





        screen_line = line - (summaryline + 1);

        if (screen_line < 8)
        {



            if (screen_line == 0)
            {

                buffer[0] = ('A' - 64) << 3;
                buffer[1] = ('L' - 64) << 3;
                buffer[2] = ('T' - 64) << 3;
                buffer[3] = (0) << 3;
                buffer[4] = ('A' - 64) << 3;
                buffer[5] = ('L' - 64) << 3;
                buffer[6] = ('A' - 64) << 3;
                buffer[7] = ('R' - 64) << 3;
                buffer[8] = ('M' - 64) << 3;
                buffer[9] = (0) << 3;
            }
            else
            {
                _delay_loop_1(50);
                if (menupos == 1)
                {
                    SPDR = 0b11111100; //numbers[0+(temp)];
                    _delay_loop_1(3);
                }
                else
                {
                    SPDR = 0b00000000;
                    _delay_loop_1(3);
                }

                DimOn;
                for (unsigned char ij = 0; ij < 10; ij++)
                {
                    SPDR = letters[buffer[ij] + (screen_line)];
                    _delay_loop_1(2);
                }

                _delay_loop_1(10);
                for (unsigned char ij = 0; ij < 4; ij++)
                {
                    SPDR = numbers[GPSbuffer[ij] + (screen_line)];
                    _delay_loop_1(4);
                }
                _delay_loop_1(3);
                DimOff;
            }


        }
        else if (screen_line > 10 && screen_line < 19)
        {
            screen_line = line - (summaryline + 12);
            _delay_loop_1(37);


            buffer[0] = ('L' - 64) << 3;
            buffer[1] = ('O' - 64) << 3;
            buffer[2] = ('S' - 64) << 3;
            buffer[3] = (0) << 3;
            buffer[4] = ('A' - 64) << 3;
            buffer[5] = ('L' - 64) << 3;
            buffer[6] = ('A' - 64) << 3;
            buffer[7] = ('R' - 64) << 3;
            buffer[8] = ('M' - 64) << 3;
            buffer[9] = (0) << 3;

            if (menupos == 2)
            {
                SPDR = 0b11111100; //numbers[0+(temp)];
                _delay_loop_1(3);
            }
            else
            {
                SPDR = 0b00000000;
                _delay_loop_1(3);
            }

            DimOn;
            for (unsigned char ij = 0; ij < 9; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(2);
            }

            _delay_loop_1(16);
            for (unsigned char ij = 4; ij < 8; ij++)
            {
                SPDR = numbers[GPSbuffer[ij] + (screen_line)];
                _delay_loop_1(4);
            }
            _delay_loop_1(3);
            DimOff;



        }
        else if (screen_line > 20 && screen_line < 29)
        {
            screen_line = line - (summaryline + 22);
            _delay_loop_1(34);


            buffer[0] = ('V' - 64) << 3;
            buffer[1] = ('O' - 64) << 3;
            buffer[2] = ('L' - 64) << 3;
            buffer[3] = ('T' - 64) << 3;
            buffer[4] = (0) << 3;
            buffer[5] = ('A' - 64) << 3;
            buffer[6] = ('L' - 64) << 3;
            buffer[7] = ('A' - 64) << 3;
            buffer[8] = ('R' - 64) << 3;
            buffer[9] = ('M' - 64) << 3;

            if (menupos == 3)
            {
                SPDR = 0b11111100; //numbers[0+(temp)];
                _delay_loop_1(3);
            }
            else
            {
                SPDR = 0b00000000;
                _delay_loop_1(3);
            }

            DimOn;
            for (unsigned char ij = 0; ij < 10; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(2);
            }

            _delay_loop_1(18);
            for (unsigned char ij = 9; ij < 12; ij++)
            {
                SPDR = numbers[GPSbuffer[ij] + (screen_line)];
                _delay_loop_1(4);
            }
            _delay_loop_1(3);
            DimOff;




        }


        else if (screen_line > 30 && screen_line < 39)
        {
            screen_line = line - (summaryline + 32);

            if (screen_line == 0)
            {
                buffer[9] = ((align_text / 10) + 3) << 3;
                buffer[10] = ((align_text % 10) + 3) << 3;
            }
            else
            {
                _delay_loop_1(31);

                buffer[0] = ('M' - 64) << 3;
                buffer[1] = ('A' - 64) << 3;
                buffer[2] = ('H' - 64) << 3;
                buffer[3] = (0) << 3;
                buffer[4] = ('A' - 64) << 3;
                buffer[5] = ('L' - 64) << 3;
                buffer[6] = ('A' - 64) << 3;
                buffer[7] = ('R' - 64) << 3;
                buffer[8] = ('M' - 64) << 3;

                if (menupos == 4)
                {
                    SPDR = 0b11111100; //numbers[0+(temp)];
                    _delay_loop_1(3);
                }
                else
                {
                    SPDR = 0b00000000;
                    _delay_loop_1(3);
                }

                DimOn;
                for (unsigned char ij = 0; ij < 9; ij++)
                {
                    SPDR = letters[buffer[ij] + (screen_line)];
                    _delay_loop_1(2);
                }

                _delay_loop_1(17);
                for (unsigned char ij = 12; ij < 16; ij++)
                {
                    SPDR = numbers[GPSbuffer[ij] + (screen_line)];
                    _delay_loop_1(4);
                }
                _delay_loop_1(3);
                DimOff;

            }

        }


        else if (screen_line > 60 && screen_line < 69)
        {
            screen_line = line - (summaryline + 62);
            _delay_loop_1(33);


            buffer[0] = ('E' - 64) << 3;
            buffer[1] = ('X' - 64) << 3;
            buffer[2] = ('I' - 64) << 3;
            buffer[3] = ('T' - 64) << 3;
            buffer[4] = (0) << 3;


            if (menupos == 5)
            {
                SPDR = 0b11111100; //numbers[0+(temp)];
                _delay_loop_1(3);
            }
            else
            {
                SPDR = 0b00000000;
                _delay_loop_1(3);
            }

            DimOn;
            for (unsigned char ij = 0; ij < 4; ij++)
            {
                SPDR = letters[buffer[ij] + (screen_line)];
                _delay_loop_1(4);
            }
            DimOff;
        }
    }

}
*/
void print_time()
{
    screen_line = line - (summaryline + 66);
    _delay_loop_1(35);

    // Stores all the time-numbers in a temporary buffer.
    if (screen_line == 0)
    {
        for (unsigned char ij = 0; ij < 11; ij++)
        {
            //buffer[ij] = time[ij] << 3;
        }
    }
    else
    {
        // Shift out first 8 bit

        DimOn;
        for (unsigned char ij = 0; ij < 2; ij++)
        {
            SPDR = numbers[buffer[ij] + (screen_line)];
            _delay_loop_1(3);
        }



        _delay_loop_1(3);
        SPDR = numbers[(104) + (screen_line)];

        _delay_loop_1(4);
        for (unsigned char ij = 2; ij < 4; ij++)
        {
            SPDR = numbers[buffer[ij] + (screen_line)];
            _delay_loop_1(4);
        }



        _delay_loop_1(3);
        SPDR = numbers[(104) + (screen_line)];
        _delay_loop_1(4);
        for (unsigned char ij = 4; ij < 9; ij++)
        {
            SPDR = numbers[buffer[ij] + (screen_line)];
            _delay_loop_1(2);
        }


        _delay_loop_1(3);
        DimOff;
    }
}

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

        if (screen_line > 64 && screen_line < 73)
        {
            print_time();
        }


        if (screen_line > 80 && screen_line < 89)
        {
            print_version();
        }
    }
    else
    {
/*
        if (landed == 1)
        {
            _delay_loop_1(25);
            screen_line = line - (summaryline + 1);

            if (screen_line < 8)
            {
                _delay_loop_1(30);
                buffer[0] = ('M' - 64) << 3;
                buffer[1] = ('A' - 64) << 3;
                buffer[2] = ('X' - 64) << 3;

                buffer[3] = ('A' - 64) << 3;
                buffer[4] = ('L' - 64) << 3;
                buffer[5] = ('T' - 64) << 3;


                SPDR = letters[buffer[0] + (screen_line)];
                DimOn;
                delay14
                SPDR = letters[buffer[1] + (screen_line)];
                delay13
                SPDR = letters[buffer[2] + (screen_line)];


                _delay_loop_1(10);
                SPDR = letters[buffer[3] + (screen_line)];
                delay15;
                SPDR = letters[buffer[4] + (screen_line)];
                delay15;
                SPDR = letters[buffer[5] + (screen_line)];
                delay13

                buffer[0] = (max_altr[0]) << 3;
                buffer[1] = (max_altr[1]) << 3;
                buffer[2] = (max_altr[2]) << 3;
                buffer[3] = (max_altr[3]) << 3;
                buffer[4] = (max_altr[4]) << 3;


                SPDR = numbers[buffer[0] + (screen_line)];
                delay13
                SPDR = numbers[buffer[1] + (screen_line)];
                delay13
                SPDR = numbers[buffer[2] + (screen_line)];
                delay13
                SPDR = numbers[buffer[3] + (screen_line)];
                delay13

                SPDR = numbers[8 + (screen_line)];
                delay13

                SPDR = numbers[buffer[4] + (screen_line)];
                delay13
                DimOff;

            }

            if (screen_line > 10 && screen_line < 19)
            {
                screen_line = line - (summaryline + 11);
                _delay_loop_1(23);


                buffer[0] = ('M' - 64) << 3;
                buffer[1] = ('A' - 64) << 3;
                buffer[2] = ('X' - 64) << 3;

                buffer[3] = ('S' - 64) << 3;
                buffer[4] = ('P' - 64) << 3;
                buffer[5] = ('D' - 64) << 3;


                SPDR = letters[buffer[0] + (screen_line)];
                DimOn;
                delay13
                SPDR = letters[buffer[1] + (screen_line)];
                delay13
                SPDR = letters[buffer[2] + (screen_line)];


                _delay_loop_1(10);
                SPDR = letters[buffer[3] + (screen_line)];
                delay15;
                SPDR = letters[buffer[4] + (screen_line)];
                delay15;
                SPDR = letters[buffer[5] + (screen_line)];
                delay13


                buffer[0] = (max_speedr[0]) << 3;
                buffer[1] = (max_speedr[1]) << 3;
                buffer[2] = (max_speedr[2]) << 3;
                buffer[3] = (max_speedr[3]) << 3;

                _delay_loop_1(2);
                delay1

                SPDR = numbers[buffer[0] + (screen_line)];
                delay13
                SPDR = numbers[buffer[1] + (screen_line)];
                delay13
                SPDR = numbers[buffer[2] + (screen_line)];
                delay15;
                SPDR = numbers[8 + (screen_line)];
                delay13
                SPDR = numbers[buffer[3] + (screen_line)];
                delay13
                DimOff;

            }

            if (screen_line > 20 && screen_line < 29)
            {
                screen_line = line - (summaryline + 21);
                _delay_loop_1(19);


                buffer[0] = ('M' - 64) << 3;
                buffer[1] = ('A' - 64) << 3;
                buffer[2] = ('X' - 64) << 3;

                buffer[3] = ('L' - 64) << 3;
                buffer[4] = ('O' - 64) << 3;
                buffer[5] = ('S' - 64) << 3;


                SPDR = letters[buffer[0] + (screen_line)];
                DimOn;
                delay13
                SPDR = letters[buffer[1] + (screen_line)];
                delay13
                SPDR = letters[buffer[2] + (screen_line)];


                _delay_loop_1(10);
                SPDR = letters[buffer[3] + (screen_line)];
                delay15;
                SPDR = letters[buffer[4] + (screen_line)];
                delay15;
                SPDR = letters[buffer[5] + (screen_line)];
                delay13

                buffer[0] = (max_losr[0]) << 3;
                buffer[1] = (max_losr[1]) << 3;
                buffer[2] = (max_losr[2]) << 3;
                buffer[3] = (max_losr[3]) << 3;

                _delay_loop_1(2);
                delay2

                SPDR = numbers[buffer[0] + (screen_line)];
                delay13
                SPDR = numbers[buffer[1] + (screen_line)];
                delay13
                SPDR = numbers[buffer[2] + (screen_line)];
                delay13
                SPDR = numbers[buffer[3] + (screen_line)];
                delay13
                DimOff;

            }

            if (screen_line > 31 && screen_line < 40)
            {
                screen_line = line - (summaryline + 32);
                _delay_loop_1(15);
                delay1

                buffer[0] = ('T' - 64) << 3;
                buffer[1] = ('O' - 64) << 3;
                buffer[2] = ('T' - 64) << 3;

                buffer[3] = ('D' - 64) << 3;
                buffer[4] = ('I' - 64) << 3;
                buffer[5] = ('S' - 64) << 3;


                SPDR = letters[buffer[0] + (screen_line)];
                DimOn;
                delay9
                SPDR = letters[buffer[1] + (screen_line)];
                delay15;
                SPDR = letters[buffer[2] + (screen_line)];


                _delay_loop_1(10);
                SPDR = letters[buffer[3] + (screen_line)];
                delay15;
                SPDR = letters[buffer[4] + (screen_line)];
                delay15;
                SPDR = letters[buffer[5] + (screen_line)];
                delay13


                buffer[0] = (total_distancer[0]) << 3;
                buffer[1] = (total_distancer[1]) << 3;
                buffer[2] = (total_distancer[2]) << 3;
                buffer[3] = (total_distancer[3]) << 3;
                buffer[4] = (total_distancer[4]) << 3;

                _delay_loop_1(1);
                delay1

                SPDR = numbers[buffer[0] + (screen_line)];
                delay13
                SPDR = numbers[buffer[1] + (screen_line)];
                delay13

                SPDR = numbers[buffer[2] + (screen_line)];
                delay13
                SPDR = numbers[buffer[3] + (screen_line)];
                delay14
                SPDR = numbers[buffer[4] + (screen_line)];
                delay13
                DimOff;


            }

            if (screen_line > 42 && screen_line < 51)
            {
                screen_line = line - (summaryline + 43);
                _delay_loop_1(14);


                buffer[0] = ('T' - 64) << 3;
                buffer[1] = ('I' - 64) << 3;
                buffer[2] = ('M' - 64) << 3;
                buffer[3] = ('E' - 64) << 3;



                SPDR = letters[buffer[0] + (screen_line)];
                DimOn;
                delay13
                SPDR = letters[buffer[1] + (screen_line)];
                delay13
                SPDR = letters[buffer[2] + (screen_line)];
                delay15;
                SPDR = letters[buffer[3] + (screen_line)];
                delay13

 
                _delay_loop_1(20);
                delay2


                SPDR = numbers[buffer[0] + (screen_line)];
                delay13
                SPDR = numbers[buffer[1] + (screen_line)];
                delay13

                SPDR = numbers[104 + (screen_line)];
                delay13


                SPDR = numbers[buffer[2] + (screen_line)];
                delay13
                SPDR = numbers[buffer[3] + (screen_line)];
                delay13
                DimOff;

            }

            if (screen_line > 53 && screen_line < 62)
            {
                screen_line = line - (summaryline + 54);
                _delay_loop_1(9);

                buffer[0] = ('A' - 64) << 3;
                buffer[1] = ('V' - 64) << 3;
                buffer[2] = ('G' - 64) << 3;

                buffer[3] = ('S' - 64) << 3;
                buffer[4] = ('P' - 64) << 3;
                buffer[5] = ('D' - 64) << 3;


                SPDR = letters[buffer[0] + (screen_line)];
                DimOn;
                delay11
                SPDR = letters[buffer[1] + (screen_line)];
                delay15;
                SPDR = letters[buffer[2] + (screen_line)];


                _delay_loop_1(10);
                SPDR = letters[buffer[3] + (screen_line)];
                delay15;
                SPDR = letters[buffer[4] + (screen_line)];
                delay15;
                SPDR = letters[buffer[5] + (screen_line)];
                delay13


                buffer[0] = (avg_speedr[0]) << 3;
                buffer[1] = (avg_speedr[1]) << 3;
                buffer[2] = (avg_speedr[2]) << 3;
                buffer[3] = (avg_speedr[3]) << 3;

                _delay_loop_1(1);
                delay2

                SPDR = numbers[buffer[0] + (screen_line)];
                delay13
                SPDR = numbers[buffer[1] + (screen_line)];
                delay13

                SPDR = numbers[buffer[2] + (screen_line)];
                delay13

                SPDR = numbers[8 + (screen_line)];
                delay13

                SPDR = numbers[buffer[3] + (screen_line)];
                delay13
                DimOff;

            }

            if (screen_line > 64 && screen_line < 73 && 1 == 0)
            {
                screen_line = line - (summaryline + 65);
                _delay_loop_1(4);

                buffer[0] = ('@' - 64) << 3;
                buffer[1] = ('@' - 64) << 3;
                buffer[2] = ('@' - 64) << 3;

                buffer[3] = ('@' - 64) << 3;
                buffer[4] = ('@' - 64) << 3;
                buffer[5] = ('@' - 64) << 3;


                SPDR = letters[buffer[0] + (screen_line)];
                DimOn;
                delay13
                SPDR = letters[buffer[1] + (screen_line)];
                delay13
                SPDR = letters[buffer[2] + (screen_line)];


                _delay_loop_1(10);
                SPDR = letters[buffer[3] + (screen_line)];
                delay13
                SPDR = letters[buffer[4] + (screen_line)];
                delay15;
                SPDR = letters[buffer[5] + (screen_line)];
                delay13
                DimOff;

            }

            if (screen_line > 75 && screen_line < 84 && 1 == 0)
            {
                screen_line = line - (summaryline + 76);

                buffer[0] = ('@' - 64) << 3;
                buffer[1] = ('@' - 64) << 3;
                buffer[2] = ('@' - 64) << 3;

                buffer[3] = ('@' - 64) << 3;
                buffer[4] = ('@' - 64) << 3;
                buffer[5] = ('@' - 64) << 3;


                SPDR = letters[buffer[0] + (screen_line)];
                DimOn;
                delay13
                SPDR = letters[buffer[1] + (screen_line)];
                delay13
                SPDR = letters[buffer[2] + (screen_line)];


                _delay_loop_1(10);
                SPDR = letters[buffer[3] + (screen_line)];
                delay15;
                SPDR = letters[buffer[4] + (screen_line)];
                delay15;
                SPDR = letters[buffer[5] + (screen_line)];
                delay13
                DimOff;

            }

        }

*/
    }
}

void print_gps()
{

}

void print_top_numbers()
{

    buffer3[0] = speedr[0] << 5;;
    buffer3[1] = speedr[1] << 5;;
    buffer3[2] = speedr[2] << 5;;
    buffer3[3] = speedr[3] << 5;
    buffer3[4] = speedr[4] << 5;



    buffer3[5] = losr[0] << 5;
    buffer3[6] = losr[1] << 5;
    buffer3[7] = losr[2] << 5;
    buffer3[8] = losr[3] << 5;

    if (losr[0] == 3 && losr[1] == 3)
    {
        buffer3[5] = 14 << 5;
        buffer3[6] = losr[2] << 5;
        buffer3[7] = losr[3] << 5;
        buffer3[8] = 14 << 5;
    }
    else if (losr[0] == 3)
    {
        buffer3[5] = 14 << 5;
        buffer3[6] = losr[1] << 5;
        buffer3[7] = losr[2] << 5;
        buffer3[8] = losr[3] << 5;
    }

    if (altitude_offset_on == 0)
    {
        if (altitude2[3] == 14)
        {
            buffer3[9] = 14 << 5;
            buffer3[10] = 14 << 5;
            buffer3[11] = 14 << 5;
            buffer3[12] = altitude2[0] << 5;
            buffer3[13] = altitude2[1] << 5;
            buffer3[14] = altitude2[2] << 5;
        }
        else if (altitude2[4] == 14)
        {
            buffer3[9] = 14 << 5;
            buffer3[10] = 14 << 5;
            buffer3[11] = altitude2[0] << 5;
            buffer3[12] = altitude2[1] << 5;
            buffer3[13] = altitude2[2] << 5;
            buffer3[14] = altitude2[3] << 5;
        }
        else if (altitude2[5] == 14)
        {
            buffer3[9] = 14 << 5;
            buffer3[10] = altitude2[0] << 5;
            buffer3[11] = altitude2[1] << 5;
            buffer3[12] = altitude2[2] << 5;
            buffer3[13] = altitude2[3] << 5;
            buffer3[14] = altitude2[4] << 5;
        }
        else
        {
            buffer3[9] = altitude2[0] << 5;
            buffer3[10] = altitude2[1] << 5;
            buffer3[11] = altitude2[2] << 5;
            buffer3[12] = altitude2[3] << 5;
            buffer3[13] = altitude2[4] << 5;
            buffer3[14] = altitude2[5] << 5;
        }

    }
    else
    {


        if (altituder[0] == 3 && altituder[1] == 3 && altituder[2] == 3)
        {
            buffer3[9] = 14 << 5;
            buffer3[10] = 14 << 5;
            buffer3[11] = 14 << 5;
            buffer3[12] = altituder[3] << 5;
            //     buffer3[13]=altituder[3]<<5;
            buffer3[14] = altituder[4] << 5;
        }
        else if (altituder[0] == 3 && altituder[1] == 3)
        {
            buffer3[9] = 14 << 5;
            buffer3[10] = 14 << 5;
            buffer3[11] = altituder[2] << 5;
            buffer3[12] = altituder[3] << 5;
            //      buffer3[13]=altituder[3]<<5;
            buffer3[14] = altituder[4] << 5;
        }
        else if (altituder[0] == 3)
        {
            buffer3[9] = 14 << 5;
            buffer3[10] = altituder[1] << 5;
            buffer3[11] = altituder[2] << 5;
            buffer3[12] = altituder[3] << 5;
            //       buffer3[13]=altituder[3]<<5;
            buffer3[14] = altituder[4] << 5;
        }
        else
        {
            buffer3[9] = altituder[0] << 5;
            buffer3[10] = altituder[1] << 5;
            buffer3[11] = altituder[2] << 5;
            buffer3[12] = altituder[3] << 5;
            //       buffer3[13]=altituder[4]<<5;
            buffer3[14] = altituder[4] << 5;
        }

        buffer3[13] = 1 << 5;

        if (altitude_negative == 1)
        {
            buffer3[9] = 13 << 5;
        }

    }
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
    else if (horizonBuffer[line] != 0)
    {
        _delay_loop_1(horizonBuffer[line] - horizon_repeat);
        int i = 0;
        if (horizon_repeat > 1)
        {
            horizon_sprite = 0b11111111;
        }

        for (i = 0; i < horizon_repeat + 1; i++)
        {
            SPDR = horizon_sprite;
            delay5;
        }
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
void print_bottom_numbers()
{

    _delay_loop_1(align_text);
    if (currentr[0] == 3)
    {
        buffer2[0] = 14 << 5;
        buffer2[1] = currentr[1] << 5;
        buffer2[2] = currentr[3] << 5;
    }
    else
    {
        buffer2[0] = currentr[0] << 5;
        buffer2[1] = currentr[1] << 5;
        buffer2[2] = currentr[3] << 5;
    }


    if (mahr[0] == 3 && mahr[1] == 3 && mahr[2] == 3)
    {
        buffer2[4] = 14 << 5;
        buffer2[5] = 14 << 5;
        buffer2[6] = 14 << 5;
        buffer2[7] = mahr[3] << 5;
    }
    else if (mahr[0] == 3 && mahr[1] == 3)
    {
        buffer2[4] = 14 << 5;
        buffer2[5] = 14 << 5;
        buffer2[6] = mahr[2] << 5;
        buffer2[7] = mahr[3] << 5;
    }
    else if (mahr[0] == 3)
    {
        buffer2[4] = 14 << 5;
        buffer2[5] = mahr[1] << 5;
        buffer2[6] = mahr[2] << 5;
        buffer2[7] = mahr[3] << 5;
    }
    else
    {
        buffer2[4] = mahr[0] << 5;
        buffer2[5] = mahr[1] << 5;
        buffer2[6] = mahr[2] << 5;
        buffer2[7] = mahr[3] << 5;
    }

    buffer2[8] = voltager[0] << 5;
    buffer2[9] = voltager[1] << 5;
    buffer2[10] = voltager[3] << 5;


    screen_line = (arrowr[0] - 3) * 100 + (arrowr[1] - 3) * 10 + (arrowr[0] - 3);
    _delay_loop_1(align_text);

}


void print_horizon()
{
    draw_horizon_point_at_line(line - summaryline);

}
int update_counter = 0;

extern uint16_t mwcurrent;
extern uint16_t rssi;
extern uint8_t GPS_fix;
void update_data()
{
    if (updatedAnalog)
    {
        int curvar = MwAngle[0];
        currentr[3] = (curvar % 10 + 3);
        currentr[2] = (curvar % 100) / 10 + 3;
        currentr[1] = (((curvar % 1000) / 100) + 3);
        currentr[0] = (curvar / 1000 + 3);


        mahr[3] = (rssi % 10 + 3);
        mahr[2] = (rssi % 100) / 10 + 3;
        mahr[1] = ((rssi / 100) + 3);
        mahr[0] = 3;
        updatedAnalog = 0;

    }
    if (updatedVolt)
    {
        int voltvar = success;
        voltager[0] = (voltvar / 100) + 3 ;
        voltager[1] = ((voltvar % 100) / 10) + 3;
        voltager[3] = ((voltvar % 100) % 10) + 3;
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
        losr[3] = (los % 10 + 3);
        losr[2] = (los % 100) / 10 + 3;
        losr[1] = (((los % 1000) / 100) + 3);
        losr[0] = (los / 1000 + 3);
        updatedDist = 0;
    }
    ///convert speed, one piece at a time
    if (updatedSpeed)
    {
        speedr[4] = (speedkm % 10 + 3);
        speedr[2] = (speedkm % 100) / 10 + 3;
        speedr[1] = (((speedkm % 1000) / 100) + 3);
        speedr[0] = (speedkm / 1000 + 3);
        updatedSpeed = 0;
    }
    if (updatedAlt)
    {
        altituder[4] =  (GPS_altitude % 10 + 3);
        altituder[3] = (GPS_altitude % 100) / 10 + 3;
        altituder[2] = (((GPS_altitude % 1000) / 100) + 3);
        altituder[1] = (GPS_altitude / 1000 + 3);
        updatedAlt = 0;
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
        for (j = 0; j < 90; j++)
        {
            float temp = linear_coef + j * angular_coef + 80;
            if (temp > 0 && temp < 250)
            {
                horizonBuffer[j] = temp;
            }
            else
            {
                horizonBuffer[j] = 0;
            }
        }
        horizon_lenght = abs((int)angular_coef) % 1110;
        int iangle = MwAngle[0];
        /*if ( iangle == 0)
        {
            horizon_lenght = 100;
            horizonBuffer[45] = 150;
        }*/
        horizon_repeat = horizon_lenght / 8;

        if (horizon_lenght < 2)
        {
            horizon_lenght = 2;
        }
        if (!horizon_repeat)
        {
            horizon_sprite = (1 << horizon_lenght) - 2;
        }

        updatedAtt = 0;
    }

}
extern int should_process_now;
int msgcounter = 0;
void blankserialRequest(uint8_t requestMSP);

void send_serial_request()
{
    msgcounter++;
    if (msgcounter >= 4)
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

}

void detectline()
{
    little_delay // This is used to adjust to timing when using SimpleOSD instead of Arduino

    print_timer();

    if (line == serial_line)
    {

        send_serial_request();

    }
    if (line > toplinenumbers && line < (toplinenumbers + 17))
    {
        print_top_large_numbers();
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
        if(homepos)
        {
            print_horizon();
        }
        //
        print_summary();
    }
    else if (line > gps_nmea_line && line < (gps_nmea_line + 9))
    {
        print_gps();
    }
    else if (line == toplinenumbers)
    {
        print_top_numbers();
    }    // ============================================================
    // Buttom line text
    // ============================================================

    else if (line == butlinenumbers)
    {
        print_bottom_numbers();
    }

    //else if (line >= current_calc_line && line <= current_calc_line+20)

    line++;

    // Let's make sure SPI is not idling high.
    SPDR = 0b00000000;

}


