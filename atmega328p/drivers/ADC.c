#include<avr/io.h>
#include<stdint.h>
#include"../devices/humidity_sensor.h"

extern volatile uint8_t sensor_read;
extern volatile uint16_t buffer_ADC;
ISR(ADC_vect){
	ADMUX &= ~(1<<(sensor_read));

	buffer_ADC |= ADCL;
	buffer_ADC |= (ADCH<<8);
	//storing data in the right sensor	
}

void configure_ADC(){

	ADMUX |= (1<<REFS0); //short circuiting AVCC with AREF, ADC0 is the port enable to be read
	ADCSRA |= (1<<ADCEN)+(1<<ADIE)+(1<<ADPS2)+(1<<ADATE); // enabling ADC, interruption enable and clock divided by 32, resulting in 62.5 kHz, auto triggering enabled
	// ADTS2..0 = 0, free running.
}

void start_ADC(){
	ADMUX &= ~((1<<MUX0)+(1<<MUX1)+(1<<MUX2)+(1<<MUX3));
	buffer_ADC=0;
	sensor_read = 0; //initiating from the first sensor
	ADCSRA |= ADSC; //starting convertion
}

void stop_ADC(){
	
	ADCSRA &= ~ ((1<<ADSC) + (1<<ADIF)); //disabling convertion
	sensor_read = 0;
}
