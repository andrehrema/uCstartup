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

int main (void){

        CLKPR = (1<<CLKPCE); // enabling bit writing in clock divider
        CLKPR = 2; //clock divider = 4, from 8 MHz to 2 MHZ

	configure_timer() //Clock = 250K, counts until 250
	configure_USART(); //baud_rate = 9600, RX e TX interruption, even parity, 8 data bits
	configure_ADC(); // clock = 62.5 KHz, AREF = AVCC, auto triggering enabled, trigger_event = free running	

	

	char owner[]="Andre"
	int PIN_owner = 1;
	char package_USART[50]

	humidity sensors[N_SENSORS];
	//detect sensors
	//
	
	for (int PIN = 1; PIN<N_SENSORS+1; PIN++){
		initiate_sensor(&sensors[PIN-1], owner[0], PIN_owner, PIN);
	}

	sei(); //enabling interrupt
	while(1){
		set_sleep_mode(SLEEP_MODE_IDLE); //idle mode,clock_cpu disabled, clock_flash disabled
		sleep_mode(); // sleeping

		if(timer_counter == TIMER_COUNTER_VALUE){
			read_ADC(); //reading data in ADC with free run
			timer_counter = 0;
		}
		if(sensor_read == N_sensors){
			stop_ADC();
		}

		if(all_data_sent()){ //sending a package wether the previous was sent, or the buffer is empty
			sprintf(package_USART, "%s|%i|%i|%i|%i!", sensor.owner_name, sensor.PIN_owner, sensor.state,sensor.data);
			USART_send(&package);
		}
		else{ // send next buffer's character
			USART_next();
		}
	}
		


	return 0;
}
