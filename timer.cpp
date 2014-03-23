
#include "timer.h"
#include "Arduino.h"
#include "Math.h"
#include <avr/delay.h>
#include <avr/pgmspace.h>
#include "rssi_bat.h"
#include "variables.h"
// timer for time keeping without interruptions

void setup_timer()
{

    // setup timer0 for keeping track of time
    TCCR0B =
        (1 << CS12) | //Prescale 1024
        (0 << CS11) | //Prescale 1024
        (1 << CS10);
    TCNT0 = 0;
   

}

void start_timer()
{
    TCNT0 = 146;
    sbi(TIMSK0,TOIE0);//enable interrutps on overflow
}
/*
ISR(TIMER0_OVF_vect)
{
    cbi(TIMSK0,TOIE0);//enable interrutps on overflow
    //start_read();

}
*/
