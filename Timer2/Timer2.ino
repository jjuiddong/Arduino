// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>
 
#define LEDPIN 2
#define INPUTPIN 3
 
void setup()
{
    pinMode(LEDPIN, OUTPUT);
    pinMode(INPUTPIN, INPUT);
 
    // initialize Timer1
    cli();             // disable global interrupts
    TCCR1A = 0;        // set entire TCCR1A register to 0
    TCCR1B = 0;
 
    // enable Timer1 overflow interrupt:
    TIMSK1 = (1 << TOIE1);
    // Set CS10 bit so timer runs at clock speed:
    TCCR1B |= (1 << CS10);
    // enable global interrupts:
    sei();
}

ISR(TIMER1_OVF_vect)
{
    digitalWrite(LEDPIN, digitalRead(INPUTPIN));
}

void loop()
{
  
}
