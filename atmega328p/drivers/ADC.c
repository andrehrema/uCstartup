#include<avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>
#include"macros.h"

static volatile int8_t sensor_read;
static volatile uint16_t buffer_ADC;
extern volatile uint8_t converteu;

ISR(ADC_vect){
	ADMUX &= ~(1<<(sensor_read-1));
	PORTB++;
	buffer_ADC |= ADCL;
	buffer_ADC |= (ADCH<<8);
	ADCSRA &= ~ADIF;
	converteu = 1;
	next_channel();
	//storing data in the right sensor	
}

void configure_ADC(){

	ADMUX &= ~((1<<MUX0)+(1<<MUX1)+(1<<MUX2)+(1<<MUX3));
	ADMUX |= (1<<REFS0); //short circuiting AVCC with AREF, ADC0 is the port enable to be read
	//ADCSRA |= (1<<ADEN)+(1<<ADIE)+(1<<ADPS2)+(1<<ADATE); // enabling ADC, interruption enable and clock divided by 32, resulting in 62.5 kHz, auto triggering enabled
	ADCSRA |= (1<<ADEN)+(1<<ADIE);
	sensor_read = 0;
	converteu = 0;
	//ADCSRA &= ~ADSC;
	//ADTS2..0 = 0, free running.
}

void initial_state_ADC(){
	sensor_read=0;
}

void start_ADC(){
	
	buffer_ADC=0;
	//sensor_read = 0; //initiating from the first sensor
	PRR &= ~PRADC;
	ADCSRA |= ADSC; //starting convertion
}

void stop_ADC(){
	
	ADCSRA &= ~ ((1<<ADSC) + (1<<ADIF)); //disabling convertion
	ADMUX &= ~((1<<MUX0)+(1<<MUX1)+(1<<MUX2)+(1<<MUX3));
}

void next_channel(){
	sensor_read++;
	ADMUX |= (1<<(sensor_read-1)); //read next sensor
}

int read_ADC(){ //return the read value
	return buffer_ADC;
}


int final_channel(){ //return true if the last channel has been already read
	
	if (sensor_read == N_SENSORS)
		return 0;
	else
		return 1;
}


int ADC_channel(){
	return sensor_read;
}
