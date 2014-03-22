
#include "ascii.h"
#include "variables.h"
#include "output.h"
#include "config.h"
#include "gps.h"




#define True 1
#define False 0


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

#define output_small_number_line(number,aline) SPDR = pgm_read_byte_near(&numbers[(number) + (aline)]);
#define to_index(ch) (ch - 64) << 3;

//#define output_big_number_left_part(buffer) SPDR = LargeNumbers[buffer + 2 * screen_line];
//#define output_big_number_right_part(buffer) SPDR = LargeNumbers[buffer + 2 * screen_line + 1];

#define output_big_number_left_part(buffer) SPDR = pgm_read_byte_near(&LargeNumbers[buffer + 2 * screen_line]);
#define output_big_number_right_part(buffer) SPDR = pgm_read_byte_near(&LargeNumbers[buffer + 2 * screen_line + 1]);



#define delaybetweenchars 2
#define delaybetweenwords 3

#define small_arrow_left  ('a' - 64) << 3;

#define wait_before_next_char() delay4;

//extern uint16_t frame_counter = 0;

unsigned char customMessage = 0;
char *data;
char data_length = 0;

unsigned char toptext[12] = {'S' - 64, 'P' - 64, 'E' - 64, 'E' - 64, 'D' - 64, 'L' - 64, 'O' - 64, 'S' - 64, 'A' - 64, 'L' - 64, 'T' - 64, 20};

// Linenumber
int line = 0;
int screen_line = 0;

// Standard integers to use with for/while loops etc.
int a = 0;
int i = 0;
int k = 0;

unsigned char ii = 0;


#include "Arduino.h"
#include "Math.h"
#include <avr/delay.h>
#include <avr/pgmspace.h>

//========================================
// Data for mAh
//========================================
// Measuring amps and mah's;
int current = 0;

unsigned char currentr[] = {3, 3, 3, 3, 3}; // Stores current characters (numbers) written to screen
unsigned char text_buffer_bottom_mid[] = {3, 3, 3, 3, 3}; // Stores current characters (numbers) written to screen
int bat_volt = 0;

long mah = 0;
long mahtemp = 0;
unsigned char mahr[] = {3, 3, 3, 3, 3, 3}; // Stores mah characters (numbers) written to screen


//ADC (It's a 10 bit ADC, so we need to read from 2 registers and put them together. This is what ADSCtemp is used for
int ADCtemp = 0;
int ADCtemp2 = 0;
int ADCreal = 0; // Just a stupid name for the complete analog-read
int ADCreal2 = 0; // Can be replaced with ADCreal


