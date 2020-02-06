#include<avr/io.h>
#include<stdint.h>
#include"ADC.h"
#include"TIMER.h"


extern volatile uint16_t timer_counter;

ISR (TIMER2_COMPA_vect){ //timer interruption handler

        timer_counter+=1;
}


void configure_timer(){

        TCCR2A = (1<<WGM21); //timer counts until OCRA value
        OCR2A  = OCR_VALUE; //OCRA value

        TIMSK2 = (1<<OCIE2A); // interruption when timer value == OCRA value

        TCCR2B = CLOCK_DIVIDER; // timer dividided by 8, from 2MHz to 250KHz
        TCNT2 = 0; //timer intial value

}

