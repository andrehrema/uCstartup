#include<avr/io.h>
#include<stdint.h>
#include<interrupt.h>
#include<sleep.h>
#include<string.h>

#include"drivers/ADC.h"
#include"drivers/TIMER.h"
#include"drivers/USART.h"
#include"devices/humidity_sensor.h"

volatile int timer_counter = 0; //value of timer_counter
volatile int8_t sensor_read = 1; //sensor being read
volatile int16_t buffer_ADC;

int main (void){

        CLKPR = (1<<CLKPCE); // enabling bit writing in clock divider
        CLKPR = 2; //clock divider = 4, from 8 MHz to 2 MHZ

	configure_TIMER(); //Clock = 250K, counts until 250
	configure_USART(); //baud_rate = 9600, RX e TX interruption, even parity, 8 data bits
	configure_ADC(); // clock = 62.5 KHz, AREF = AVCC, auto triggering enabled, trigger_event = free running	

	
	int sensor_send = 0;
	char owner[]="Andre"
	int PIN_owner = 1;
	char package_USART[50]

	sensor mapped_sensor[N_SENSORS];
	//detect sensors
	//
	
	for (int PIN = 1; PIN<N_SENSORS+1; PIN++){
		initiate_sensor(&mapped_sensor[PIN-1], owner[0], PIN_owner, PIN);
	}

	sei(); //enabling interrupt
	while(1){
		set_sleep_mode(SLEEP_MODE_IDLE); //idle mode,clock_cpu disabled, clock_flash disabled
		sleep_mode(); // sleeping

		if(timer_counter == TIMER_COUNTER_VALUE){
			read_ADC(); //reading data in ADC with free run
			timer_counter = 0;
			sensor_send = 0;
		}

		if (sensor_read < N_SENSORS){
			add_data_sensor(&mapped_sensor[sensor_read],buffer_ADC);
			buffer_adc;
			sensor_read++;
		        ADMUX |= (1<<(sensor_read)); //read next sensor
		}
		if(sensor_read == N_SENSORS){
			stop_ADC();
		}
		

		if(all_data_sent() && sensor_send<N_SENSORS){ //sending a package wether the previous was sent, or the buffer is empty
			
			sprintf(package_USART, "%s|%i|%i|%i|%i!", mapped_sensor[sensor_send].owner_name[sensor_send], mapped_sensor[sensor_send].PIN_owner, mapped_sensor[sensor_send].state,mapped_sensor[sensor_send].data);
			USART_send(&package);
			sensor_send++;
		}
		else if(){ // send next buffer's character
			USART_next();
		}
	}
		


	return 0;
}
