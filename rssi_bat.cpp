#include "variables.h"
#include "rssi_bat.h"

#define ADCchannel 0

#define conversion_not_done()  ADCSRA & (1<<ADSC)
#define conversion_done() !(ADCSRA & (1<<ADSC))

void initADC()
{
    // Select Vref=AVcc
    ADMUX |= (1 << REFS0);
    //set prescaller to 128 and enable ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
     ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
}


void update_analog()
{
    if (conversion_done())
    {
    	cbi(ADCSRA,ADIF);
        uint16_t val = ADC;
        if (val < 150)
        {
            uint16_t oldrssi = rssi;
            //rssi = ((rssi << 8) - oldrssi) + ADC;
            rssi = rssi*0.95 + ADC*0.05	;
            percentrssi = 130 - rssi;
        }
          ADCSRA |= (1<<ADSC);
    }
}