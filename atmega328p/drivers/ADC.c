#include<avr/io.h>
#include<stdint.h>
#include"../devices/humidity_sensor.h"

extern volatile uint8_t sensor_read;

ISR(ADC_vect){
	ADMUX &= ~(1<<(sensor_read-1));
	sensor_read++;
	ADMUX |= (1<<(sensor_read-1)); //read next sensor
	//storing data in the right sensor	
}

void ADC_configuration(){

	ADMUX |= (1<<REFS0); //short circuiting AVCC with AREF, ADC0 is the port enable to be read
	ADCSRA |= (1<<ADCEN)+(1<<ADIE)+(1<<ADPS2)+(1<<ADATE); // enabling ADC, interruption enable and clock divided by 32, resulting in 62.5 kHz, auto triggering enabled
	// ADTS2..0 = 0, free running.
}

void start_ADC(){

	sensor_read = 1; //initiating from the first sensor
	ADCSRA |= ADSC; //starting convertion
}

void stop_ADC(){
	ADCSRA &= ~ADSC; //disabling convertion

}
