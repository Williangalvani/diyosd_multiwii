#include "rssi_bat.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

int analogRead(uint8_t pin)
{
        uint8_t low, high, ch = analogInPinToBit(pin);

        // set the analog reference (high two bits of ADMUX) and select the
        // channel (low 4 bits).  this also sets ADLAR (left-adjust result)
        // to 0 (the default).
        ADMUX = (analog_reference << 6) | (pin & 0x0f);

        // without a delay, we seem to read from the wrong channel
        //delay(1);

        // start the conversion
        sbi(ADCSRA, ADSC);

        // ADSC is cleared when the conversion finishes
        while (bit_is_set(ADCSRA, ADSC));

        // we have to read ADCL first; doing so locks both ADCL
        // and ADCH until ADCH is read.  reading ADCL second would
        // cause the results of each conversion to be discarded,
        // as ADCL and ADCH would be locked when it completed.
        low = ADCL;
        high = ADCH;

        // combine the two bytes
        return (high << 8) | low;
}


int startRead(uint8_t pin)
{
        uint8_t low, high, ch = analogInPinToBit(pin);

        // set the analog reference (high two bits of ADMUX) and select the
        // channel (low 4 bits).  this also sets ADLAR (left-adjust result)
        // to 0 (the default).
        

        ADMUX = (analog_reference << 6) | (pin & 0x0f);

        // without a delay, we seem to read from the wrong channel
        //delay(1);

        // start the conversion
        sbi(ADCSRA, ADSC);
        sbi(ADCSRA,ADIE);
}

int read_is_done()
{
        return !bit_is_set(ADCSRA, ADSC);
}

int read_value()
{
        uint8_t low, high;
        low = ADCL;
        high = ADCH;

        // combine the two bytes
        return (high << 8) | low;
}
/*
ISR(ADC_vect)
{
        cbi
}*/