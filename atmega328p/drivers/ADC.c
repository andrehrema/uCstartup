#include<avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>
#include"ADC.h"
#include"macros.h"

static volatile int8_t sensor_read;
static volatile uint16_t buffer_ADC;
extern volatile uint8_t converteu;


ISR(ADC_vect){
	buffer_ADC |= ADCL + (ADCH<<8);
	
	converteu = 1;
}

void configure_ADC(){
	ADMUX |= (1<<REFS0); //short circuiting AVCC with AREF, ADC0 is the port enable to be read
	
	ADMUX &= ~((1<<MUX0)+(1<<MUX1)+(1<<MUX2)+(1<<MUX3)); //channel 1
	ADCSRA |= ((1<<ADEN)+(1<<ADPS2)); //enabling interruption ad clock divided by 16, clock = 125 KHz

	PRR &= ~(1<<PRADC); // no low power on ADC	

	sensor_read = 0;
}

void initial_state_ADC(){
	sensor_read=0;
}

void start_ADC(){
	
	PORTB |= 2;	
	buffer_ADC=0;
	ADCSRA |= ((1<<ADIE)+(1<<ADSC)); //starting the adc conversion and enabling ADC interruption
}

void stop_ADC(){
	
	PORTB &= ~2;	
	ADCSRA &= ~ ((1<<ADSC)+(1<<ADIE)); //disabling convertion, and disabling ADC
	ADMUX &= ~((1<<MUX0)+(1<<MUX1)+(1<<MUX2)+(1<<MUX3)); // channel 0
}



void next_channel(){
	sensor_read++;
	converteu=0;	
	ADMUX |= (1<<(sensor_read-1)); //read next sensor
	ADCSRA |= (1<<ADSC);
}

int read_ADC(){ //return the read value
	return buffer_ADC;
}


int final_channel(){ //return true if the last channel has been already read
	
	if (sensor_read == N_SENSORS)
		return 1;
	else
		return 0;
}


int ADC_channel(){
	return sensor_read;
}



