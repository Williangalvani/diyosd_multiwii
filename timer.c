
#include "Arduino.h"
#include "Math.h"
#include <avr/delay.h>
#include <avr/pgmspace.h>

// timer for time keeping without interruptions

void setup_timer();
void read_millis();
void update();

int minutes = 0;
int seconds  = 0;
int millisseconds  = 0;


void setup_timer()
{

    // setup timer0 for keeping track of time
    TCCR1B =
        (0 << CS12) | //Prescale 8
        (1 << CS11) | //Prescale 8
        (0 << CS10);
    TCNT1 = 0;

}

void update()
{
    millisseconds += ( TCNT0 / 2);
    if (millisseconds > 1000)
    {
        seconds++;
        millisseconds = 0;
    }
    if (seconds > 60)
    {
        minutes++;
        seconds -= 60;
    }
}
