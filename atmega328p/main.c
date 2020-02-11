#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <string.h>

#include "drivers/ADC.h"
#include "./drivers/TIMER.h"
#include "drivers/USART.h"
#include "devices/humidity_sensor.h"

volatile int timer_counter = 0; //value of timer_counter
volatile uint8_t converteu;

int main (void){
	//////////////////////////  CONFIGURE THE PORTS /////////////////////////////
        CLKPR = (1<<CLKPCE); // enabling bit writing in clock divider
        CLKPR = 2; //clock divider = 4, from 8 MHz to 2 MHZ



	DDRB = 7; // PB0, PB1, PB2 as output

	
	configure_ADC(); // clock = 125 KHz, AREF = AVCC, single sample	
	configure_TIMER(); //Clock = 250 KHz, counts until 125
	//configure_USART(); //baud_rate = 9600, RX e TX interruption, even parity, 8 data bits


	
	int sensor_send = 0;
	char owner[]="Andre"; //sensor owner
	int PIN_owner = 1; // PIN owner
	char package_USART[50]; //buffer for USART message

	sensor mapped_sensor[N_SENSORS]; //sensors mapped
	//detect sensors
	//
	for (int PIN = 1; PIN<N_SENSORS+1; PIN++){
		initiate_sensor(&mapped_sensor[PIN-1], owner[0], PIN_owner, PIN); //initiating routine
	}


	while(1){
	

		sei(); //enabling interrupt
		set_sleep_mode(SLEEP_MODE_IDLE); //idle mode,clock_cpu disabled, clock_flash disabled
		sleep_mode(); // sleeping
	
	/*
		
		if(timer_counter == TIMER_COUNTER_VALUE){
			PORTB ^= 4;
			timer_counter = 0;
		}

	*/

		if(timer_counter == TIMER_COUNTER_VALUE){
			
			initial_state_ADC();
			timer_counter = 0;

			PORTB ^= 4;

			
			for (int index=0; index < SENSOR_BUFF_LENGTH; index++){ //updating mean and standard deviation
				calc_mean(&mapped_sensor[index]);
				calc_std_dev(&mapped_sensor[index]);
			}
			
			start_ADC();
			
			while(!final_channel()){
				if (converteu){
					add_data_sensor(&mapped_sensor[ADC_channel()],read_ADC());
					next_channel();
				}
			}
			
			stop_ADC();

			//sensor_send = 0;		
		}
		
		
/*		if (final_channel()){	
			//PORTB ^= 1;
			//PORTB |= 2;
			converteu = 0;
			stop_ADC();
		}

		else if(converteu){
			//add_data_sensor(&mapped_sensor[ADC_channel()],read_ADC());
			//PORTB |= 2;	
			converteu = 0;
			next_channel();
			start_ADC();
		}
*/
		
		//send_USART("teste");

	

		/*if(all_sent() && sensor_send<N_SENSORS){ //sending a package wether the previous was sent, or the buffer is empty
			
			sprintf(package_USART, "%s|%i|%i|%i|%i!", &mapped_sensor[sensor_send].owner_name, mapped_sensor[sensor_send].PIN_owner, mapped_sensor[sensor_send].state,mapped_sensor[sensor_send].buffer[mapped_sensor[sensor_send].index_buf]);
			send_USART(&package_USART);
			sensor_send++;
		}*/
		
		//else if(){ // send next buffer's character
		//	USART_next();
		//}
	}
	
	return 0;
}
