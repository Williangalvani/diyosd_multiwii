
// Depeloped by Willian Galvani - 2014
// Contact: williangalvani@gmail.com


// Based on work by Dennis Frie - 2011
// Contact: Dennis.frie@gmail.com

// Discussion:
// www.rcgroups.com/forums/showthread.php?t=1473207

// Notes on DIY hardware pins:;
// pin 6 = PD6 / AIN0 (Reference voltage)
// Pin 7 = PD7 / AIN1 (Video)
// Pin 11 = MOSI (SPI) used for pixel-generation.
// Pin 8 = Dimming (Optional)


#include <avr/delay.h>

#include <EEPROM.h>
#include "config.h"
#include "output.h"
#include "gps.h"
#include "menu.h"
#include "rssi_bat.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

extern int line;

#define F_CPU 16000000
#define baud 115200



int minutes = 0;
int seconds  = 0;

char updated_clock = 1;

uint8_t frame_counter = 0;

extern int16_t *rcData;

void setup()
{
    rcData[0] = 1500;
    // Set pin-modes:
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);


    // Init Serial communication.
    Serial.begin(BAUD);

    SPCR =
        (1 << SPE) | //Enable SPI
        (1 << MSTR) | // Set as master
        (0 << SPR1) | // Max speed
        (0 << SPR0) | // Max speed
        (0 << DORD) | // Year, Try to set this to 1 :D (Will mirror the byte)
        (1 << CPOL) | // Doesnt really matter, its the SCK polarity
        (1 << CPHA); //

    SPSR = (1 << SPI2X); // SPI double speed - we want 8 mhz output speed.
    SPDR = 0b00000000; // IMPORTANT.. The SPI will idle random at low or high in the beginning. If it idles high you will get black screen = bad idea in FPV.
    // It will always idle at the last bit sent, so always be sure the last bit is 0. The main-loop and end of each line will always send 8 zeros - so it should
    // be pretty safe.

    // Analog read enable and set prescale. You can change prescale if you like.
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0);

    // Disable standard Arduino interrupts used for timer etc. (you can clearly see the text flicker if they are not disabled)
    TIMSK0 = 0;
    TIMSK1 = 0;
    TIMSK2 = 0;





    // If Arduino is used
    if (CONTROLLER == 0)
    {
        // Init analog comparator to register new line and frame
        ADCSRB = 0b00000001; // Set analog comparator mode

        ACSR = 0b00001011; //Enable Analog comparator interrupt

        // Set interrupt on falling output edge.
        ADCSRA |= (1 << ADSC);

        // Start timer 2 - used to determine if it's a new frame or line.
        TCCR2B =
            (0 << CS22) | //Prescale 1024
            (0 << CS21) | //Prescale 1024
            (1 << CS20) | //Prescale 1024
            (0 << WGM22); // CTC mode (Clear timer on compare match)

        // Button with internal pull-up.
        pinMode(Buttonpin_, INPUT);
        digitalWrite(Buttonpin_, HIGH);
    }

    // If SimpleOSD/LM1881
    if (CONTROLLER == 1)
    {
        attachInterrupt(0, detectline, FALLING);
        attachInterrupt(1, detectframe, RISING);
        pinMode(5, OUTPUT);
        digitalWrite(5, HIGH); // Turn on the led

        // Button with internal pull-up.
        pinMode(6, INPUT);
        digitalWrite(6, HIGH);
    }


initADC();


}



// ====================================================================================================================================================================================================================
// ====================================================================================================================================================================================================================
// ====================================================================================================================================================================================================================
// ====================================================================================================================================================================================================================
// Analog comparator interrupt:
ISR(ANALOG_COMP_vect)
{
    // Reset counter
    TCNT2 = 0;

    // Wait for the sync to go high again;
    while ((ACSR & 0b00100000) == 0b00100000) { }

    // If the counter has exceeded the "new line sync time", it's a new
    // frame. In that case, we just need to reset the line-counter.
    //
    if (TCNT2 > 75)
    {
        line = 0;


    }
    //cbi(UCSR0B,RXCIE0);
    detectline();
    //sbi(UCSR0B,RXCIE0);
}


// ====================================================================================================================================================================================================================
// ====================================================================================================================================================================================================================
// ====================================================================================================================================================================================================================
// ====================================================================================================================================================================================================================



void loop()
{
    while (1 == 1)
    {
        do_multiwii_communication();
        process_menu();
        update_analog();
    }

}