//========================================
// Buffers
//========================================
unsigned char buffer[50];
unsigned char menuBuffer[91];
unsigned char menu_dim[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// Need an integer when reading large characeters (will exceed 256)
int buffer2[12] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
int buffer3[17];


//========================================
// Mixed
//========================================

unsigned int mahkm_buf[5];
unsigned char showcoordinates = 1;
unsigned char rssir[] = {3, 3, 3};




unsigned char satellitesr[3] = {3, 3, 3};

int horizon_lenght = 1;
char horizon_sprite = 1;
int horizon_repeat = 0;


unsigned char horizonBuffer[90];
unsigned char speedr[] = {1, 1, 1, 1};


int current_letter = 0;
unsigned char charcounter;
char printing_numbers = 0;

void print_large_3(int *buffer);
void print_large_5(int *buffer);
void serialMSPCheck();

void draw_arrow()
{
    SPDR = pgm_read_byte_near(&HomeArrow[buffer2[11] + 2 * screen_line]);
    DimOn;
    delay13

    SPDR = pgm_read_byte_near(&HomeArrow[buffer2[11] + 2 * screen_line + 1]);
    delay5;
    DimOff;

}

void write_speed()
{
    print_large_5(buffer3);
    delay15;
    DimOff
}

void print_altitude()
{

    _delay_loop_1(5);
    DimOn;
    for (int i = 0; i < 6; i++)
    {
        output_big_number_left_part(buffer3[10 + i]);
        delay11;

        output_big_number_right_part(buffer3[10 + i]);
        delay4


    }
    DimOff;

}

void print_large_3(int *buffer)
{

    output_big_number_left_part(buffer[0]);
    DimOn;
    delay9
    output_big_number_right_part(buffer[0]);
    delay4

    output_big_number_left_part(buffer[1]);
    delay11;

    output_big_number_right_part(buffer[1]);
    delay4

    output_big_number_left_part(buffer[2]);
    delay11;

    output_big_number_right_part(buffer[2]);
}

void print_large_4(int *buffer)
{

    output_big_number_left_part(buffer[0]);
    DimOn;
    delay9

    output_big_number_right_part(buffer[0]);
    delay4


    output_big_number_left_part(buffer[1]);
    delay11;

    output_big_number_right_part(buffer[1]);
    delay4;


    output_big_number_left_part(buffer[2]);
    delay11;

    output_big_number_right_part(buffer[2]);
    delay4

    output_big_number_left_part(buffer[3]);
    delay11;

    output_big_number_right_part(buffer[3]);
    delay1;
    DimOff;
}

void print_large_5(int *buffer)
{

    DimOn;
    delay9

    output_big_number_right_part(buffer[0]);
    delay4

    output_big_number_left_part(buffer[1]);
    delay11;

    output_big_number_right_part(buffer[1]);
    delay4;

    output_big_number_left_part(buffer[2]);
    delay11;

    output_big_number_right_part(buffer[2]);
    delay6

    output_big_number_left_part(buffer[3]);
    delay12;

    output_big_number_right_part(buffer[3]);
    delay6;

    output_big_number_left_part(buffer[4]);
    delay13;

    output_big_number_right_part(buffer[4]);
    delay3;
    DimOff;
}


void print_small_5(unsigned char *buffer)
{
    // Updates SPDR (SPI buffer)
    output_small_byte(buffer[0]);
    DimOn;
    // Adds delay before the SPI buffer can be updated again.
    delay12

    output_small_byte(buffer[1]);
    delay12

    output_small_byte(buffer[2]);
    delay13

    output_small_byte(buffer[3]);
    delay13

    output_small_byte(buffer[4]);
    delay13
    DimOff;
}

void print_small_3(unsigned char *buffer)
{

    output_small_byte(buffer[0]);
    DimOn;
    delay12

    output_small_byte(buffer[1]);
    delay13

    output_small_byte(buffer[2]);
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
        write_speed();
        buffer2[11] = arrowd << 5;

        _delay_loop_1(3);

        print_large_4((int *)&buffer3[5]);

        _delay_loop_1(1);

        draw_arrow();

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
            delay11

            output_small_letter('U');
            delay11

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
            delay10

            output_small_letter('A');
            delay11

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
            delay11

            output_small_letter('S');
            delay13;

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



void clear_menu()
{
    for (int i = 0; i < 91; i++)
    {
        menuBuffer[i] = to_index(' ') ;
    }
}

void print_menu()
{
    int ij;
    screen_line = line - (summaryline + 1);

    _delay_loop_1(5);

    //_delay_loop_1(65);




    for (int i = 0; i < 10; i++)
    {

        if (screen_line > i * 10 && screen_line < i * 10 + 9 )
        {


            if (printing_numbers)
            {
                _delay_loop_1(100 - 10 * i);
                if (menu_dim[i])
                {
                    DimOn;
                }

                ij = 10 * i;
                uint8_t counter = screen_line - 10 * i;

                output_small_byte_line(menuBuffer[ij++], counter);
                _delay_loop_1(3);
                output_small_byte_line(menuBuffer[ij++], counter);
                _delay_loop_1(3);
                output_small_byte_line(menuBuffer[ij++], counter);
                _delay_loop_1(3);
                output_small_byte_line(menuBuffer[ij++], counter);
                _delay_loop_1(3);
                output_small_byte_line(menuBuffer[ij++], counter);
                _delay_loop_1(3);
                output_small_byte_line(menuBuffer[ij++], counter);
                _delay_loop_1(3);
                output_small_byte_line(menuBuffer[ij++], counter);
                _delay_loop_1(3);
                if (i > 2 && i < 6)
                {
                    output_small_number_line(menuBuffer[ij++] << 3, counter);
                    _delay_loop_1(2);
                    output_small_number_line(menuBuffer[ij++] << 3, counter);
                    _delay_loop_1(2);
                    output_small_number_line(menuBuffer[ij++] << 3, counter);
                    _delay_loop_1(2);
                }
                DimOff;

            }
            else
            {
                _delay_loop_1(50 - 5 * i);
                uint8_t counter = screen_line - 10 * i;
                for (ij = 10 * i; ij <= 10 * i + 9; ij++)
                {

                    output_small_byte_line(menuBuffer[ij], counter);
                    wait_before_next_char();
                }
                DimOff;
            }


        }
    }


}



unsigned char altituder[6] ;
unsigned char losr[] = {1, 1, 1, 1}; // Stores LOS characters (numbers) written to screen
unsigned char arrowr[] = {3, 3, 3};



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

    convert_to_big_numbers(altituder, &buffer3[10], 3, 6);
}

void draw_horizon_point_at_line(int line)
{
    unsigned int pixels = 0b10101010;
    if (line == 1 || line == 89 || line == 45)
    {
        if (line == 45  && horizonBuffer[45] == 70)
        {
            pixels = 0b11111110;
        }
        SPDR = pixels;
        _delay_loop_1(align_text);
        int i;
        for (i = 0; i < 70; i++)
        {
            SPDR = pixels;
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
        /*DimOn;
        delay5;
        DimOff;*/
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
            output_small_byte(buffer[ij]);
            _delay_loop_1(5);
        }

        // Writes ':'
        SPDR = pgm_read_byte_near(&numbers[104 + screen_line]);
        _delay_loop_1(10);

        for (unsigned char ij = 3; ij < 5; ij++)
        {
            output_small_number_line(buffer[ij], screen_line);
            _delay_loop_1(5);
        }
        _delay_loop_1(2);
        DimOff;

        /////////////now the fix///////////////
        _delay_loop_1(10);

        DimOn;
        for (unsigned char ij = 5; ij < 12; ij++)
        {
            output_small_byte(buffer[ij]);
            _delay_loop_1(2);
        }

        SPDR = pgm_read_byte_near(&numbers[104 + screen_line]);
        _delay_loop_1(6);


        for (unsigned char ij = 12; ij < 15; ij++)
        {
            output_small_byte(buffer[ij]);
            _delay_loop_1(4);
        }
        _delay_loop_1(3);
        DimOff;
    }
}






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
        DimOn;
        unsigned char ij;
        if (mode_armed)
        {
            for (ij = 0; ij <= 4; ij++)
            {
                output_small_byte(buffer[ij]);
                wait_before_next_char();
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_stable)
        {
            for (ij = 6; ij <= 10; ij++)
            {
                output_small_byte(buffer[ij]);
                wait_before_next_char();
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_horizon)
        {
            for (ij = 12; ij <= 18; ij++)
            {
                output_small_byte(buffer[ij]);
                wait_before_next_char();
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_baro)
        {
            for (ij = 20; ij <= 23; ij++)
            {
                output_small_byte(buffer[ij]);
                wait_before_next_char();
                delay3;
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_mag)
        {
            for (ij = 25; ij <= 27; ij++)
            {
                output_small_byte(buffer[ij]);
                wait_before_next_char();
                delay5;
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_gpshome)
        {
            for (ij = 29; ij <= 31; ij++)
            {
                output_small_byte(buffer[ij]);
                wait_before_next_char();
                delay5;
            }
            _delay_loop_1(delaybetweenwords);

        }
        if (mode_gpshold)
        {
            for (ij = 33; ij <= 39; ij++)
            {
                output_small_byte(buffer[ij]);
                wait_before_next_char();
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

        while (number >= 10)
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


uint16_t totalmsg = 0;
void update_data()
{
    if (updatedAnalog)
    {
        int curvar = 0;
        copy_to_buffer(curvar, currentr, 4, AS_DECIMAL);


        int rssivar = 0;
        copy_to_buffer(rssivar, mahr, 4, AS_INTEGER);
        updatedAnalog = 0;

    }
    if (updatedVolt)
    {
        //rcData[0] = 1500;
        int16_t voltvar = vario;
        copy_to_buffer(voltvar, text_buffer_bottom_mid, 4, AS_INTEGER);
        updatedVolt = 0;
    }
    if (updatedSats)
    {
        copy_to_buffer(GPS_numSat, satellitesr, 2, AS_INTEGER);
        //satellitesr[0] = (GPS_numSat / 10) + 3 ;
        //satellitesr[1] = (GPS_numSat % 10) + 3;
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
        copy_to_buffer(GPS_speed, speedr, 5, AS_DECIMAL);
        updatedSpeed = 0;
    }
    if (updatedAlt)
    {
        copy_to_buffer(GPS_altitude, altituder, 6 , AS_DECIMAL);
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
        horizon_sprite = 0b11111110;
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
    if (customMessage)
    {
        if (customMessage == MSP_SET_PID)
        {
            send_msp_set_pid();
            customMessage = MSP_PID;
            data = 0;
            data_length = 0;
        }
        else
        {
            if (data_length == 0)
            {
                blankserialRequest(customMessage);
            }
            customMessage = 0;
        }


    }
    else if (msgcounter >= 7)
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
    else if (msgcounter == 6 )
    {
        blankserialRequest(MSP_RC);
    }

}

void detectline()
{
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
        if (menuon)
        {
            print_menu();
        }
        else
        {
            print_horizon();

        }

        //print_summary();
    }
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
}


